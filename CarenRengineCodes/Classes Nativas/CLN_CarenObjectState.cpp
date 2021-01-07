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
#include "CLN_CarenObjectState.h"

STDMETHODIMP_(HRESULT __stdcall) CLN_CarenObjectState::GetName(_Out_ PWSTR* Param_Out_NameObjet)
{
    //Variavel que vai retornar o resultado.
    HRESULT Resultado = E_FAIL;

    //Variaveis utilizadas.
    Utilidades Util;

    //Verifica se o nome do objeto atual năo é invalido.
    if (!ObjetoValido(vi_Global_Name))
    {
        //Define erro.
        Resultado = E_POINTER;

        //Sai do método
        Sair;
    }

    //Verifica se o ponteiro informado pelo usuário năo é invalido
    if (!ObjetoValido(Param_Out_NameObjet))
    {
        //Define erro.
        Resultado = E_INVALIDARG;

        //Sai do método
        Sair;
    }
    
    //Abre um try para evitar exceçőes criticas.
    try
    {
        //Aloca memória para enviar uma copia do nome do objeto atual.
        *Param_Out_NameObjet = new WCHAR[vi_Global_SizeName]; //vi_Global_SizeName já contém -> +1

        //Copia o nome para a variavel alocada.
        wcscpy(*Param_Out_NameObjet, const_cast<PWSTR>(vi_Global_Name));
    }
    catch (const std::bad_alloc&)
    {
        //Verifica se há dados alocados e libera a memória.
        DeletarStringAllocatedSafe(Param_Out_NameObjet);

        //Năo há memória suficiente para realizar a operaçăo.
        Resultado = E_OUTOFMEMORY;

        //Sai do método
        Sair;
    }
    catch (const std::exception&)
    {
        //Verifica se há dados alocados e libera a memória.
        DeletarStringAllocatedSafe(Param_Out_NameObjet);

        //Ocorreu uma exceçăo desconhecida.
        Resultado = E_FAIL;

        //Sai do método
        Sair;
    }

    //Define sucesso na operaçăo.
    Resultado = S_OK;

Done:;
    //Retorna o resultado.
    return Resultado;
}

STDMETHODIMP_(HRESULT __stdcall) CLN_CarenObjectState::GetLenghtName(UINT32* Param_Out_Size)
{
    //Variavel que vai retornar o resultado.
    HRESULT Resultado = E_FAIL;

    //Verifica se o ponteiro năo é invalido
    if (!ObjetoValido(Param_Out_Size))
    {
        //Define erro.
        Resultado = E_INVALIDARG;

        //Sai do método
        Sair;
    }

    //Define a largura do nome do objeto atual.
    *Param_Out_Size = vi_Global_SizeName;

    //Define sucesso na operaçăo.
    Resultado = S_OK;

Done:;
    //Retorna o resultado.
    return Resultado;
}

STDMETHODIMP_(HRESULT __stdcall) CLN_CarenObjectState::SetName(_In_ const PWSTR& Param_NameObject, _In_ UINT32 Param_SizeName)
{
    //Variavel que vai retornar o resultado.
    HRESULT Resultado = E_FAIL;

    //Variaveis utilizadas.
    Utilidades Util;
    PWSTR vi_NewNameObject = Nulo; //Variavel que vai receber o novo nome.

    //Verifica se o nome é valido
    if (!ObjetoValido(Param_NameObject))
    {
        //Define erro.
        Resultado = E_INVALIDARG;

        //Sai do método
        Sair;
    }

    //Verifica se o tamanho năo é inválido.
    if (Param_SizeName == 0)
    {
        //Define erro.
        Resultado = E_INVALIDARG;

        //Sai do método
        Sair;
    }

    //Aloca memória para o objeto e copia os dados.
    try
    {
        //Aloca memória para enviar uma copia do nome do objeto atual.
        vi_NewNameObject = new WCHAR[Param_SizeName + 1];

        //Copia o nome para a variavel alocada.
        wcscpy(vi_NewNameObject, const_cast<PWSTR>(Param_NameObject));
    }
    catch (const std::bad_alloc&)
    {
        //Verifica se há dados alocados e libera a memória.
        DeletarStringAllocatedSafe(&vi_Global_Name);

        //Năo há memória suficiente para realizar a operaçăo.
        Resultado = E_OUTOFMEMORY;

        //Sai do método
        Sair;
    }
    catch (const std::exception&)
    {
        //Verifica se há dados alocados e libera a memória.
        DeletarStringAllocatedSafe(&vi_Global_Name);

        //Ocorreu uma exceçăo desconhecida.
        Resultado = E_FAIL;

        //Sai do método
        Sair;
    }

    //Libera a memória para o nome antigo se valido
    DeletarStringAllocatedSafe(&vi_Global_Name);

    //Define o novo nome.
    vi_Global_Name = vi_NewNameObject;

    //Define a nova largura.
    vi_Global_SizeName = Param_SizeName + 1;

    //Define sucesso na operaçăo.
    Resultado = S_OK;

Done:;
    //Retorna o resultado.
    return Resultado;
}