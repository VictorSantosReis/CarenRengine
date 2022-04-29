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
#include "CarenMFTranscodeSinkInfoProvider.h"

//Destruidor.
CarenMFTranscodeSinkInfoProvider::~CarenMFTranscodeSinkInfoProvider()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFTranscodeSinkInfoProvider::CarenMFTranscodeSinkInfoProvider()
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
CarenResult CarenMFTranscodeSinkInfoProvider::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTranscodeSinkInfoProvider*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTranscodeSinkInfoProvider**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTranscodeSinkInfoProvider*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTranscodeSinkInfoProvider**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFTranscodeSinkInfoProvider::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFTranscodeSinkInfoProvider::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFTranscodeSinkInfoProvider::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFTranscodeSinkInfoProvider::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFTranscodeSinkInfoProvider::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFTranscodeSinkInfoProvider();
}



// Métodos da interface proprietária(ICarenMFTranscodeSinkInfoProvider)


/// <summary>
/// Obtém os tipos de mídia para os fluxos de áudio e vídeo especificados no perfil de transcódigo.
/// </summary>
/// <param name="Param_Out_SinkInfo">Recebe uma estrutura CA_MF_TRANSCODE_SINK_INFO. Se o método for bem-sucedido, o método atribui ponteiros do ICarenMFMediaType aos membros 
/// pAudioMediaType e pVideoMediaType desta estrutura. O método pode definir qualquer membro como NULO. Se um dos membros não for NULO após o retorno do método, o chamador deve 
/// liberar os ponteiros das interfaces.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::GetSinkInfo([Out] CA_MF_TRANSCODE_SINK_INFO^% Param_Out_SinkInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	MF_TRANSCODE_SINK_INFO vi_OutTranscodeInfo = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSinkInfo(&vi_OutTranscodeInfo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_SinkInfo = Util.ConverterMF_TRANSCODE_SINK_INFOUnamaged_ToManaged(&vi_OutTranscodeInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um fluxo de byte de saída para o dissipador de mídia transcodificado.
/// </summary>
/// <param name="Param_ByteStream">Um ponteiro para a interface ICarenMFActivate de um objeto de ativação de fluxo de bytes(Byte-Stream).</param>
CarenResult CarenMFTranscodeSinkInfoProvider::SetOutputByteStream(ICarenMFActivate^ Param_ByteStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFActivate* vi_pAtivador = Nulo;

	//Recupera o ponteiro para a interface de ativação.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pAtivador);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputByteStream(vi_pAtivador);

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
/// Define o nome do arquivo de saída codificado.
/// </summary>
/// <param name="Param_NomeArquivo">Uma string que contém o nome do arquivo de saida.</param>
CarenResult CarenMFTranscodeSinkInfoProvider::SetOutputFile(String^ Param_NomeArquivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pUrlArquivoSaida = Nulo;

	//Converte a string para a nativa.
	vi_pUrlArquivoSaida = Util.ConverterStringToWCHAR(Param_NomeArquivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputFile(vi_pUrlArquivoSaida);

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
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pUrlArquivoSaida);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o perfil de transcodificação no objeto de ativação do dissipador de transcódigo.
/// </summary>
/// <param name="Param_Profile">Um ponteiro para a interface ICarenMFTranscodeProfile.</param> 
CarenResult CarenMFTranscodeSinkInfoProvider::SetProfile(ICarenMFTranscodeProfile^ Param_Profile)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFTranscodeProfile* vi_pProfile = Nulo;

	//Recupera o ponteiro para a interface do profile.
	CarenGetPointerFromICarenSafe(Param_Profile, vi_pProfile);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetProfile(vi_pProfile);

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