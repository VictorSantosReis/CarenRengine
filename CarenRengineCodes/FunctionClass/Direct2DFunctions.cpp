#include "../pch.h"
#include "Direct2DFunctions.h"

float Direct2DFunctions::_D2D1ComputeMaximumScaleFactor(CA_D2D1_MATRIX_3X2_F^ Param_Matrix)
{
    //Resultado retornado
    float Resultado = 0.0f;

    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_MATRIX_3X2_F* vi_pMatrix = Nulo;

    //Converte a estrutura gerenciada para a nativa.
    vi_pMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Matrix);

    //Realiza a operaçăo.
    Resultado = D2D1ComputeMaximumScaleFactor(const_cast<D2D1_MATRIX_3X2_F*>(vi_pMatrix));

    //Libera a memória utilizada pela estrutura.
    DeletarEstruturaSafe(&vi_pMatrix);

    //Retorna o resultado.
    return Resultado;
}

Boolean Direct2DFunctions::_D2D1InvertMatrix(CA_D2D1_MATRIX_3X2_F^% Param_Ref_Matrix)
{
    //Resultado retornado
    Boolean Resultado = false;

    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_MATRIX_3X2_F* vi_pInOutMatrix = Nulo; //Entrada e Saida.

    //Converte a estrutura gerenciada para a nativa.
    vi_pInOutMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Ref_Matrix);

    //Realiza a operaçăo.
    Resultado = static_cast<Boolean>(D2D1InvertMatrix(vi_pInOutMatrix));

    //Verifica se teve sucesso e define na matrix de referencia do parametro.
    if (Resultado)
        Param_Ref_Matrix = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(vi_pInOutMatrix);

    //Libera a memória utilizada pela estrutura.
    DeletarEstruturaSafe(&vi_pInOutMatrix);

    //Retorna o resultado.
    return Resultado;
}

Boolean Direct2DFunctions::_D2D1IsMatrixInvertible(CA_D2D1_MATRIX_3X2_F^ Param_Matrix)
{
    //Resultado retornado
    BOOL Resultado = FALSE;

    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_MATRIX_3X2_F* vi_pMatrix = Nulo;

    //Converte a estrutura gerenciada para a nativa.
    vi_pMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Matrix);

    //Realiza a operaçăo.
    Resultado = static_cast<Boolean>(D2D1IsMatrixInvertible(vi_pMatrix));

    //Libera a memória utilizada pela estrutura.
    DeletarEstruturaSafe(&vi_pMatrix);

    //Retorna o resultado.
    return Resultado;
}

void Direct2DFunctions::_D2D1MakeRotateMatrix(
    float Param_Angulo, 
    CA_D2D1_POINT_2F^ Param_Center, 
    OutParam CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
{
    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_POINT_2F* vi_pPointCenter = Nulo;
    D2D1_MATRIX_3X2_F *vi_pOutMatrix = CriarEstrutura<D2D1_MATRIX_3X2_F>(); //Aloca memória para a Matrix.

    //Converte a estrutura de ponto.
    vi_pPointCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

    //Realiza a operaçăo.
    D2D1MakeRotateMatrix(Param_Angulo, *vi_pPointCenter, vi_pOutMatrix);

    //Converte a estrutura nativa para a gerenciada e define no parametro de saida.
    Param_Out_Matrix = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(vi_pOutMatrix);

    //Libera a memória utilizada pelas estruturas.
    DeletarEstruturaSafe(&vi_pPointCenter);
    DeletarEstruturaSafe(&vi_pOutMatrix);
}

void Direct2DFunctions::_D2D1MakeSkewMatrix(
    float Param_AnguloX, 
    float Param_AnguloY, 
    CA_D2D1_POINT_2F^ Param_Center, 
    OutParam CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
{
    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_POINT_2F* vi_pPointCenter = Nulo;
    D2D1_MATRIX_3X2_F *vi_pOutMatrix = CriarEstrutura<D2D1_MATRIX_3X2_F>(); //Aloca memória para a Matrix.

    //Converte a estrutura de ponto.
    vi_pPointCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

    //Realiza a operaçăo.
    D2D1MakeSkewMatrix(Param_AnguloX, Param_AnguloY, *vi_pPointCenter, vi_pOutMatrix);

    //Converte a estrutura nativa para a gerenciada e define no parametro de saida.
    Param_Out_Matrix = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(vi_pOutMatrix);

    //Libera a memória utilizada pelas estruturas.
    DeletarEstruturaSafe(&vi_pPointCenter);
    DeletarEstruturaSafe(&vi_pOutMatrix);
}

CA_D2D1_COLOR_F^ Direct2DFunctions::_D2D1ConvertColorSpace(
    CA_D2D1_COLOR_SPACE Param_SourceColorSpace, 
    CA_D2D1_COLOR_SPACE Param_DestinationColorSpace, 
    CA_D2D1_COLOR_F^ Param_Color)
{
    //Resultado retornado
    CA_D2D1_COLOR_F^ Resultado = nullptr;

    //Variaveis a serem utilizadas.
    Utilidades Util;
    D2D1_COLOR_F* vi_pColor = Nulo;
    D2D1_COLOR_F vi_OutColor = { 0 };

    //Converte a estrutura com a cor de destino.
    vi_pColor = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Color);

    //Realiza a operaçăo.
    vi_OutColor = D2D1ConvertColorSpace(
        static_cast<D2D1_COLOR_SPACE>(Param_SourceColorSpace),
        static_cast<D2D1_COLOR_SPACE>(Param_DestinationColorSpace),
        const_cast<D2D1_COLOR_F*>(vi_pColor));

    //Converte a estrutura criada para a gerenciada.
    Resultado = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&vi_OutColor);

    //Libera a memória utilizada pela estrutura.
    DeletarEstruturaSafe(&vi_pColor);

    //Retorna o resultado.
    return Resultado;
}

void Direct2DFunctions::_D2D1SinCos(
    float Param_Angulo, 
    OutParam float% Param_Out_Seno, 
    OutParam float% Param_Out_Cosseno)
{
    //Variaveis a serem utilizadas.
    float vi_OutSeno = 0.0f, vi_OutCosseno = 0.0f;

    //Realiza a operaçăo.
    D2D1SinCos(Param_Angulo, &vi_OutSeno, &vi_OutCosseno);

    //Define os dados nos parametros de saida.
    Param_Out_Seno = vi_OutSeno;
    Param_Out_Cosseno = vi_OutCosseno;
}

float Direct2DFunctions::_D2D1Tan(float Param_Angulo)
{
    //Realiza a operaçăo e retorna.
    return D2D1Tan(Param_Angulo);
}

float Direct2DFunctions::_D2D1Vec3Length(float Param_X, float Param_Y, float Param_Z)
{
    //Realiza a operaçăo e retorna.
    return D2D1Vec3Length(Param_X, Param_Y, Param_Z);
}
