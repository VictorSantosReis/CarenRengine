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

#include "../Header.h"
#include "../SDK_Base.h"
#include "../SDK_Utilidades.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ESTA CLASSE IMPLEMENTA AS MATRIX (3X2F & 4X4F) QUE ESTÃO PRESENTES NA DOCUMENTAÇÃO DO (DIRECT2D) PARA AUXILIAR O USUÁRIO ///
//NAS FUNÇÕES QUE AS UTILIZAM. ESTAS CLASSES REPRESENTAM AS ESTRUTURAS (CA_D2D1_MATRIX_3X2_F & CA_D2D1_MATRIX_4X4_F).      ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace CarenRengine
{
	namespace Direct2D
	{
		/// <summary>
		/// A classe Matrix3x2F representa uma matriz 3 por 2 e fornece métodos de conveniência para a criação de matrizes(Matrix).
		/// </summary>
		public ref class CarenMatrix3x2F
		{
			//Ponteiro para a Matrix atual
			D2D1::Matrix3x2F* PonteiroTrabalho = Nulo;

			//Construtor & Destruidor
		public:
			/// <summary>
			/// Inicializa e cria a classe como uma Matrix Vazia.
			/// </summary>
			CarenMatrix3x2F()
			{
				//Cria uma Matrix vazia.
				PonteiroTrabalho = new D2D1::Matrix3x2F();
			};

			/// <summary>
			/// Inicializa a classe derivada de uma estrutura gerenciada.
			/// </summary>
			/// <param name="Param_Matrix">Uma Matrix gerenciada para associar a esta classe.</param>
			CarenMatrix3x2F(CA_D2D1_MATRIX_3X2_F^ Param_Matrix)
			{
				//Variveis utilizadas.
				Utilidades Util;
				D2D1_MATRIX_3X2_F* vi_pMatrix = Nulo;

				//Converte a estrutura
				vi_pMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Matrix);

				//Cria o ponteiro de trabalho a parti da Matrix convertida.
				PonteiroTrabalho = D2D1::Matrix3x2F::ReinterpretBaseType(vi_pMatrix);

				//Libera a memória utilizada pela Matrix
				DeletarEstruturaSafe(&vi_pMatrix);
			};

			/// <summary>
			/// (Nativo) - Inicializa a classe a parti da classe nativa representante.
			/// </summary>
			CarenMatrix3x2F(D2D1::Matrix3x2F& Param_Matrix)
			{
				//Cria o ponteiro de trabalho a parti de uma classe nativa.
				PonteiroTrabalho = new D2D1::Matrix3x2F(Param_Matrix);
			};

			~CarenMatrix3x2F() 
			{
				//Chama o Finalizador da classe.
				if (ObjetoValido(PonteiroTrabalho))
					delete PonteiroTrabalho;
			};

			//Métodos auxiliares para a classe.
		public:
			/// <summary>
			/// Retorna uma estrutura (CA_D2D1_MATRIX_3X2_F) a parti da instância atual desta classe.
			/// </summary>
			/// <returns></returns>
			CA_D2D1_MATRIX_3X2_F^ ToStruct();

			/// <summary>
			/// (Nativo) - Retorna a classe nativa (Matrix3x2F) associada a esta classe gerenciada.
			/// </summary>
			/// <returns></returns>
			D2D1::Matrix3x2F* GetNativeClass();

			//Métodos da classe original.
		public:
			/// <summary>
			/// ‎Calcula o determinante da matriz.‎
			/// </summary>
			/// <returns></returns>
			float Determinant();

			/// <summary>
			/// ‎Cria uma Matrix de identidade.‎
			/// </summary>
			CarenMatrix3x2F^ Identity();

			/// <summary>
			/// ‎Inverte a Matrix, se for invertível.‎
			/// Retorna ‎TRUE‎‎ se a Matrix foi invertida; caso contrário, ‎‎FALSE.‎
			/// </summary>
			Boolean Invert();

			/// <summary>
			/// ‎Indica se essa Matrix é a Matrix de identidade.‎
			/// Retorna ‎TRUE‎‎ se a Matrix é uma Matrix de identidade; caso contrário, ‎‎FALSE.‎
			/// </summary>
			Boolean IsIdentity();

			/// <summary>
			/// ‎Indica se a Matrix é invertível.‎
			/// Retorna ‎TRUE se a Matrix é invertível; caso contrário, FALSE.‎
			/// </summary>
			Boolean IsInvertible();

			/// <summary>
			/// ‎Cria uma transformação de rotação que tem o ângulo especificado e o ponto central.‎
			/// </summary>
			/// <param name="Param_Angulo">‎O ângulo de rotação em graus. Um ângulo positivo cria uma rotação no sentido horário, e um ângulo negativo cria uma rotação no sentido anti-horário.‎</param>
			/// <param name="Param_Center">‎O ponto sobre o qual a rotação é realizada.‎</param>
			CarenMatrix3x2F^ Rotation(
				float Param_Angulo,
				CA_D2D1_POINT_2F^ Param_Center);

			/// <summary>
			/// ‎Cria uma Scale Transform que tem os fatores de escala especificados e o ponto central.‎
			/// </summary>
			/// <param name="Param_Size">Os fatores de escala do eixo x e do eixo y da transformação da escala.</param>
			/// <param name="Param_Center">O ponto sobre o qual a escala é realizada.</param>
			CarenMatrix3x2F^ Scale(
				CA_D2D1_SIZE_F^ Param_Size,
				CA_D2D1_POINT_2F^ Param_Center);

			/// <summary>
			/// ‎Cria uma Scale Transform que tem os fatores de escala especificados e o ponto central.‎
			/// </summary>
			/// <param name="Param_X">O fator de escala do eixo x da transformação da escala.</param>
			/// <param name="Param_Y">O fator de escala do eixo y da transformação da escala.</param>
			/// <param name="Param_Center">O ponto sobre o qual a escala é realizada.</param>
			CarenMatrix3x2F^ Scale(
				float Param_X,
				float Param_Y,
				CA_D2D1_POINT_2F^ Param_Center);

			/// <summary>
			/// ‎Multiplica as duas Matrix e armazena o resultado nesta Matrix.‎
			/// </summary>
			/// <param name="Param_A">A primeira Matrix a se multiplicar.</param>
			/// <param name="Param_B">A segunda Matrix a se multiplicar.</param>
			void SetProduct(
				CarenMatrix3x2F^ Param_A,
				CarenMatrix3x2F^ Param_B);

			/// <summary>
			/// Cria uma Skew Transform(Transformação de distorção) que tem os valores especificados do eixo x e do eixo y e ponto central.
			/// </summary>
			/// <param name="Param_AnguloX">O ângulo de inclinação do eixo x, que é medido em graus anti-horário do eixo y.</param>
			/// <param name="Param_AnguloY">O ângulo de inclinação do eixo y, que é medido em graus no sentido horário a partir do eixo x.</param>
			/// <param name="Param_Center">O ponto sobre o qual o Skew(Distorção) é realizada.</param>
			CarenMatrix3x2F^ Skew(
				float Param_AnguloX,
				float Param_AnguloY,
				CA_D2D1_POINT_2F^ Param_Center);

			/// <summary>
			/// Usa essa Matrix para transformar o ponto especificado e retorna o resultado.
			/// </summary>
			/// <param name="Param_Point"></param>
			CA_D2D1_POINT_2F^ TransformPoint(CA_D2D1_POINT_2F^ Param_Point);

			/// <summary>
			/// Cria uma Translation Transform(Transformação de Translação - Transladar) que tem os deslocamentos especificados x e y.
			/// </summary>
			/// <param name="Param_Size">A distância para transladar ao longo do eixo x e do eixo y.</param>
			CarenMatrix3x2F^ Translation(CA_D2D1_SIZE_F^ Param_Size);

			/// <summary>
			/// Cria uma Translation Transform(Transformação de Translação - Transladar) que tem os deslocamentos especificados x e y.
			/// </summary>
			/// <param name="Param_X">>A distância para transladar ao longo do eixo x.</param>
			/// <param name="Param_Y">>A distância para transladar ao longo do eixo y.</param>
			CarenMatrix3x2F^ Translation(
				float Param_X,
				float Param_Y);
		};

		/// <summary>
		/// A classe Matrix4x4F representa uma matriz 4 por 4 e fornece métodos de conveniência para a criação de matrizes(Matrix).
		/// </summary>
		public ref class CarenMatrix4x4F
		{
			//Ponteiro para a Matrix atual
			D2D1::Matrix4x4F* PonteiroTrabalho = Nulo;

			//Construtor & Destruidor
		public:
			/// <summary>
			/// Inicializa e cria a classe como uma Matrix Vazia.
			/// </summary>
			CarenMatrix4x4F()
			{
				//Cria uma Matrix vazia.
				PonteiroTrabalho = new D2D1::Matrix4x4F();
			};

			/// <summary>
			/// Inicializa a classe derivada de uma estrutura gerenciada.
			/// </summary>
			/// <param name="Param_Matrix">Uma Matrix gerenciada para associar a esta classe.</param>
			CarenMatrix4x4F(CA_D2D1_MATRIX_4X4_F^ Param_Matrix)
			{
				//Variveis utilizadas.
				Utilidades Util;
				D2D1_MATRIX_4X4_F* vi_pMatrix = Nulo;

				//Converte a estrutura
				vi_pMatrix = Util.ConverterD2D1_MATRIX_4X4_FManagedToUnmanaged(Param_Matrix);

				//Cria o ponteiro de trabalho a parti da Matrix convertida.
				PonteiroTrabalho = D2D1::Matrix4x4F::ReinterpretBaseType(vi_pMatrix);

				//Libera a memória utilizada pela Matrix
				DeletarEstruturaSafe(&vi_pMatrix);
			};

			/// <summary>
			/// (Nativo) - Inicializa a classe a parti da classe nativa representante.
			/// </summary>
			CarenMatrix4x4F(D2D1::Matrix4x4F& Param_Matrix)
			{
				//Cria o ponteiro de trabalho a parti de uma classe nativa.
				PonteiroTrabalho = new D2D1::Matrix4x4F(Param_Matrix);
			};

			~CarenMatrix4x4F()
			{
				//Chama o Finalizador da classe.
				if (ObjetoValido(PonteiroTrabalho))
					delete PonteiroTrabalho;
			};

			//Métodos auxiliares para a classe.
		public:
			/// <summary>
			/// Retorna uma estrutura (CA_D2D1_MATRIX_4X4_F) a parti da instância atual desta classe.
			/// </summary>
			/// <returns></returns>
			CA_D2D1_MATRIX_4X4_F^ ToStruct();

			/// <summary>
			/// (Nativo) - Retorna a classe nativa (Matrix4x4F) associada a esta classe gerenciada.
			/// </summary>
			/// <returns></returns>
			D2D1::Matrix4x4F* GetNativeClass();

			//Métodos da classe original.
		public:
			/// <summary>
			/// Calcula o determinante da Matrix.
			/// </summary>
			float Determinant();

			/// <summary>
			/// Indica se essa Matrix é a Matrix de identidade.
			/// </summary>
			Boolean IsIdentity();

			/// <summary>
			/// Uma Perspective Transform(Transformação de Perspectiva) dado um valor de profundidade(Depth).
			/// </summary>
			/// <param name="Param_Depth">O depth(profundidade) para a Perspective Transform.</param>
			CarenMatrix4x4F^ PerspectiveProjection(float Param_Depth);

			/// <summary>
			/// Determina a Matrix de rotação 3D para um eixo arbitrário.
			/// </summary>
			/// <param name="Param_X">O ponto X do eixo.</param>
			/// <param name="Param_Y">O ponto Y do eixo.</param>
			/// <param name="Param_Z">O ponto Z do eixo.</param>
			/// <param name="Param_Degree">A quantidade de rotação.</param>
			CarenMatrix4x4F^ RotationArbitraryAxis(
				float Param_X,
				float Param_Y,
				float Param_Z,
				float Param_Degree);

			/// <summary>
			/// Rotaciona a Matrix de transformação ao redor do eixo X.
			/// </summary>
			/// <param name="Param_DegreeX">A quantidade de rotação.</param>
			CarenMatrix4x4F^ RotationX(float Param_DegreeX);

			/// <summary>
			/// Rotaciona a Matrix de transformação ao redor do eixo Y.
			/// </summary>
			/// <param name="Param_DegreeY">A quantidade de rotação.</param>
			CarenMatrix4x4F^ RotationY(float Param_DegreeY);

			/// <summary>
			/// Rotaciona a Matrix de transformação ao redor do eixo Z.
			/// </summary>
			/// <param name="Param_DegreeZ">A quantidade de rotação.</param>
			CarenMatrix4x4F^ RotationZ(float Param_DegreeZ);

			/// <summary>
			/// Escala o plano de perspectiva da Matrix.
			/// </summary>
			/// <param name="Param_X">A escala na direção X.</param>
			/// <param name="Param_Y">A escala na direção Y.</param>
			/// <param name="Param_Z">A escala na direção Z.</param>
			CarenMatrix4x4F^ Scale(
				float Param_X,
				float Param_Y,
				float Param_Z);

			/// <summary>
			/// Multiplica duas Matrix e armazena o resultado nesta Matrix.
			/// </summary>
			/// <param name="Param_A">A primeira Matrix a se multiplicar.</param>
			/// <param name="Param_B">A segunda Matrix a se multiplicar.</param>
			void SetProduct(
				CarenMatrix4x4F^ Param_A,
				CarenMatrix4x4F^ Param_B);

			/// <summary>
			/// Distorce a Matrix na direção X.
			/// </summary>
			/// <param name="Param_DegreeX">A quantidade de distorção.</param>
			CarenMatrix4x4F^ SkewX(float Param_DegreeX);

			/// <summary>
			/// Distorce a Matrix na direção Y.
			/// </summary>
			/// <param name="Param_DegreeY">A quantidade de distorção.</param>
			CarenMatrix4x4F^ SkewY(float Param_DegreeY);
		};
	}
}