﻿/*
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
#include "CarenD2D1BitmapBrush1.h"

//Destruidor.
CarenD2D1BitmapBrush1::~CarenD2D1BitmapBrush1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1BitmapBrush1::CarenD2D1BitmapBrush1()
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
CarenResult CarenD2D1BitmapBrush1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1BitmapBrush1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1BitmapBrush1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1BitmapBrush1**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1BitmapBrush1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1BitmapBrush1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1BitmapBrush1**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1BitmapBrush1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1BitmapBrush1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1BitmapBrush1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1BitmapBrush1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1BitmapBrush1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1BitmapBrush1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1BitmapBrush1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1BitmapBrush1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1BitmapBrush1();
}



// Métodos da interface proprietária(ICarenD2D1BitmapBrush1)


/// <summary>
/// Retorna o modo de interpolação atual do pincel.
/// </summary>
/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação atual.</param>
void CarenD2D1BitmapBrush1::GetInterpolationMode1([Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolationMode)
{
	//Variaveis a serem utilizadas.
	D2D1_INTERPOLATION_MODE OutInterPolationMode;

	//Chama o método para realizar a operação.
	OutInterPolationMode = PonteiroTrabalho->GetInterpolationMode1();

	//Converte e define no parametro de saida.
	Param_Out_InterpolationMode = ConverterPara<CA_D2D1_INTERPOLATION_MODE>(OutInterPolationMode);
}

/// <summary>
/// Define o modo de interpolação para o pincel.
/// </summary>
/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado.</param>
void CarenD2D1BitmapBrush1::SetInterpolationMode1(CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetInterpolationMode1(ConverterPara<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode));
}



// Métodos da interface proprietária(ICarenD2D1BitmapBrush)


/// <summary>
/// Obtém a fonte bitmap que este pincel usa para pintar.
/// </summary>
/// <param name="Param_Out_Bitmap">Quando este método retorna, contém o endereço a um ponteiro para o bitmap com o qual este pincel pinta.</param>
CarenResult CarenD2D1BitmapBrush1::GetBitmap([Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmapBrush = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetBitmap(&pBitmapBrush);

	//Verifica se a interface é valida
	if (!ObjetoValido(pBitmapBrush))
	{
		//A interface não é valida.

		//Define erro 
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Adiciona o ponteiro a interface de saida.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pBitmapBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Não foi possivel definir o ponteiro.

		//Libera o ponteiro para a interface
		pBitmapBrush->Release();
		pBitmapBrush = NULL;

		//Libera a gerenciada
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o método pelo qual a escova inclina horizontalmente as áreas que se estendem além de seu bitmap.
/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
/// </summary>
/// <param name="Param_Out_ExtendModeX">Retorna um valor que especifica como a escova horizontalmente ladrilhos(Tile) as áreas que se estendem além de seu bitmap.</param>
void CarenD2D1BitmapBrush1::GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = PonteiroTrabalho->GetExtendModeX();

	//Converte e define no parametro de saida.
	Param_Out_ExtendModeX = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém o método pelo qual a escova corta verticalmente as áreas que se estendem além de seu bitmap.
/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
/// </summary>
/// <param name="Param_Out_ExtendModeY">Retorna um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
void CarenD2D1BitmapBrush1::GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = PonteiroTrabalho->GetExtendModeY();

	//Converte e define no parametro de saida.
	Param_Out_ExtendModeY = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém o método de interpolação usado quando o bitmap da escova é dimensionado ou girado.
/// </summary>
/// <param name="Param_Out_InterpolationMode">Retorna o método de interpolação utilizado quando o bitmap da escova é dimensionado ou girado.</param>
void CarenD2D1BitmapBrush1::GetInterpolationMode([Out] CA_D2D1_BITMAP_INTERPOLATION_MODE% Param_Out_InterpolationMode)
{
	//Variaveis a serem utilizadas.
	D2D1_BITMAP_INTERPOLATION_MODE OutInterPolationMode;

	//Chama o método para realizar a operação.
	OutInterPolationMode = PonteiroTrabalho->GetInterpolationMode();

	//Converte e define no parametro de saida.
	Param_Out_InterpolationMode = ConverterPara<CA_D2D1_BITMAP_INTERPOLATION_MODE>(OutInterPolationMode);
}

/// <summary>
/// Especifica a fonte bitmap que este pincel usa para pintar.
/// Este método especifica a fonte bitmap que este pincel usa para pintar. O bitmap não é redimensionado ou redimensionado automaticamente para se encaixar na geometria que preenche. 
/// O bitmap permanece em seu tamanho nativo. Para redimensionar ou traduzir o bitmap, use o método ICarenD2D1Brush::SetTransform para aplicar uma transformação no pincel.
/// O tamanho nativo de um bitmap é a largura e altura em pixels bitmap, dividido pelo DPI bitmap. Este tamanho nativo forma o Tile do pincel. Para ladrilar uma sub-região do bitmap, 
/// você deve gerar um novo bitmap contendo esta sub-região e usar SetBitmap para aplicá-lo no Brush.
/// </summary>
/// <param name="Param_Bitmap">Retorna a fonte de bitmap usada pelo pincel.</param>
CarenResult CarenD2D1BitmapBrush1::SetBitmap(ICarenD2D1Bitmap^ Param_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmap = NULL;

	//Recupera o ponteiro para o bitmap a ser definido.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se recuperou com sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera o ponteiro para o bitmap.

		//Saido método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetBitmap(pBitmap);

	//Define sucesso na operação.
	SetCarenSucesso(Resultado);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica como o Brush inclina horizontalmente as áreas que se estendem além de seu bitmap.
/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
/// vertical(SetExtendModeY) para determinar como preencher a área restante.
/// </summary>
/// <param name="Param_ExtendModeX">Um valor que especifica como o pincel monitora horizontalmente as áreas que ultrapassam seu bitmap.</param>
void CarenD2D1BitmapBrush1::SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ExtendModeX)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetExtendModeX(ConverterPara<D2D1_EXTEND_MODE>(Param_ExtendModeX));
}

/// <summary>
/// Especifica como o Brush ladrilhou(Tiled) verticalmente as áreas que se estendem além de seu bitmap.
/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
/// vertical(SetExtendModeY) para determinar como preencher a área restante.
/// </summary>
/// <param name="Param_ExtendModeY">Um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
void CarenD2D1BitmapBrush1::SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ExtendModeY)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetExtendModeY(ConverterPara<D2D1_EXTEND_MODE>(Param_ExtendModeY));
}

/// <summary>
/// Especifica o modo de interpolação usado quando o bitmap da escova é dimensionado ou girado.
/// D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR representa a filtragem do vizinho mais próximo. Ele olha o pixel bitmap mais próximo do pixel de renderização atual e escolhe sua cor exata.
/// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR representa filtragem linear e interpola uma cor dos quatro pixels de bitmap mais próximos.
/// O modo de interpolação de um bitmap também afeta traduções subpixel. Em uma tradução subpixel, a interpolação bilinear posiciona o bitmap mais precisamente às solicitações do aplicativo, mas desfoca o bitmap no processo.
/// </summary>
/// <param name="Param_InterpolationMode">O modo de interpolação usado quando o bitmap do Brush é dimensionado ou girado.</param>
void CarenD2D1BitmapBrush1::SetInterpolationMode(CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetInterpolationMode(ConverterPara<D2D1_BITMAP_INTERPOLATION_MODE>(Param_InterpolationMode));
}



// Métodos da interface (ICarenD2D1Brush)


/// <summary>
/// Obtém o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1BitmapBrush1::GetOpacity([Out] float% Param_Out_Opacidade)
{
	//Chama o método para realizar a operação e define no parametro de saida.
	Param_Out_Opacidade = PonteiroTrabalho->GetOpacity();
}

/// <summary>
/// A transformação é aplicada a este pincel.
/// </summary>
/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
void CarenD2D1BitmapBrush1::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
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
void CarenD2D1BitmapBrush1::SetOpacity(float Param_Opacidade)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetOpacity(Param_Opacidade);
}

/// <summary>
/// Define a transformação aplicada ao pincel.
/// </summary>
/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
void CarenD2D1BitmapBrush1::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
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
void CarenD2D1BitmapBrush1::GetFactory(ICaren^ Param_Out_Factory)
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