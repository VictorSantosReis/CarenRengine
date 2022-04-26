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
#include "CarenMFAsyncResult.h"


//Destruidor.
CarenMFAsyncResult::~CarenMFAsyncResult()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFAsyncResult::CarenMFAsyncResult()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenMFAsyncResult::CarenMFAsyncResult(ICaren^ Param_ObjetoDados, ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoEstado)
{
	//Variavel que contém o resultado COM.
	HRESULT Hr = E_FAIL;

	
	//Variaveis utilizadas no método.
	Utilidades Util;
	IUnknown* vi_pObjetoDados = NULL;
	IMFAsyncCallback* vi_pAsyncCallback = NULL;
	IUnknown* vi_pObjetoEstado = NULL;
	IMFAsyncResult* vi_pOutAsyncResult = NULL;
	CarenResult Resultado;

	//Recupera o ponteiro para a interface do objeto de dados se informada.
	if (ObjetoGerenciadoValido(Param_ObjetoDados))
		RecuperarPonteiroCaren(Param_ObjetoDados, &vi_pObjetoDados);

	//Verifica se o callback foi informado.
	if (!ObjetoGerenciadoValido(Param_Callback))
		throw gcnew NullReferenceException("O parametro (Param_Callback) não pode ser NULO!");

	//Recupera o ponteiro para o callback.
	Resultado = RecuperarPonteiroCaren(Param_Callback, &vi_pAsyncCallback);

	//Verifica se não ocorreu erro durante o processo de captura do ponteiro.
	if (Resultado.StatusCode != ResultCode::SS_OK)
		throw gcnew Exception("O ponteiro para a interface (IMFAsyncCallback) era inválido!");

	//Recupera o poneiro para um objeto de estado se fornecido.
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
		RecuperarPonteiroCaren(Param_ObjetoEstado, &vi_pObjetoEstado);

	//Chama o método para criar o evento.
	Hr = MFCreateAsyncResult(vi_pObjetoDados, vi_pAsyncCallback, vi_pObjetoEstado, &vi_pOutAsyncResult);

	//Verifica o resultado da operação
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define o ponteiro criado no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutAsyncResult;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFAsyncResult::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAsyncResult::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFAsyncResult*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAsyncResult::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFAsyncResult*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAsyncResult::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAsyncResult::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFAsyncResult::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFAsyncResult::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFAsyncResult::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFAsyncResult::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFAsyncResult::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFAsyncResult::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFAsyncResult();
}






//Métodos da interface ICarenMFAsyncResult


/// <summary>
/// (GetObject) - Retorna um objeto associado à operação assíncrona. O tipo de objeto, se houver, depende do método assíncrono que foi chamado.
/// </summary>
/// <param name="Param_Out_Objeto">Recebe a interface com o objeto desconhecido. Se nenhum objeto estiver associado à operação, esse parâmetro receberá o valor NULO. 
/// Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFAsyncResult::GetObject(ICaren^ Param_Out_Objeto)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IUnknown* pObjeto = NULL;

	//Chama o método para obter o objeto.
	Hr = PonteiroTrabalho->GetObject(&pObjeto);

	//Verifica o resultado da operação
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else if (Hr == E_POINTER)
	{
		//Não existe um objeto associado.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o códgio Hresult
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho
	Param_Out_Objeto->AdicionarPonteiro(pObjeto);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetState) - Retorna o objeto de estado especificado pelo chamador no método Begin assíncrono.
/// O chamador do método assíncrono especifica o objeto de estado e pode usá-lo para qualquer finalidade definida pelo responsável da chamada. O objeto de estado pode ser NULO.
/// </summary>
/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFAsyncResult::GetState(ICaren^ Param_Out_ObjetoEstado)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IUnknown* pObjetoEstado = NULL;

	//Chama o método para obter o objeto de estado.
	Hr = PonteiroTrabalho->GetState(&pObjetoEstado);

	//Verifica o resultado da operação
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else if (Hr == E_POINTER)
	{
		//Não existe um objeto associado.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o códgio Hresult
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho
	Param_Out_ObjetoEstado->AdicionarPonteiro(pObjetoEstado);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetStateNoAddRef) - Retorna o objeto de estado especificado pelo chamador no método assíncrono Begin, sem incrementar a contagem de referência do objeto.
/// </summary>
/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFAsyncResult::GetStateNoAddRef(ICaren^ Param_Out_ObjetoEstado)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas no método
	IUnknown* pObjetoEstado = NULL;

	//Chama o método para obter o objeto de estado.
	pObjetoEstado = PonteiroTrabalho->GetStateNoAddRef();

	//Verifica o resultado da operação
	if (ObjetoValido(pObjetoEstado))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho
	Param_Out_ObjetoEstado->AdicionarPonteiro(pObjetoEstado);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetStatus) - Retorna o status da operação assíncrona.
/// </summary>
CarenResult CarenMFAsyncResult::GetStatus()
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para verificar o status do método.
	Hr = PonteiroTrabalho->GetStatus();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetStatus) - Define o status da operação assíncrona.
/// </summary>
/// <param name="Param_HRESULT">O código HRESULT que vai definir o status geral da operação.</param>
CarenResult CarenMFAsyncResult::SetStatus(int Param_HRESULT)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir o Código HRESULT
	Hr = PonteiroTrabalho->SetStatus(Param_HRESULT);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}