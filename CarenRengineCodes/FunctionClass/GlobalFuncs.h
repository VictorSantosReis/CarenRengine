#pragma once
#include "../SDK_Base.h"

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

//Typedef que tenta recuperar um ponteiro nativo de uma interface que implementa ICaren. Pula para o label 'Done' se a interface não for valida ou ocorrer um erro na recuperação do ponteiro.
#define CarenGetPointerFromICarenSafe(CarenInterface, OutPointer) Resultado = RecuperarPonteiroCaren(CarenInterface, &OutPointer); SairOnError(Resultado); 

//Typedef que define de forma segura um ponteiro nativo em uma interface que implementa ICaren. O método pode liberar o ponteiro em caso de erro.
#define CarenSetPointerToICarenSafe(Pointer, CarenInterface, ReleasePointerOnError) Resultado = DefinirPonteiroInterface(Pointer, CarenInterface, ReleasePointerOnError);

//Typedef que tenta recuperar o ponteiro nativo para o buffer na interface (ICarenBufer). Pula para o label 'Done' se o buffer não for valido ou ocorrer um erro na recuperação do ponteiro.
#define CarenGetPointerFromICarenBufferSafe(CarenInterfaceBuffer, OutIntPtrBuffer) if(CarenInterfaceBuffer != nullptr){Resultado = CarenInterfaceBuffer->ObterPonteiroInterno(OutIntPtrBuffer); SairOnError(Resultado);}

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

/// <summary>
/// Método responsávelpor verificar se um objeto generico é valido para um determinado tipo de destino.
/// </summary>
/// <typeparam name="T">O tipo do objeto de destino esperado.</typeparam>
/// <param name="Param_Objeto">O objeto a ser verificado.</param>
/// <returns></returns>
template<class T> BOOL VerificarGenericoValido(System::Object^ Param_Objeto)
{
	//Retorna se o objeto generico é valido para o tipo.
	return dynamic_cast<T>(Param_Objeto) != nullptr;
}