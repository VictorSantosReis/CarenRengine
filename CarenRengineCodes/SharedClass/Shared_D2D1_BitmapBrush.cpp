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

//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D2D1BitmapBrush)


// Métodos da interface (ICarenD2D1BitmapBrush1)


/// <summary>
/// Retorna o modo de interpolação atual do pincel.
/// </summary>
/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação atual.</param>
void Shared_D2D1BitmapBrush::GetInterpolationMode1(
	ID2D1BitmapBrush1* Param_MyPointerWork, 
	[Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolationMode)
{
	//Variaveis a serem utilizadas.
	D2D1_INTERPOLATION_MODE OutInterPolationMode;

	//Chama o método para realizar a operação.
	OutInterPolationMode = Param_MyPointerWork->GetInterpolationMode1();

	//Converte e define no parametro de saida.
	Param_Out_InterpolationMode = ConverterPara<CA_D2D1_INTERPOLATION_MODE>(OutInterPolationMode);
}

/// <summary>
/// Define o modo de interpolação para o pincel.
/// </summary>
/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado.</param>
void Shared_D2D1BitmapBrush::SetInterpolationMode1(
	ID2D1BitmapBrush1* Param_MyPointerWork, 
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode)
{
	//Chama o método para realizar a operação.
	Param_MyPointerWork->SetInterpolationMode1(ConverterPara<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode));
}



// Métodos da interface (ICarenD2D1BitmapBrush)


/// <summary>
/// Obtém a fonte bitmap que este pincel usa para pintar.
/// </summary>
/// <param name="Param_Out_Bitmap">Quando este método retorna, contém o endereço a um ponteiro para o bitmap com o qual este pincel pinta.</param>
CarenResult Shared_D2D1BitmapBrush::GetBitmap(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmapBrush = NULL;

	//Chama o método para realizar a operação.
	Param_MyPointerWork->GetBitmap(&pBitmapBrush);

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
void Shared_D2D1BitmapBrush::GetExtendModeX(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	[Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = Param_MyPointerWork->GetExtendModeX();

	//Converte e define no parametro de saida.
	Param_Out_ExtendModeX = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém o método pelo qual a escova corta verticalmente as áreas que se estendem além de seu bitmap.
/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
/// </summary>
/// <param name="Param_Out_ExtendModeY">Retorna um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
void Shared_D2D1BitmapBrush::GetExtendModeY(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	[Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = Param_MyPointerWork->GetExtendModeY();

	//Converte e define no parametro de saida.
	Param_Out_ExtendModeY = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém o método de interpolação usado quando o bitmap da escova é dimensionado ou girado.
/// </summary>
/// <param name="Param_Out_InterpolationMode">Retorna o método de interpolação utilizado quando o bitmap da escova é dimensionado ou girado.</param>
void Shared_D2D1BitmapBrush::GetInterpolationMode(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	[Out] CA_D2D1_BITMAP_INTERPOLATION_MODE% Param_Out_InterpolationMode)
{
	//Variaveis a serem utilizadas.
	D2D1_BITMAP_INTERPOLATION_MODE OutInterPolationMode;

	//Chama o método para realizar a operação.
	OutInterPolationMode = Param_MyPointerWork->GetInterpolationMode();

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
CarenResult Shared_D2D1BitmapBrush::SetBitmap(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	ICarenD2D1Bitmap^ Param_Bitmap)
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
	Param_MyPointerWork->SetBitmap(pBitmap);

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
void Shared_D2D1BitmapBrush::SetExtendModeX(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	CA_D2D1_EXTEND_MODE Param_ExtendModeX)
{
	//Chama o método para realizar a operação.
	Param_MyPointerWork->SetExtendModeX(ConverterPara<D2D1_EXTEND_MODE>(Param_ExtendModeX));
}

/// <summary>
/// Especifica como o Brush ladrilhou(Tiled) verticalmente as áreas que se estendem além de seu bitmap.
/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
/// vertical(SetExtendModeY) para determinar como preencher a área restante.
/// </summary>
/// <param name="Param_ExtendModeY">Um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
void Shared_D2D1BitmapBrush::SetExtendModeY(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	CA_D2D1_EXTEND_MODE Param_ExtendModeY)
{
	//Chama o método para realizar a operação.
	Param_MyPointerWork->SetExtendModeY(ConverterPara<D2D1_EXTEND_MODE>(Param_ExtendModeY));
}

/// <summary>
/// Especifica o modo de interpolação usado quando o bitmap da escova é dimensionado ou girado.
/// D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR representa a filtragem do vizinho mais próximo. Ele olha o pixel bitmap mais próximo do pixel de renderização atual e escolhe sua cor exata.
/// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR representa filtragem linear e interpola uma cor dos quatro pixels de bitmap mais próximos.
/// O modo de interpolação de um bitmap também afeta traduções subpixel. Em uma tradução subpixel, a interpolação bilinear posiciona o bitmap mais precisamente às solicitações do aplicativo, mas desfoca o bitmap no processo.
/// </summary>
/// <param name="Param_InterpolationMode">O modo de interpolação usado quando o bitmap do Brush é dimensionado ou girado.</param>
void Shared_D2D1BitmapBrush::SetInterpolationMode(
	ID2D1BitmapBrush* Param_MyPointerWork, 
	CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode)
{
	//Chama o método para realizar a operação.
	Param_MyPointerWork->SetInterpolationMode(ConverterPara<D2D1_BITMAP_INTERPOLATION_MODE>(Param_InterpolationMode));
}