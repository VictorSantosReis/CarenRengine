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
#include "CarenMFMediaSourceExtension.h"

//Destruidor.
CarenMFMediaSourceExtension::~CarenMFMediaSourceExtension()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaSourceExtension::CarenMFMediaSourceExtension()
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
CarenResult CarenMFMediaSourceExtension::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaSourceExtension::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaSourceExtension*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaSourceExtension**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaSourceExtension::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaSourceExtension*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaSourceExtension**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaSourceExtension::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaSourceExtension::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaSourceExtension::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaSourceExtension::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaSourceExtension::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaSourceExtension::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaSourceExtension::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaSourceExtension();
}



// Métodos da interface proprietária(ICarenMFMediaSourceExtension)


/// <summary>
/// Adiciona um ICarenMFSourceBuffer à coleção de buffers associados ao ICarenMFMediaSourceExtension.
/// </summary>
/// <param name="Param_Type">(NOT PRESENT DOCUMENTATION)</param>
/// <param name="Param_Notify">(NOT PRESENT DOCUMENTATION)</param>
/// <param name="Param_Out_BufferFonte">(NOT PRESENT DOCUMENTATION)</param>
CarenResult CarenMFMediaSourceExtension::AddSourceBuffer(
String^ Param_Type, 
ICarenMFSourceBufferNotify^ Param_Notify, 
[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pType = Nulo;
	IMFSourceBufferNotify* vi_pBufferNotify = Nulo;
	IMFSourceBuffer* vi_pOutSourceBuffer = Nulo;

	//Converte a string para BSTR.
	vi_pType = Util.ConverterStringToBSTR(Param_Type);

	//Recupera o ponteiro para a interface de notificação.
	CarenGetPointerFromICarenSafe(Param_Notify, vi_pBufferNotify);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddSourceBuffer(vi_pType, vi_pBufferNotify, &vi_pOutSourceBuffer);

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
	Param_Out_BufferFonte = gcnew CarenMFSourceBuffer();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutSourceBuffer, Param_Out_BufferFonte, true);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pType);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os buffers de origem que estão fornecendo ativamente dados de mídia para a fonte de mídia.
/// </summary>
/// <param name="Param_Out_ListBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) que contém uma lista dos buffers ativos.</param>
void CarenMFMediaSourceExtension::GetActiveSourceBuffers([Out] ICarenMFSourceBufferList^% Param_Out_ListBuffers)
{
	//Variaveis a serem utilizadas.
	IMFSourceBufferList* vi_pOutBufferList = Nulo;

	//Chama o método para realizar a operação.
	vi_pOutBufferList = PonteiroTrabalho->GetActiveSourceBuffers();

	//Verifica se a interface é valida
	if (ObjetoValido(vi_pOutBufferList))
	{
		//Cria a interface a ser retornada.
		Param_Out_ListBuffers = gcnew CarenMFSourceBufferList();

		//Define o ponteiro na interface
		Param_Out_ListBuffers->AdicionarPonteiro(vi_pOutBufferList);
	}
}

/// <summary>
/// Obtém a duração da fonte de mídia em unidades de 100 nanossegundos.
/// </summary>
/// <param name="Param_Out_Duracao">Retorna a duração da midia em unidades de 100 nanossegundos.</param>
void CarenMFMediaSourceExtension::GetDuration([Out] double% Param_Out_Duracao)
{
	//Chama o método para realizar a operação.
	Param_Out_Duracao = PonteiroTrabalho->GetDuration();
}

/// <summary>
/// Obtém o estado pronto da fonte da mídia.
/// </summary>
/// <param name="Param_Out_ReadyState">Retorna uma bandeira da enumeração(CA_MF_MSE_READY) que indica o estado pronto da fonte de mídia.</param>
void CarenMFMediaSourceExtension::GetReadyState([Out] CA_MF_MSE_READY% Param_Out_ReadyState)
{
	//Chama o método para realizar a operação.
	Param_Out_ReadyState = static_cast<CA_MF_MSE_READY>(PonteiroTrabalho->GetReadyState());
}

/// <summary>
/// Obtém o ICarenMFSourceBuffer no índice especificado na coleção de buffers.
/// </summary>
/// <param name="Param_Index">O Index para o buffer na coleção.</param>
/// <param name="Param_Out_BufferFonte">Retorna um ponteiro para a interface(ICarenMFSourceBuffer) da fonte do buffer no index especificado. </param>
void CarenMFMediaSourceExtension::GetSourceBuffer(
UInt32 Param_Index, 
[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte)
{
	//Variaveis a serem utilizadas.
	IMFSourceBuffer* vi_pOutSourceBuffer = Nulo;

	//Chama o método para realizar a operação.
	vi_pOutSourceBuffer = PonteiroTrabalho->GetSourceBuffer(static_cast<DWORD>(Param_Index));

	//Verifica se a interface é valida
	if (ObjetoValido(vi_pOutSourceBuffer))
	{
		//Cria a interface a ser retornada.
		Param_Out_BufferFonte = gcnew CarenMFSourceBuffer();

		//Define o ponteiro na interface.
		Param_Out_BufferFonte->AdicionarPonteiro(vi_pOutSourceBuffer);
	}
}

/// <summary>
/// Obtém a coleção de buffers de origem associados a esta fonte de mídia.
/// </summary>
/// <param name="Param_Out_ListaBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) de coleção de buffers.</param>
void CarenMFMediaSourceExtension::GetSourceBuffers([Out] ICarenMFSourceBufferList^% Param_Out_ListaBuffers)
{
	//Variaveis a serem utilizadas.
	IMFSourceBufferList* vi_pOutListSourceBuffers = Nulo;

	//Chama o método para realizar a operação.
	vi_pOutListSourceBuffers = PonteiroTrabalho->GetSourceBuffers();

	//Verifica se a interface é valida
	if (ObjetoValido(vi_pOutListSourceBuffers))
	{
		//Cria a interface a ser retornada.
		Param_Out_ListaBuffers = gcnew CarenMFSourceBufferList();

		//Define o ponteiro na interface.
		Param_Out_ListaBuffers->AdicionarPonteiro(vi_pOutListSourceBuffers);
	}
}


/// <summary>
/// Obtém um valor que indica se o tipo MIME especificado é suportado pela fonte de mídia.
/// </summary>
/// <param name="Param_Type">O tipo de mídia para verificar o suporte.</param>
/// <param name="Param_Out_Resultado">TRUE se o tipo de mídia for suportado; caso contrário, FALSE.</param>
void CarenMFMediaSourceExtension::IsTypeSupported(
String^ Param_Type, 
[Out] Boolean% Param_Out_Resultado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pType = Nulo;

	//Converte a string para BSTR.
	vi_pType = Util.ConverterStringToBSTR(Param_Type);

	//Chama o método para realizar a operação.
	Param_Out_Resultado = static_cast<Boolean>(PonteiroTrabalho->IsTypeSupported(vi_pType));

	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pType);
}

/// <summary>
/// Remove o buffer de origem especificado da coleta de buffers de origem gerenciados pelo objeto IMFMediaSourceExtension.
/// </summary>
/// <param name="Param_BufferFonte">Um ponteiro para a interface do buffer fonte a ser removido</param>
CarenResult CarenMFMediaSourceExtension::RemoveSourceBuffer(ICarenMFSourceBuffer^ Param_BufferFonte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFSourceBuffer* vi_pSourceBuffer = Nulo;

	//Recuperao ponteiro para a interface do buffer.
	CarenGetPointerFromICarenSafe(Param_BufferFonte, vi_pSourceBuffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveSourceBuffer(vi_pSourceBuffer);

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
/// Define a duração da fonte de mídia em unidades de 100 nanossegundos.
/// </summary>
/// <param name="Param_Duracao">A duração da fonte de mídia em unidades de 100 nanossegundos</param>
CarenResult CarenMFMediaSourceExtension::SetDuration(double Param_Duracao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDuration(Param_Duracao);

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
/// Indique que o fim da transmissão de mídia foi alcançado.
/// </summary>
/// <param name="Param_Error">Usado para passar informações de erro.</param>
CarenResult CarenMFMediaSourceExtension::SetEndOfStream(CA_MF_MSE_ERROR Param_Error)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetEndOfStream(static_cast<MF_MSE_ERROR>(Param_Error));

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