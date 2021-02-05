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
#include "WindowsFunctions.h"

String^ WindowsFunctions::HResultMensagem(UInt32 Param_HResultCode)
{
	//Variavel que vai conter a mensagem.
	LPCTSTR MensagemHResult = NULL;;
	String^ MsgHResult = "";

	//Variavel que vai ser utilizada para obter a mensagem.
	_com_error Err = (Param_HResultCode);

	//Verifica se existe algum erro
	if (Param_HResultCode == 0)
	{
		//Sai do método.
		goto Done;
	}

	//Obtém a mensagem de erro.
	MensagemHResult = Err.ErrorMessage();

	//Verifica se é valida
	if (MensagemHResult != NULL)
	{
		//Define a mensagem de retorno.
		MsgHResult = gcnew String(MensagemHResult);
	}
	else
	{
		//Mensagem não disponivel.
	}

Done:;
	//Retorna o resultado.
	return MsgHResult;
}

UInt32 WindowsFunctions::ObterUltimoCodigoErro()
{
	//Retorna o Ultimo código de erro.
	return GetLastError();
}

IntPtr WindowsFunctions::_AvSetMmThreadCharacteristicsW(String^ Param_NameTask, OutParam UInt32% Param_Out_TaskIndex)
{
	//Variavel a ser retornada.
	HANDLE vi_Handle = Nulo;

	//Variaveis utilizadas.
	DWORD vi_OutTaskIndex = 0;
	LPWSTR vi_pNomeTask = Nulo;

	//Verfica se a String não é invalida ou vazia.
	if (!StringObjetoValido(Param_NameTask))
		throw gcnew NullReferenceException("O parametro (Param_NameTask) não pode ser NULO!");
	
	//Converte o nome gerenciada para o nativo.
	vi_pNomeTask = static_cast<LPWSTR>(Marshal::StringToCoTaskMemUni(Param_NameTask).ToPointer());

	//Chama o método.
	vi_Handle = AvSetMmThreadCharacteristicsW(vi_pNomeTask, &vi_OutTaskIndex);

	//Define o Id da task no parametro de saida.
	Param_Out_TaskIndex = static_cast<UInt32>(vi_OutTaskIndex);

	//Libera a memória utilizada pela string.
	Marshal::FreeCoTaskMem(IntPtr(vi_pNomeTask));

	//Retorna a handle.
	return ObjetoValido(vi_Handle)? IntPtr(vi_Handle): DefaultGenPointer;
}

Boolean WindowsFunctions::_AvRevertMmThreadCharacteristics(IntPtr Param_Handle)
{
	//Chama o método para realizar a função. 
	return AvRevertMmThreadCharacteristics(Param_Handle.ToPointer())? true: false;
}

void WindowsFunctions::SleepNativo(UInt32 Param_Sleep)
{
	Sleep(Param_Sleep);
}

void WindowsFunctions::SleepNativoChrono_MicroSeconds(UInt32 Param_Sleep)
{
	std::this_thread::sleep_for(std::chrono::microseconds(Param_Sleep));
}

void WindowsFunctions::SleepNativoChrono_Miliseconds(UInt32 Param_Sleep)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(Param_Sleep));
}

CarenResult WindowsFunctions::_TimeBeginPeriod(UInt32 Param_Periodo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	MMRESULT Hr = timeBeginPeriod(Param_Periodo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}

CarenResult WindowsFunctions::_TimeEndPeriod(UInt32 Param_Periodo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	MMRESULT Hr = timeEndPeriod(Param_Periodo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}

CarenResult WindowsFunctions::_TimeGetDevCaps([Out] UInt32% Param_Out_PeriodoMinimo, [Out] UInt32% Param_Out_PeriodoMaximo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	TIMECAPS TimeStruct = { 0 };

	//Chama o método para realizar a operação.
	MMRESULT Hr = timeGetDevCaps(&TimeStruct, sizeof(TimeStruct));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os valores nos parametros de saida.
	Param_Out_PeriodoMinimo = TimeStruct.wPeriodMin;
	Param_Out_PeriodoMaximo = TimeStruct.wPeriodMax;

Done:;
	//Retorna o resultado
	return Resultado;
}

Boolean WindowsFunctions::_QueryPerformanceCounter([Out] Int64% Param_OutPerformanceCounter)
{
	//Variavel que vai definir o resultado.
	BOOLEAN Resultado = FALSE;

	//Define a estrutura que vai receber os dados.
	LARGE_INTEGER DadosPerformance = { 0 };

	//Chama o método para recuperar os dados.
	Resultado = QueryPerformanceCounter(&DadosPerformance);

	//Verifica o resultado
	if (Resultado)
	{
		//Define os dados no parametro de saida.
		Param_OutPerformanceCounter = static_cast<Int64>(DadosPerformance.QuadPart);
	}

	//Retorna o resultado da função.
	return Resultado;
}

Boolean WindowsFunctions::_QueryPerformanceFrequency([Out] Int64% Param_OutFrequency)
{
	//Variavel que vai definir o resultado.
	BOOLEAN Resultado = FALSE;

	//Define a estrutura que vai receber os dados.
	LARGE_INTEGER DadosPerformance = { 0 };

	//Chama o método para recuperar os dados.
	Resultado = QueryPerformanceFrequency(&DadosPerformance);

	//Verifica o resultado
	if (Resultado)
	{
		//Define os dados no parametro de saida.
		Param_OutFrequency = static_cast<Int64>(DadosPerformance.QuadPart);
	}

	//Retorna o resultado da função.
	return Resultado;
}
