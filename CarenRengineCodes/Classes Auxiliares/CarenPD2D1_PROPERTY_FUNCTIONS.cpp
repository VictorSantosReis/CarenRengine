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
#include "CarenPD2D1_PROPERTY_FUNCTIONS.h"

CarenPD2D1_PROPERTY_FUNCTIONS::CarenPD2D1_PROPERTY_FUNCTIONS()
{
   
}

CarenPD2D1_PROPERTY_FUNCTIONS::~CarenPD2D1_PROPERTY_FUNCTIONS()
{
    
}


//Métodos de registro e de-registro dos eventos.

void CarenPD2D1_PROPERTY_FUNCTIONS::RegistrarCallback()
{
    //Variveis utilizadas
    Utilidades Util;

    //Cria todos os delegates.
    Callback_OnPropertySetFunction = gcnew DelegateNativo_Evento_OnPropertySetFunction(this, &CarenPD2D1_PROPERTY_FUNCTIONS::EncaminharEvento_OnPropertySetFunction);
    Callback_OnPropertyGetFunction = gcnew DelegateNativo_Evento_OnPropertyGetFunction(this, &CarenPD2D1_PROPERTY_FUNCTIONS::EncaminharEvento_OnPropertyGetFunction);

    //Converte os delegates para ponteiros do IntPtr
    IntPtr Pointer_OnPropertySetFunction = Util.ConverterDelegateToPointer(Callback_OnPropertySetFunction);
    IntPtr Pointer_OnPropertyGetFunction = Util.ConverterDelegateToPointer(Callback_OnPropertyGetFunction);

    //Aloca a Handle para cada delegate que fornece o método de chamado do evento.
    gHandle_Delegate_OnPropertySetFunction = Util.AlocarPointerDelegate(Pointer_OnPropertySetFunction);
    gHandle_Delegate_OnPropertyGetFunction = Util.AlocarPointerDelegate(Pointer_OnPropertyGetFunction);

    //Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
    PonteiroTrabalho_SET = Util.ConverterPointerDelegateToNativeDelegate<PD2D1_PROPERTY_SET_FUNCTION*>(Pointer_OnPropertySetFunction);
    PonteiroTrabalho_GET = Util.ConverterPointerDelegateToNativeDelegate<PD2D1_PROPERTY_GET_FUNCTION*>(Pointer_OnPropertyGetFunction);
}

void CarenPD2D1_PROPERTY_FUNCTIONS::UnRegisterCallback()
{
    //Libera o ponteiro para todos os eventos
    gHandle_Delegate_OnPropertySetFunction.Free();
    gHandle_Delegate_OnPropertyGetFunction.Free();

    //Verifica se é valido e deleta o ponteiro.
    if (ObjetoValido(PonteiroTrabalho_SET))
    {
        //Descarta o delegate.
        PonteiroTrabalho_SET = NULL;
    }
    //Verifica se é valido e deleta o ponteiro.
    if (ObjetoValido(PonteiroTrabalho_GET))
    {
        //Descarta o delegate.
        PonteiroTrabalho_GET = NULL;
    }
}


//Métodos para recuperar e definir as funções.

PD2D1_PROPERTY_SET_FUNCTION CarenPD2D1_PROPERTY_FUNCTIONS::RecuperarSetFunction()
{
    return *PonteiroTrabalho_SET;
}

PD2D1_PROPERTY_GET_FUNCTION CarenPD2D1_PROPERTY_FUNCTIONS::RecuperarGetFunction()
{
    return *PonteiroTrabalho_GET;
}

void CarenPD2D1_PROPERTY_FUNCTIONS::DefinirSetFunction(PD2D1_PROPERTY_SET_FUNCTION* Param_SetFunc)
{
    //Define o ponteiro de trabalho SET.
    PonteiroTrabalho_SET = Param_SetFunc;
}

void CarenPD2D1_PROPERTY_FUNCTIONS::DefinirGetFunction(PD2D1_PROPERTY_GET_FUNCTION* Param_GetFunc)
{
    //Define o ponteiro de trabalho GET.
    PonteiroTrabalho_GET = Param_GetFunc;
}


//Métodos que recebem a chamada nativa e encaminha para o usuário.

HRESULT CarenPD2D1_PROPERTY_FUNCTIONS::EncaminharEvento_OnPropertySetFunction(IUnknown* effect, const BYTE* data, UINT32 dataSize)
{
    //Variaveis Utilizadas.
    ICaren^ Efeito = gcnew Caren();
    ICarenBuffer^ BufferDados = gcnew CarenBuffer();
    CarenResult Resultado = CarenResult(ResultCode::SS_OK, true);

    //Define o ponteiro para o efeito.
    Efeito->AdicionarPonteiro(effect);

    //Define o buffer nativo na interface do buffer gerenciado.
    BufferDados->CriarBuffer(IntPtr(const_cast<BYTE*>(data)), false, dataSize, dataSize);
    
    //Chama o evento para notificar o usuário.
    Resultado = OnPropertySetFunction(Efeito, BufferDados, dataSize);

    //Retorna o resultado.
    return static_cast<HRESULT>(Resultado.HResult);
}

HRESULT CarenPD2D1_PROPERTY_FUNCTIONS::EncaminharEvento_OnPropertyGetFunction(const IUnknown* effect, BYTE* data, UINT32 dataSize, UINT32* actualSize)
{
   //Variaveis utilizadas para o método.
    Utilidades Util;
    ICaren^ OutEfeito = nullptr;
    ICarenBuffer^ OutBufferDados = nullptr;
    UInt32 OutDataSize = 0;
    UInt32 OutDataSizeAtual = 0;
    CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, true);

    //Variaveis nativas.
    IUnknown* pEfeito = NULL;
    GenPointer pBufferDados = DefaultGenPointer;

    //Chama o evento para recuperar os valores.
    Resultado = OnPropertyGetFunction(OutEfeito, OutBufferDados, OutDataSize, OutDataSizeAtual);

    //Verifica se obteve com sucesso os dados.
    if (!CarenSucesso(Resultado))
    {
        //Falhou ao obter os dados...

        //Sai do método
        Sair;
    }

    //Recupera o ponteiro para o evento.
    Resultado = RecuperarPonteiroCaren(OutEfeito, &pEfeito);

    //Sai do método em caso de erro.
    SairOnError(Resultado);

    //Recupera o ponteiro para o buffer.
    Resultado = OutBufferDados->ObterPonteiroInterno(pBufferDados);

    //Define os dados nos parametros de saida para o método nativo.
    effect = const_cast<const IUnknown*>(pEfeito);
    data = Util.ConverterIntPtrTo<PBYTE>(pBufferDados);
    dataSize = OutDataSize;
    *actualSize = OutDataSizeAtual;

Done:;

    //Retorna o resultado geral.
    return static_cast<HRESULT>(Resultado.HResult);
}
