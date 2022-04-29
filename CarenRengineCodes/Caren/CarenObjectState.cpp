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
#include "CarenObjectState.h"


//Destruidor.
CarenObjectState::~CarenObjectState()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenObjectState::CarenObjectState()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenObjectState::CarenObjectState(String^ Param_NomeObjeto)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	PWSTR vi_pNomeObjeto = Nulo; //A interface que vai gerenciar a vida deste objeto depois de sua criação.
	INACarenObjectState* vi_OutNewObject = Nulo;
	UINT32 vi_SizeNome = 0;

	//Verfifica se a string é valida e difente de " ".
	if (String::IsNullOrEmpty(Param_NomeObjeto))
		throw gcnew NullReferenceException("A string em (Param_NomeObjeto) não pode ser NULA!");

	//Obtém o size do nome.
	vi_SizeNome = static_cast<UInt32>(Param_NomeObjeto->Length);

	//Verifica a largura da string.
	if(vi_SizeNome == 0)
		throw gcnew Exception("A string deve conter dados validos.");

	//Chama o método para converter e alocar memória para o nome do objeto.
	vi_pNomeObjeto = Util.ConverterStringToWCHAR(Param_NomeObjeto);

	//Cria a interface.
	vi_OutNewObject = new CLN_CarenObjectState(const_cast<PWSTR&>(vi_pNomeObjeto), vi_SizeNome);

	//Verifica se não ocorreu erro no processo.
	if (!ObjetoValido(vi_OutNewObject))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception("Ocorreu uma falha desconhecida ao criar a interface.");
	}

	//Define a interface no ponteiro de trabalho
	PonteiroTrabalho = vi_OutNewObject;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenObjectState::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenObjectState::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<INACarenObjectState*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<INACarenObjectState**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenObjectState::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<INACarenObjectState*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<INACarenObjectState**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenObjectState::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenObjectState::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenObjectState::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenObjectState::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenObjectState::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenObjectState::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenObjectState::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenObjectState::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenObjectState();
}



// Métodos da interface proprietária(ICarenObjectState)


/// <summary>
/// Retorna o nome do objeto de estado atual se válido.
/// </summary>
/// <param name="Param_Out_NomeObjeto">Recebe o nome do objeto atual.</param>
/// <returns></returns>
CarenResult CarenObjectState::GetName(OutParam String^% Param_Out_NomeObjeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR vi_pOutNome = Nulo; //o método que aloca memória para este ponteiro.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetName(&vi_pOutNome);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_NomeObjeto = gcnew String(vi_pOutNome);

Done:;
	//Libera a memória para a string alocada.
	DeletarStringAllocatedSafe(&vi_pOutNome);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna a largura do nome do objeto de estado atual.
/// </summary>
/// <param name="Param_Out_Size">Recebe a largura da string.</param>
/// <returns></returns>
CarenResult CarenObjectState::GetNameLenght(OutParam UInt32% Param_Out_Size)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutSizeName = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetLenghtName(&vi_OutSizeName);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_Size = vi_OutSizeName;

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
///  Define um novo nome para o objeto de estado atual.
/// </summary>
/// <param name="Param_Nome">O novo nome do objeto.</param>
/// <param name="Param_SizeNome">A largura do novo nome.</param>
/// <returns></returns>
CarenResult CarenObjectState::SetName(String^ Param_Nome, UInt32 Param_SizeNome)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pNewName = Nulo;

	//Verifica se a string não é invalida
	if (String::IsNullOrEmpty(Param_Nome))
	{
		//Define erro de argumento.
		Resultado.AdicionarCodigo(ResultCode::ER_E_INVALIDARG, false);

		//Sai do método
		Sair;
	}

	//Converte a string.
	vi_pNewName = Util.ConverterStringToWCHAR(Param_Nome);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetName(
		const_cast<PWSTR&>(vi_pNewName),
		Param_SizeNome
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para a string.
	DeletarStringAllocatedSafe(&vi_pNewName);

	//Retorna o resultado.
	return Resultado;
}