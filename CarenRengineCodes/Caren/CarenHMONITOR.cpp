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


#include "..\pch.h"
#include "CarenHMONITOR.h"

bool CarenHMONITOR::ConstruirFromHandle(IntPtr Param_Handle, UInt32 Param_Flags)
{
	//Converte para handle.
	HWND pHandle = (HWND)Param_Handle.ToPointer();
	DWORD Flags = static_cast<DWORD>(Param_Flags);

	//Chama a função
	pMonitor = MonitorFromWindow(pHandle, Flags);

	//Retorna true.
	return true;
}

bool CarenHMONITOR::ConstruirFromPoint(long Param_X, long Param_Y, UInt32 Param_Flags)
{
	//Cria o point.
	POINT pCord = { };
	pCord.x = Param_X;
	pCord.y = Param_Y;
	DWORD Flags = static_cast<DWORD>(Param_Flags);

	//Chama a função.
	pMonitor = MonitorFromPoint(pCord, Flags);

	//Retorna true;
	return true;
}

bool CarenHMONITOR::ConstruirFromRect(long Param_Top, long Param_Bottom, long Param_Rigth, long Param_Left, UInt32 Param_Flags)
{
	//Cria o Rect
	RECT pRect = {};
	pRect.top = Param_Top;
	pRect.bottom = Param_Bottom;
	pRect.right = Param_Rigth;
	pRect.left = Param_Left;
	DWORD Flags = static_cast<DWORD>(Param_Flags);

	//Chama a função.
	pMonitor = MonitorFromRect(&pRect, Flags);

	//Retorna true.
	return true;
}

void CarenHMONITOR::RecuperarObjeto(HMONITOR* Param_Out_Monitor)
{
	//Verifica se o monitor é valido.
	if (pMonitor)
	{
		//Define o monitor na saida.
		*Param_Out_Monitor = pMonitor;
	}
	else
	{
		//Define null porque o monitor é invalido.
		Param_Out_Monitor = NULL;
	}
}

void CarenHMONITOR::DefinirObjeto(HMONITOR Param_Monitor)
{
	//Define na variavel da classe.
	pMonitor = Param_Monitor;
}

bool CarenHMONITOR::Valido()
{
	//Retorna se o monitor é valido.
	return pMonitor ? true : false;
}
