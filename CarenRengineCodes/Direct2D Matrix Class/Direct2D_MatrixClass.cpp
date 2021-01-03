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
#include "Direct2D_MatrixClass.h"

//Adiciona o namespace do Direct2D.
using namespace CarenRengine::Direct2D;





// CLASSE -> CarenMatrix3x2F


//Métodos auxiliares.

CA_D2D1_MATRIX_3X2_F^ CarenRengine::Direct2D::CarenMatrix3x2F::ToStruct()
{
	//Variavel que vai retornar o resultado.
	CA_D2D1_MATRIX_3X2_F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* vi_pMatrixAtual = Nulo;

	//Realiza a operação.
	vi_pMatrixAtual = reinterpret_cast<D2D1_MATRIX_3X2_F*>(PonteiroTrabalho);

	//Converte a estrutura para a gerenciada
	Resultado = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(vi_pMatrixAtual);

	//Retorna o resultado
	return Resultado;
}

D2D1::Matrix3x2F* CarenRengine::Direct2D::CarenMatrix3x2F::GetNativeClass()
{
	//Retorna a classe nativa atual.
	return PonteiroTrabalho;
}



//Métodos da classe original.

float CarenRengine::Direct2D::CarenMatrix3x2F::Determinant()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->Determinant();
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Identity()
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Identity();

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

Boolean CarenRengine::Direct2D::CarenMatrix3x2F::Invert()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->Invert();
}

Boolean CarenRengine::Direct2D::CarenMatrix3x2F::IsIdentity()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->IsIdentity();
}

Boolean CarenRengine::Direct2D::CarenMatrix3x2F::IsInvertible()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->IsInvertible();
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Rotation(
	float Param_Angulo, 
	CA_D2D1_POINT_2F^ Param_Center)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;
	D2D1_POINT_2F* vi_pCenter = Nulo;

	//Converte a estrutura gerenciada para a nativa.
	vi_pCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Rotation(Param_Angulo, *vi_pCenter);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pCenter);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Scale(
	CA_D2D1_SIZE_F^ Param_Size,
	CA_D2D1_POINT_2F^ Param_Center)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;
	D2D1_SIZE_F* vi_pSize = Nulo;
	D2D1_POINT_2F* vi_pCenter = Nulo;

	//Converte as estruturas.
	vi_pSize = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_Size);
	vi_pCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Scale(*vi_pSize, *vi_pCenter);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pSize);
	DeletarEstruturaSafe(&vi_pCenter);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Scale(
	float Param_X,
	float Param_Y, 
	CA_D2D1_POINT_2F^ Param_Center)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;
	D2D1_POINT_2F* vi_pCenter = Nulo;

	//Converte a estrutura de ponto.
	vi_pCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Scale(Param_X, Param_Y, *vi_pCenter);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pCenter);

	//Retorna o resultado
	return Resultado;
}

void CarenRengine::Direct2D::CarenMatrix3x2F::SetProduct(
	CarenMatrix3x2F^ Param_A, 
	CarenMatrix3x2F^ Param_B)
{
	//Realiza a operação.
	PonteiroTrabalho->SetProduct(const_cast<D2D1::Matrix3x2F&>(*Param_A->GetNativeClass()), const_cast<D2D1::Matrix3x2F&>(*Param_B->GetNativeClass()));
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Skew(
	float Param_AnguloX, 
	float Param_AnguloY, 
	CA_D2D1_POINT_2F^ Param_Center)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;
	D2D1_POINT_2F* vi_pCenter = Nulo;

	//Converte a estrutura de ponto.
	vi_pCenter = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Skew(Param_AnguloX, Param_AnguloY, *vi_pCenter);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pCenter);

	//Retorna o resultado
	return Resultado;
}

CA_D2D1_POINT_2F^ CarenRengine::Direct2D::CarenMatrix3x2F::TransformPoint(CA_D2D1_POINT_2F^ Param_Point)
{
	//Variavel que vai retornar o resultado.
	CA_D2D1_POINT_2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* vi_pPoint = Nulo;
	D2D1_POINT_2F vi_OutPoint = { 0 };

	//Converte a estrutura de ponto.
	vi_pPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point);

	//Realiza a operação.
	vi_OutPoint = PonteiroTrabalho->TransformPoint(*vi_pPoint);

	//Converte a estrutura nativa para a gerenciada.
	Resultado = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&vi_OutPoint);

	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&vi_pPoint);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Translation(CA_D2D1_SIZE_F^ Param_Size)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;
	D2D1_SIZE_F* vi_pSize = Nulo;

	//Converte a estrutura de ponto.
	vi_pSize = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_Size);

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Translation(*vi_pSize);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pSize);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix3x2F^ CarenRengine::Direct2D::CarenMatrix3x2F::Translation(
	float Param_X, 
	float Param_Y)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix3x2F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix3x2F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Translation(Param_X, Param_Y);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix3x2F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}





// CLASSE -> CarenMatrix4x4F


//Métodos auxiliares.

CA_D2D1_MATRIX_4X4_F^ CarenRengine::Direct2D::CarenMatrix4x4F::ToStruct()
{
	throw gcnew System::NotImplementedException();
	// TODO: inserir instrução return aqui
}

D2D1::Matrix4x4F* CarenRengine::Direct2D::CarenMatrix4x4F::GetNativeClass()
{
	return nullptr;
}



//Métodos da classe original.

float CarenRengine::Direct2D::CarenMatrix4x4F::Determinant()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->Determinant();
}

Boolean CarenRengine::Direct2D::CarenMatrix4x4F::IsIdentity()
{
	//Realiza a operação e retorna o resultado.
	return PonteiroTrabalho->IsIdentity();
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::PerspectiveProjection(float Param_Depth)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->PerspectiveProjection(Param_Depth);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::RotationArbitraryAxis(
	float Param_X,
	float Param_Y,
	float Param_Z,
	float Param_Degree)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->RotationArbitraryAxis(Param_X, Param_Y, Param_Z, Param_Degree);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::RotationX(float Param_DegreeX)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->RotationX(Param_DegreeX);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::RotationY(float Param_DegreeY)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->RotationY(Param_DegreeY);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::RotationZ(float Param_DegreeZ)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->RotationZ(Param_DegreeZ);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::Scale(
	float Param_X, 
	float Param_Y, 
	float Param_Z)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->Scale(Param_X, Param_Y, Param_Z);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

void CarenRengine::Direct2D::CarenMatrix4x4F::SetProduct(
	CarenMatrix4x4F^ Param_A, 
	CarenMatrix4x4F^ Param_B)
{
	//Realiza a operação.
	PonteiroTrabalho->SetProduct(const_cast<D2D1::Matrix4x4F&>(*Param_A->GetNativeClass()), const_cast<D2D1::Matrix4x4F&>(*Param_B->GetNativeClass()));
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::SkewX(float Param_DegreeX)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->SkewX(Param_DegreeX);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}

CarenMatrix4x4F^ CarenRengine::Direct2D::CarenMatrix4x4F::SkewY(float Param_DegreeY)
{
	//Variavel que vai retornar o resultado.
	CarenMatrix4x4F^ Resultado = nullptr;

	//Variaveis utilizadas.
	Utilidades Util;
	D2D1::Matrix4x4F vi_OutMatrix;

	//Realiza a operação.
	vi_OutMatrix = PonteiroTrabalho->SkewY(Param_DegreeY);

	//Cria e define a classe gerada no resultado a ser retornado.
	Resultado = gcnew CarenMatrix4x4F(vi_OutMatrix);

	//Retorna o resultado
	return Resultado;
}