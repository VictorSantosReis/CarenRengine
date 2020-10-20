#pragma once
#include "..\SDK_Base.h"

//Importa o namespace base
using namespace CarenRengine;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;




//TypeDefs

//Typedef que verifica se a função falhou e pula para o label(Done:). Em caso de falha, define a variavel (Resultado) como ER_E_POINTER, caso contrario, não edita nada e deixa o método continuar.
#define SairOnError(ResultObj) if(ResultObj.StatusCode != ResultCode::SS_OK){ Resultado = CarenResult(ResultCode::ER_E_POINTER, false); goto Done; }



//FUNCÕES GLOBAIS.

/// <summary>
/// Função responsável por definir um ponteiro nativo a uma interface gerenciada que tem como base a ICaren.
/// Permite informar se deve liberar o ponteiro em caso de erro.
/// </summary>
/// <param name="Param_NativePointer">O ponteiro nativo a ser definido na interface.</param>
/// <param name="Param_Destino">A interface de destino que vai receber o ponteiro.</param>
/// <param name="Param_ReleasePointerOnErro">Um valor booleano que indica se deve liberar o ponteiro em caso de falha ao definir.</param>
/// <returns></returns>
CarenResult DefinirPonteiroInterface(IUnknown* Param_NativePointer, ICaren^ Param_Destino, bool Param_ReleasePointerOnErro = true);

/// <summary>
/// Função resposável por recuperar o ponteiro nativo de uma interface baseada em ICaren.
/// </summary>
/// <typeparam name="NativePointerOut">O tipo da interface nativa de saida.</typeparam>
/// <param name="Param_Interface">A interface gerenciada que será obtida o ponteiro interno.</param>
/// <param name="Param_Out_Interface">Retorna o ponteiro para a interface nativa.</param>
/// <returns></returns>
template<class OutTypePointer> CarenResult RecuperarPonteiroCaren(ICaren^ Param_Interface, OutTypePointer** Param_Out_Interface)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado;

	//Recupera o ponteiro
	Resultado = Param_Interface->RecuperarPonteiro((void**)Param_Out_Interface);

	//Retorna
	return Resultado;
}
