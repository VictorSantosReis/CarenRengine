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
#include "../pch.h"
#include "../SDK_Base.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include <chrono>
#include <thread>

/// <summary>
/// Classe responsável por conter os métodos nativos do Windows que são utilizados pela biblioteca em determinadas funções.
/// </summary>
public ref class WindowsFunctions
{
public:
	/// <summary>
	/// Método responsável por retornar uma mensagem associada a um código HResult.
	/// </summary>
	/// <param name="Param_HResultCode"></param>
	String^ HResultMensagem(UInt32 Param_HResultCode);
	
	/// <summary>
	/// Método responsável por retornar o ultimo erro gerado(HRESULT). 
	/// </summary>
	UInt32 ObterUltimoCodigoErro();

	/// <summary>
	/// Método responsável por associar uma Thread de chamada com uma tarefa especifica.
	/// Chame o método (_AvRevertMmThreadCharacteristics) quando a thread não for mais executar chamadas de áudio.
	/// Está função deve ser utilizada por aplicativos de Audio e (Video & Audio) para diminuir a latência.
	/// </summary>
	/// <param name="Param_NameTask">O nome da task a qual a thread será associada. Este valor deve corresponder a algum valor da estrutura (CA_Windows_MMCSS_Multimedia_Name_Tasks).</param>
	/// <param name="Param_Out_TaskIndex">O identificador de tarefas único. Na primeira vez que esta função é chamada, este valor deve ser 0 na entrada. O valor do índice é devolvido na saída e pode ser usado como entrada em chamadas subsequentes.</param>
	/// <returns></returns>
	IntPtr _AvSetMmThreadCharacteristicsW(String^ Param_NameTask, OutParam UInt32% Param_Out_TaskIndex);

	/// <summary>
	/// Indica que uma Thread não está mais realizando trabalho associado à tarefa especificada.
	/// </summary>
	/// <param name="Param_Handle">A handle para a tarefa a associada. Esse valor é retornado pelo método (_AvSetMmThreadCharacteristicsW).</param>
	/// <returns></returns>
	Boolean _AvRevertMmThreadCharacteristics(IntPtr Param_Handle);

	/// <summary>
	/// Método responsável por realizar um Sleep.
	/// </summary>
	/// <param name="Param_Sleep"></param>
	void SleepNativo(UInt32 Param_Sleep);

	/// <summary>
	/// Método responsável por realizar um Sleep.
	/// </summary>
	/// <param name="Param_Sleep"></param>
	void SleepNativoChrono_MicroSeconds(UInt32 Param_Sleep);

	/// <summary>
	/// Método responsável por realizar um Sleep.
	/// </summary>
	/// <param name="Param_Sleep"></param>
	void SleepNativoChrono_Miliseconds(UInt32 Param_Sleep);

	/// <summary>
	/// Recupera o valor atual do contador de desempenho, que é um carimbo de tempo de alta resolução (1us) que pode ser usado para medições de intervalo de tempo.
	/// </summary>
	/// <param name="Param_OutPerformanceCounter"></param>
	Boolean _QueryPerformanceCounter([Out] Int64% Param_OutPerformanceCounter);

	/// <summary>
	/// Recupera a frequência do contador de desempenho. A frequência do contador de desempenho é fixada na inicialização do sistema e é consistente em todos os processadores. 
	/// Portanto, a frequência só precisa ser consultada após a inicialização do aplicativo, e o resultado pode ser armazenado em cache.
	/// </summary>
	/// <param name="Param_OutFrequency"></param>
	Boolean _QueryPerformanceFrequency([Out] Int64% Param_OutFrequency);

	/// <summary>
	/// (timeBeginPeriod) - A função solicita uma resolução mínima para temporizadores periódicos.
	/// Chame esta função imediatamente antes de usar os serviços do temporizador e ligue para a função CA_TimeEndPeriod imediatamente após terminar de usar os serviços do temporizador.
	/// Você deve corresponder cada chamada _TimeBeginPeriod com uma chamada para CA_TimeEndPeriod, especificando a mesma resolução mínima em ambas as chamadas. Um aplicativo pode fazer várias chamadas de _TimeBeginPeriod, 
	/// desde que cada chamada seja combinada com uma chamada para CA_TimeEndPeriod.
	/// </summary>
	/// <param name="Param_Periodo">Resolução mínima do temporizador, em milissegundos, para o motorista de aplicativo ou dispositivo. Um valor mais baixo especifica uma resolução mais alta (mais precisa).</param>
	CarenResult _TimeBeginPeriod(UInt32 Param_Periodo);

	/// <summary>
	/// (timeEndPeriod) - A função limpa uma resolução de temporizador mínimo previamente definida.
	/// </summary>
	/// <param name="Param_Periodo">A resolução, em milissegundos, definida na chamada para _TimeBeginPeriod.</param>
	CarenResult _TimeEndPeriod(UInt32 Param_Periodo);

	/// <summary>
	/// (timeGetDevCaps) - A função consulta o dispositivo temporizador para determinar sua resolução.
	/// </summary>
	/// <param name="Param_Out_PeriodoMinimo">Recebe a resolução mínima suportada, em milissegundos.</param>
	/// <param name="Param_Out_PeriodoMaximo">Recebe a resolução máxima suportada, em milissegundos.</param>
	CarenResult _TimeGetDevCaps([Out] UInt32% Param_Out_PeriodoMinimo, [Out] UInt32% Param_Out_PeriodoMaximo);
};

