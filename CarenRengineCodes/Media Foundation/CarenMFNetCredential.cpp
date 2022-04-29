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
#include "CarenMFNetCredential.h"

//Destruidor.
CarenMFNetCredential::~CarenMFNetCredential()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFNetCredential::CarenMFNetCredential()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFNetCredential::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredential::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredential*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredential**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredential::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredential*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredential**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredential::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredential::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetCredential::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetCredential::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFNetCredential::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetCredential::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetCredential::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetCredential::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetCredential();
}



// Métodos da interface proprietária(ICarenMFNetCredential)


/// <summary>
/// Recupera a senha.
/// </summary>
/// <param name="Param_Ref_Senha">Um buffer de bytes que recebe a (SENHA). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados. O usuário é responsável por inicializar o buffer
/// com o tamanho necessário para ser retornado.</param>
/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Senha), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
/// <param name="Param_Criptografada">Se TRUE, o método retorna uma sequência criptografada. Caso contrário, o método retorna uma sequência não criptografada.</param>
CarenResult CarenMFNetCredential::GetPassword(
cli::array<Byte>^% Param_Ref_Senha,
UInt32% Param_Ref_LarguraDados,
Boolean Param_Criptografada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PBYTE vi_pOutSenha = Nulo; //Pode ser NULO para o usuário poder recuperar a largura necessária.
	DWORD vi_InOutLargura = Param_Ref_LarguraDados;

	//Cria o Buffer que vai receber os dados se o usuário tiver informado a largura.
	if (Param_Ref_LarguraDados > 0)
	{
		//Cria a matriz que vai conter os dados.
		vi_pOutSenha = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Ref_LarguraDados));
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPassword(ObjetoGerenciadoValido(Param_Ref_Senha) ? vi_pOutSenha : Nulo, &vi_InOutLargura, static_cast<BOOL>(Param_Criptografada));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se o buffer é valido e copia para a matriz gerenciada inicializada pelo usuário.
	if(ObjetoValido(vi_pOutSenha))
		Util.CopiarBufferNativo_ToGerenciado(&vi_pOutSenha, Param_Ref_Senha, static_cast<DWORD>(vi_InOutLargura));

	//Define no parametro de entrada e saida a largura do buffer.
	Param_Ref_LarguraDados = static_cast<DWORD>(vi_InOutLargura);

Done:;
	//Libera a memória utilizada pela matriz se valida.
	DeletarMatrizUnidimensionalSafe(&vi_pOutSenha);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o nome de usuário.
/// </summary>
/// <param name="Param_Ref_Usuario">Um buffer de bytes que recebe o (USUÁRIO). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados. O usuário é responsável por inicializar o buffer
/// com o tamanho necessário para ser retornado.</param>
/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Usuario), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
/// <param name="Param_Criptografada">Se TRUE,o método retorna uma seqüência criptografada. Caso contrário, o método retorna uma seqüência não criptografada.</param>
CarenResult CarenMFNetCredential::GetUser(
cli::array<Byte>^% Param_Ref_Usuario,
UInt32% Param_Ref_LarguraDados,
Boolean Param_Criptografada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PBYTE vi_pOutUsuario = Nulo; //Pode ser NULO para o usuário poder recuperar a largura necessária.
	DWORD vi_InOutLargura = Param_Ref_LarguraDados;

	//Cria o Buffer que vai receber os dados se o usuário tiver informado a largura.
	if (Param_Ref_LarguraDados > 0)
	{
		//Cria a matriz que vai conter os dados.
		vi_pOutUsuario = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Ref_LarguraDados));
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetUser(ObjetoGerenciadoValido(Param_Ref_Usuario) ? vi_pOutUsuario : Nulo, &vi_InOutLargura, static_cast<BOOL>(Param_Criptografada));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se o buffer é valido e copia para a matriz gerenciada inicializada pelo usuário.
	if (ObjetoValido(vi_pOutUsuario))
		Util.CopiarBufferNativo_ToGerenciado(&vi_pOutUsuario, Param_Ref_Usuario, static_cast<DWORD>(vi_InOutLargura));

	//Define no parametro de entrada e saida a largura do buffer.
	Param_Ref_LarguraDados = static_cast<DWORD>(vi_InOutLargura);

Done:;
	//Libera a memória utilizada pela matriz se valida.
	DeletarMatrizUnidimensionalSafe(&vi_pOutUsuario);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Verifica se as credenciais registradas devem ser usadas.
/// </summary>
/// <param name="Param_Out_Resultado">Recebe um valor booleano. Se as credenciais registradas devem ser usadas, o valor é TRUE. Caso contrário, o valor é FALSO.</param>
CarenResult CarenMFNetCredential::LoggedOnUser([Out] Boolean% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutResultado = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoggedOnUser(&vi_OutResultado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_Resultado = vi_OutResultado ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define a senha.
/// </summary>
/// <param name="Param_Senha">Um buffer de bytes que contém a (SENHA). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
/// buffer contém dados criptografados.</param>
/// <param name="Param_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
/// <param name="Param_Criptografar">Se TRUE, a senha será criptografada. Caso contrário, a senha não é criptografada.</param>
CarenResult CarenMFNetCredential::SetPassword(
cli::array<Byte>^ Param_Senha,
UInt32 Param_LarguraDados,
Boolean Param_Criptografar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PBYTE vi_pSenha = Nulo;
	DWORD vi_LarguraDados = static_cast<DWORD>(Param_LarguraDados);

	//Cria o buffer que vai conter a senha.
	vi_pSenha = CriarMatrizUnidimensional<BYTE>(vi_LarguraDados);

	//Copia os dados da matriz gerenciada.
	Util.CopiarBufferGerenciado_ToNativo(Param_Senha, &vi_pSenha, vi_LarguraDados);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPassword(vi_pSenha, vi_LarguraDados, Param_Criptografar ? true : false);

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
	//Libera a memória utilizada pela matriz nativa.
	DeletarMatrizUnidimensionalSafe(&vi_pSenha);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o nome de usuário.
/// </summary>
/// <param name="Param_Usuario">Um buffer de bytes que contém o (USUÁRIO). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
/// buffer contém dados criptografados.</param>
/// <param name="Param_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
/// <param name="Param_Criptografar">Se TRUE, o usuário será criptografado. Caso contrário, o usuário não é criptografado.</param>
CarenResult CarenMFNetCredential::SetUser(
cli::array<Byte>^ Param_Usuario,
UInt32 Param_LarguraDados,
Boolean Param_Criptografar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PBYTE vi_pUsuario = Nulo;
	DWORD vi_LarguraDados = static_cast<DWORD>(Param_LarguraDados);

	//Cria o buffer que vai conter a senha.
	vi_pUsuario = CriarMatrizUnidimensional<BYTE>(vi_LarguraDados);

	//Copia os dados da matriz gerenciada.
	Util.CopiarBufferGerenciado_ToNativo(Param_Usuario, &vi_pUsuario, vi_LarguraDados);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetUser(vi_pUsuario, vi_LarguraDados, Param_Criptografar ? true : false);

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
	//Libera a memória utilizada pela matriz nativa.
	DeletarMatrizUnidimensionalSafe(&vi_pUsuario);

	//Retorna o resultado.
	return Resultado;
}