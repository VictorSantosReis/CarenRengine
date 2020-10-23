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


public ref class CarenTeste
{
public:
	BOOL AtivarSleep = FALSE;
	delegate CarenResult Delegate_Metodo_B(int x);
	Delegate_Metodo_B^ CallbackTeste = nullptr;

	void TesteMatrizIrregular(cli::array<cli::array<float>^>^ Param_MatrizJagged);
	void TesteMetodosTempo();
	void TesteRetornos(String^ Nome, Int32% Param_Ref_Valor, ICaren^ Param_Out_Interface)
	{
		
	}
	void TesteResultCodeState([Out] ResultCode% Param_Out_Status, [Out] bool% Param_Out_ResultadoGeral)
	{
	}
	void RegistrarMetodo(Object^ Param_InstanciaClasse, System::Reflection::MethodInfo^ Param_InfoMetodo)
	{
		CallbackTeste = static_cast<Delegate_Metodo_B^>(Delegate::CreateDelegate(Delegate_Metodo_B::typeid, Param_InstanciaClasse, Param_InfoMetodo));
	
	}
	void ChamarMetodo(int Valor)
	{
		CarenResult Result = CallbackTeste(Valor);
	}
};


public interface class ICarenBrother
{
	generic<typename T>
		void TestarMetodo(T Param_Index, UInt32 Param_Valor);

		generic<typename T, typename U>
			void TestarMetodo(T Param_Index, U% Param_Ref_valor);
};

/// <summary>
/// Testes de modelos genericos.
/// </summary>
public ref class CarenBrother : ICarenBrother
{
public:
	generic<typename T>
		virtual void TestarMetodo(T Param_Index, UInt32 Param_Valor)
		{
			
		}


	generic<typename T, typename U>
		virtual	void TestarMetodo(T Param_Index, U% Param_Ref_valor)
		{
			String^ s = gcnew String("Victor Reis :)");
			Param_Ref_valor = U(s);
		}
};