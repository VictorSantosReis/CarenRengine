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
#include "CarenMFTranscodeProfile.h"


//Destruidor.
CarenMFTranscodeProfile::~CarenMFTranscodeProfile()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFTranscodeProfile::CarenMFTranscodeProfile(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFTranscodeProfile* vi_pOutTranscodeProfile = Nulo;
		
		//Chama o método para criar a interface.
		Hr = MFCreateTranscodeProfile(&vi_pOutTranscodeProfile);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutTranscodeProfile;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFTranscodeProfile::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTranscodeProfile::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTranscodeProfile*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTranscodeProfile**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTranscodeProfile::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTranscodeProfile*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTranscodeProfile**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTranscodeProfile::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTranscodeProfile::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFTranscodeProfile::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFTranscodeProfile::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFTranscodeProfile::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFTranscodeProfile::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFTranscodeProfile::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFTranscodeProfile();
}



// Métodos da interface proprietária(ICarenMFTranscodeProfile)


/// <summary>
/// Obtém as configurações de fluxo de áudio definidas no (Perfil Transcode).
/// </summary>
/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém as configurações atuais do fluxo de Áudio. 
/// O chamador deve liberar o ponteiro da interface.</param>
CarenResult CarenMFTranscodeProfile::GetAudioAttributes([Out] ICarenMFAttributes^% Param_Out_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pOutAtributos = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAudioAttributes(&vi_pOutAtributos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Atributos = gcnew CarenMFAttributes();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutAtributos, Param_Out_Atributos, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém as configurações do contêiner definidas no (Perfil Transcode).
/// </summary>
/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém o tipo de contêiner atual para o arquivo 
/// de saída. O chamador deve liberar o ponteiro da interface.</param>
CarenResult CarenMFTranscodeProfile::GetContainerAttributes([Out] ICarenMFAttributes^% Param_Out_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pOutAtributos = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerAttributes(&vi_pOutAtributos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Atributos = gcnew CarenMFAttributes();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutAtributos, Param_Out_Atributos, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém as configurações de fluxo de vídeo que estão atualmente definidas no (Perfil Transcode).
/// </summary>
/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém as configurações atuais do fluxo de Vídeo. 
/// O chamador deve liberar o ponteiro da interface.</param>
CarenResult CarenMFTranscodeProfile::GetVideoAttributes([Out] ICarenMFAttributes^% Param_Out_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pOutAtributos = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVideoAttributes(&vi_pOutAtributos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Atributos = gcnew CarenMFAttributes();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutAtributos, Param_Out_Atributos, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define as configurações de configuração do fluxo de áudio no (Perfil Transcode).
/// </summary>
/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do fluxo de Áudio. Os valores de atributo 
/// especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
CarenResult CarenMFTranscodeProfile::SetAudioAttributes(ICarenMFAttributes^ Param_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAtributos = Nulo;

	//Recupera o ponteiro para a interface de atributos a serem definidos.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAtributos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAudioAttributes(vi_pAtributos);

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
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define as configurações de configuração do contêiner no (Perfil Transcode).
/// </summary>
/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do contêiner no qual o arquivo 
/// transcodificado será armazenado. Os valores de atributo especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
CarenResult CarenMFTranscodeProfile::SetContainerAttributes(ICarenMFAttributes^ Param_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAtributos = Nulo;

	//Recupera o ponteiro para a interface de atributos a serem definidos.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAtributos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetContainerAttributes(vi_pAtributos);

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
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define as configurações de configuração do fluxo de vídeo no (Perfil Transcode).
/// </summary>
/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do fluxo de Vídeo. Os valores de atributo 
/// especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
CarenResult CarenMFTranscodeProfile::SetVideoAttributes(ICarenMFAttributes^ Param_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAtributos = Nulo;

	//Recupera o ponteiro para a interface de atributos a serem definidos.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAtributos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetVideoAttributes(vi_pAtributos);

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
	//Retorna o resultado.
	return Resultado;
}