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
#include "PropVariantManager.h"

PROPVARIANT* PropVariantManager::ConverterPropVariantManaged_ToUnmanaged(CA_PROPVARIANT^ Param_Estrutura)
{
	return NULL;
}

CA_PROPVARIANT^ PropVariantManager::ConverterPropVariantUnmanaged_ToManaged(PROPVARIANT* Param_Estrutura)
{
	return nullptr;
}
