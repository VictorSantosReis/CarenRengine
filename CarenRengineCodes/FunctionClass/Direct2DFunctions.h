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


#pragma once
#include "../SDK_Base.h"
#include "../SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

/// <summary>
/// Classe responsável por conter funções nativas auxiliares da biblioteca da Api do Direct2D.
/// </summary>
public ref class Direct2DFunctions
{
	//Construtor & Destruidor da classe.
public:
	Direct2DFunctions() {};
	~Direct2DFunctions() {};


	//Métodos
public:
	/// <summary>
	/// Calcula o fator máximo pelo qual uma determinada transformação pode esticar qualquer vetor.
	/// </summary>
	/// <param name="Param_Matrix">A Matrix de transformação de entrada.</param>
	/// <returns></returns>
	float _D2D1ComputeMaximumScaleFactor(CA_D2D1_MATRIX_3X2_F^ Param_Matrix);

	/// <summary>
	/// Tenta inverter a Matrix especificada. Retorna TRUE se a Matrix tiver sido invertida; caso contrario, FALSE.
	/// </summary>
	/// <param name="Param_Ref_Matrix">A Matrix a ser invertida.</param>
	/// <returns></returns>
	Boolean _D2D1InvertMatrix(CA_D2D1_MATRIX_3X2_F^% Param_Ref_Matrix);

	/// <summary>
	/// Verifica se a Matrix especificada é invertível.
	/// </summary>
	/// <param name="Param_Matrix">A Matrix para verificar.</param>
	/// <returns></returns>
	Boolean _D2D1IsMatrixInvertible(CA_D2D1_MATRIX_3X2_F^ Param_Matrix);

	/// <summary>
	/// Cria uma transformação de rotação que gira pelo ângulo especificado sobre o ponto especificado.
	/// </summary>
	/// <param name="Param_Angulo">O ângulo de rotação no sentido horário, em graus.</param>
	/// <param name="Param_Center">O ponto sobre o qual girar.</param>
	/// <param name="Param_Out_Matrix">Retorna a Matrix contendo a nova transformação de rotação.</param>
	void _D2D1MakeRotateMatrix(
		float Param_Angulo, CA_D2D1_POINT_2F^ Param_Center, 
		OutParam CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix);

	/// <summary>
	/// Cria uma transformação de inclinação que tem o ângulo de eixo x especificado, ângulo do eixo y e ponto central.
	/// </summary>
	/// <param name="Param_AnguloX">O ângulo de inclinação do eixo x, que é medido em graus anti-horário do eixo y.</param>
	/// <param name="Param_AnguloY">O ângulo de inclinação do eixo y, que é medido em graus anti-horário do eixo x.</param>
	/// <param name="Param_Center">O ponto central da operação de distorção.</param>
	/// <param name="Param_Out_Matrix">Retorna a Matrix contendo a nova transformação de rotação.</param>
	void _D2D1MakeSkewMatrix(
		float Param_AnguloX, 
		float Param_AnguloY, 
		CA_D2D1_POINT_2F^ Param_Center,
		OutParam CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix);

	/// <summary>
	/// Converte a cor dada de um espaço de cor para outro.
	/// </summary>
	/// <param name="Param_SourceColorSpace">O espaço de cores de origem.</param>
	/// <param name="Param_DestinationColorSpace">O espaço de cores do destino.</param>
	/// <param name="Param_Color">A cor de origem.</param>
	/// <returns></returns>
	CA_D2D1_COLOR_F^ _D2D1ConvertColorSpace(
		CA_D2D1_COLOR_SPACE Param_SourceColorSpace, 
		CA_D2D1_COLOR_SPACE Param_DestinationColorSpace, 
		CA_D2D1_COLOR_F^ Param_Color);

	/// <summary>
	/// Retorna o seno e cosseno de um ângulo.
	/// </summary>
	/// <param name="Param_Angulo">O ângulo para calcular.</param>
	/// <param name="Param_Out_Seno">Retorna o seno do ângulo.</param>
	/// <param name="Param_Out_Cosseno">Retorna o cosseno do ângulo.</param>
	void _D2D1SinCos(
		float Param_Angulo, 
		OutParam float% Param_Out_Seno, 
		OutParam float% Param_Out_Cosseno);

	/// <summary>
	/// Retorna a tangente de um ângulo.
	/// </summary>
	/// <param name="Param_Angulo">O ângulo para calcular a tangente.</param>
	/// <returns></returns>
	float _D2D1Tan(float Param_Angulo);

	/// <summary>
	/// Retorna o comprimento de um vetor tridimensional.
	/// </summary>
	/// <param name="Param_X">O valor X do vetor.</param>
	/// <param name="Param_Y">O valor Y do vetor.</param>
	/// <param name="Param_Z">O valor Z do vetor.</param>
	/// <returns></returns>
	float _D2D1Vec3Length(
		float Param_X, 
		float Param_Y,
		float Param_Z);
};

