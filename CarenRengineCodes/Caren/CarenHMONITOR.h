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
#include <Windows.h>
#include <WinUser.h>
using namespace System;

public ref class CarenHMONITOR
{
	//Variavel que vai conter o monitor.
	HMONITOR pMonitor = NULL;

	//Constantes
public:
	literal UInt32 Flag_MONITOR_DEFAULTTONEAREST = MONITOR_DEFAULTTONEAREST;
	literal UInt32 Flag_MONITOR_DEFAULTTONULL = MONITOR_DEFAULTTONULL;
	literal UInt32 Flag_MONITOR_DEFAULTTOPRIMARY = MONITOR_DEFAULTTOPRIMARY;


	//Métodos.
public:
	virtual bool ConstruirFromHandle(IntPtr Param_Handle, UInt32 Param_Flags);
	virtual bool ConstruirFromPoint(long Param_X, long Param_Y, UInt32 Param_Flags);
	virtual bool ConstruirFromRect(long Param_Top, long Param_Bottom, long Param_Rigth, long Param_Left, UInt32 Param_Flags);
	virtual void RecuperarObjeto(HMONITOR* Param_Out_Monitor);
	virtual void SetObject(HMONITOR Param_Monitor);
	virtual bool Valido();
};

