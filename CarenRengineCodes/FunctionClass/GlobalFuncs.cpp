#include "../pch.h"
#include "../FunctionClass/GlobalFuncs.h"


#pragma region FUNÇÕES GLOBAIS
CarenResult DefinirPonteiroInterface(IUnknown* Param_NativePointer, ICaren^ Param_Destino, bool Param_ReleasePointerOnErro)
{
	//Variavel que retorna o resultado.
	CarenResultado Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se as interfaces são validas.
	if (!ObjetoGerenciadoValido(Param_Destino))
	{
		//Libera o ponteiro nativo se solicitado.
		if (Param_ReleasePointerOnErro)
			Param_NativePointer->Release(); Param_NativePointer = Nulo;

		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}
	if (!ObjetoValido(Param_NativePointer))
	{
		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	Resultado = Param_Destino->AdicionarPonteiro(Param_NativePointer);

	//Verifica o resultado.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Verifica se deve liberar o ponteiro.
		if (Param_ReleasePointerOnErro)
		{
			//Libera o ponteiro.
			Param_NativePointer->Release();
			Param_NativePointer = NULL;
			Param_Destino->Finalizar();
			Param_Destino = nullptr;
		}
	}

Done:;
	//Retorna
	return Resultado;
}
#pragma endregion