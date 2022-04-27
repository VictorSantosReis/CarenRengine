﻿/*
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
#include "CarenMFFinalizableMediaSink.h"

//Destruidor.
CarenMFFinalizableMediaSink::~CarenMFFinalizableMediaSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFFinalizableMediaSink::CarenMFFinalizableMediaSink()
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
CarenResult CarenMFFinalizableMediaSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFFinalizableMediaSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFFinalizableMediaSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFFinalizableMediaSink**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFFinalizableMediaSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFFinalizableMediaSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFFinalizableMediaSink**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFFinalizableMediaSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFFinalizableMediaSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFFinalizableMediaSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFFinalizableMediaSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFFinalizableMediaSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFFinalizableMediaSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFFinalizableMediaSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFFinalizableMediaSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFFinalizableMediaSink();
}





// Métodos da interface proprietária(ICarenMFFinalizableMediaSink)


/// <summary>
/// Notifica a mídia para tomar as medidas assíncronas que precisa para terminar suas tarefas.
/// </summary>
/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto assíncrono. O chamador deve implementar esta interface.</param>
/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
CarenResult CarenMFFinalizableMediaSink::BeginFinalize(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjetoEstado = Nulo; //Pode ser NULO.

	//Recupera o ponteiro para o callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Recupera o ponteiro para o objeto de estado se informado.
	if(ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjetoEstado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginFinalize(vi_pCallback, vi_pObjetoEstado);

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
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Completa uma operação de finalização assíncrona.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
/// ICarenMFAsyncCallback::Invoke.</param>
CarenResult CarenMFFinalizableMediaSink::EndFinalize(ICarenMFAsyncResult^ Param_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* vi_pResultado = Nulo;

	//Recupera o ponteiro para a interface de resultado
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pResultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndFinalize(vi_pResultado);

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
	//Retorna o resultado.
	return Resultado;
}





// Métodos da interface ICarenMFMediaSink


/// <summary>
/// Adiciona um novo coletor de fluxo para o coletor de mídia.
/// O método retorna uma interface para o StreamSink adicionado.
/// </summary>
/// <param name="Param_IdentificadorFluxo">Um (Identificador) para o fluxo. O valor é (Arbitrário), mas deve ser exclusivo.</param>
/// <param name="Param_TipoMidia">Uma interface com o tipo de mídia do Stream a ser adicionado. Esse valor pode ser (NULO).</param>
/// <param name="Param_Out_FluxoSink">Retorna uma interface para o fluxo adicionado.</param>
CarenResult CarenMFFinalizableMediaSink::AddStreamSink(UInt32 Param_IdentificadorFluxo, ICarenMFMediaType^ Param_TipoMidia, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFMediaType* vi_pTipoMidiaForStreamSink = NULL;
	IMFStreamSink* vi_pOutStreamSink = NULL;

	//Chama o método para recuperar o ponteiro para o tipo de midia
	CarenGetPointerFromICarenSafe(Param_TipoMidia, vi_pTipoMidiaForStreamSink);

	//Chama o método para criar um novo StreamSink para o tipo da midia definida.
	Hr = PonteiroTrabalho->AddStreamSink(Param_IdentificadorFluxo, vi_pTipoMidiaForStreamSink, &vi_pOutStreamSink);

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

	//Cria a interface a ser retornada.
	Param_Out_FluxoSink = gcnew CarenMFStreamSink();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutStreamSink, Param_Out_FluxoSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém as características do coletor de mídia.
/// </summary>
/// <param name="Param_Out_Caracteristicas">Retorna as características desse (Coletor de mídia).</param>
CarenResult CarenMFFinalizableMediaSink::GetCharacteristics([Out] Enumeracoes::CA_MEDIASINK_CHARACTERISTICS% Param_Out_Caracteristicas)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutCaracteristicasColetorCode = 0;

	//Chama o método para recuperar as caracteristicas do coletor.
	Hr = PonteiroTrabalho->GetCharacteristics(&vi_OutCaracteristicasColetorCode);

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

	//Converter as caracteristicas para a enumerção
	Param_Out_Caracteristicas = static_cast<CA_MEDIASINK_CHARACTERISTICS>(vi_OutCaracteristicasColetorCode);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém o relógio de apresentação que foi definido no coletor de mídia.
/// </summary>
/// <param name="Param_Out_RelogioApresentação">Recebe a interface que contém o Relogio de Apresentação(IMFPresentationClock)</param>
CarenResult CarenMFFinalizableMediaSink::GetPresentationClock([Out] ICarenMFPresentationClock^% Param_Out_RelogioApresentação)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFPresentationClock* vi_pOutPresentationClock = NULL;

	//Chama o método que vai obter o ponteiro para o Relogio de apresentação
	Hr = PonteiroTrabalho->GetPresentationClock(&vi_pOutPresentationClock);

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

	//Cria a interface que vai armazenar o relogio.
	Param_Out_RelogioApresentação = gcnew CarenMFPresentationClock(false);

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutPresentationClock, Param_Out_RelogioApresentação, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um coletor de fluxo, especificado pelo identificador de fluxo.
/// </summary>
/// <param name="Param_IdentificadorFluxo">O Identificador para o fluxo a ser obtido.</param>
/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o Stream Sink requisitado pelo seu (Identificador)</param>
CarenResult CarenMFFinalizableMediaSink::GetStreamSinkById(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFStreamSink* vi_pOutStreamSink = NULL;

	//Chama o método para obter o StreamSink no identificador especificado.
	Hr = PonteiroTrabalho->GetStreamSinkById(Param_IdentificadorFluxo, &vi_pOutStreamSink);

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

	//Cria a interface a ser retornada.
	Param_Out_FluxoSink = gcnew CarenMFStreamSink();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutStreamSink, Param_Out_FluxoSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um coletor de fluxo, especificado por index.
/// </summary>
/// <param name="Param_IdFluxo">O Id para o coletor de fluxo a ser obtido.</param>
/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o coletor de fluxo requisitado.</param>
CarenResult CarenMFFinalizableMediaSink::GetStreamSinkByIndex(UInt32 Param_IdFluxo, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFStreamSink* vi_pOutStreamSink = NULL;

	//Chama o método para obter o StreamSink no index especificado.
	Hr = PonteiroTrabalho->GetStreamSinkByIndex(Param_IdFluxo, &vi_pOutStreamSink);

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

	//Cria a interface a ser retornada.
	Param_Out_FluxoSink = gcnew CarenMFStreamSink();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutStreamSink, Param_Out_FluxoSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém o número de coletores de fluxo neste coletor de mídia.
/// </summary>
/// <param name="Param_Out_QuantidadeSinks">Retorna a quantidade de (Coletores de Fluxos) presente nesse (Coletor de mídia)</param>
CarenResult CarenMFFinalizableMediaSink::GetStreamSinkCount([Out] UInt32% Param_Out_QuantidadeSinks)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD CountStreams = 0;

	//Chama o método para obter a quantidade de Streams
	Hr = PonteiroTrabalho->GetStreamSinkCount(&CountStreams);

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

	//Define o valor no parametro de saida.
	Param_Out_QuantidadeSinks = static_cast<UInt32>(CountStreams);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Remove um coletor de fluxo do coletor de mídia.
/// </summary>
/// <param name="Param_IdentificadorFluxo">O Identificador do fluxo a ser removido.</param>
CarenResult CarenMFFinalizableMediaSink::RemoveStreamSink(UInt32 Param_IdentificadorFluxo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para obter a quantidade de Streams
	Hr = PonteiroTrabalho->RemoveStreamSink(static_cast<DWORD>(Param_IdentificadorFluxo));

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
/// Define o relógio de apresentação no coletor de mídia.
/// </summary>
/// <param name="Param_RelogioApresentação">A interface que contém o relógio de apresentação a ser definido.
/// O valor pode ser (NULO). Se NULL, o (Coletor de Mídia) para de escutar o relógio de apresentação
/// que foi definido anteriormente, se houver.</param>
CarenResult CarenMFFinalizableMediaSink::SetPresentationClock(ICarenMFPresentationClock^ Param_RelogioApresentação)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variavies utilizadas no método
	IMFPresentationClock* vi_pRelogio = NULL;

	//Recupera o ponteiro para o relogio.
	CarenGetPointerFromICarenSafe(Param_RelogioApresentação, vi_pRelogio);

	//Chama o método para definir o relogio de apresentação
	Hr = PonteiroTrabalho->SetPresentationClock(vi_pRelogio);

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
/// Desliga o coletor de mídia e libera os recursos que ele está usando.
/// </summary>
CarenResult CarenMFFinalizableMediaSink::Shutdown()
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para que vai desligar o coletor
	Hr = PonteiroTrabalho->Shutdown();

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