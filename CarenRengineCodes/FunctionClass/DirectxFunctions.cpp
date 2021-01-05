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
#include "DirectxFunctions.h"

UInt32 DirectxFunctions::_D3D11CalcSubresource(UInt32 Param_MipSlice, UInt32 Param_ArraySlice, UInt32 Param_MipLevels)
{
	//Chama o método para realizar a função e retorna.
	return D3D11CalcSubresource(Param_MipSlice, Param_ArraySlice, Param_MipLevels);
}
