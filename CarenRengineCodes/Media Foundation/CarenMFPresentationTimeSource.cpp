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
#include "CarenMFPresentationTimeSource.h"


//Destruidor.
CarenMFPresentationTimeSource::~CarenMFPresentationTimeSource()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFPresentationTimeSource::CarenMFPresentationTimeSource(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFPresentationTimeSource* vi_pOutTimeSource = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreateSystemTimeSource(&vi_pOutTimeSource);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutTimeSource;
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
CarenResult CarenMFPresentationTimeSource::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFPresentationTimeSource::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFPresentationTimeSource*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFPresentationTimeSource**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFPresentationTimeSource::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFPresentationTimeSource*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFPresentationTimeSource**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFPresentationTimeSource::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFPresentationTimeSource::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFPresentationTimeSource::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFPresentationTimeSource::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFPresentationTimeSource::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFPresentationTimeSource::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFPresentationTimeSource::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFPresentationTimeSource();
}





// Métodos da interface proprietaria (ICarenMFPresentationTimeSource)


/// <summary>
/// Recupera o relógio subjacente que a fonte de tempo de apresentação usa para gerar seus tempos de relógio.
/// </summary>
/// <param name="Param_Out_Relogio">Recebe a interface ICarenMFClock que representa um Relógio. O chamador deve liberar a interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFPresentationTimeSource::GetUnderlyingClock(ICarenMFClock ^% Param_Out_Relogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFClock *vi_pOutClock = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetUnderlyingClock(&vi_pOutClock);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interace a ser retornada.
	Param_Out_Relogio = gcnew CarenMFClock();

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutClock, Param_Out_Relogio, true);

Done:;
	//Retorna o resultado
	return Resultado;
}





// Métodos da interface (ICarenMFClock)


/// <summary>
/// Recupera as características do relógio.
/// </summary>
/// <param name="Param_Out_CaracteristicasClock">Recebe os flags com as características do relógio.</param>
CarenResult CarenMFPresentationTimeSource::GetClockCharacteristics([Out] Enumeracoes::CA_MFCLOCK_CHARACTERISTICS_FLAGS% Param_Out_CaracteristicasClock)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutCharacteristicsClock = 0;

	//Chama o método para obter as caracteristicas
	Hr = PonteiroTrabalho->GetClockCharacteristics(&vi_OutCharacteristicsClock);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida
	Param_Out_CaracteristicasClock = static_cast<CA_MFCLOCK_CHARACTERISTICS_FLAGS>(vi_OutCharacteristicsClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Não Suportado Nativamente) - Recupera a chave de continuidade do relógio.
/// </summary>
/// <param name="Param_Out_Chave">Recebe a chave de continuidade.</param>
CarenResult CarenMFPresentationTimeSource::GetContinuityKey([Out] UInt32% Param_Out_Chave)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutKeyClock = 0;

	//Chama o método para obter a chave de continuidade
	Hr = PonteiroTrabalho->GetContinuityKey(&vi_OutKeyClock);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor da chave no parametro de retorno.
	Param_Out_Chave = safe_cast<UInt32>(vi_OutKeyClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a hora do último relógio que foi correlacionada com a hora do sistema.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_ClockTime">Recebe o último tempo de relógio conhecido, em unidades de freqüência do relógio.</param>
/// <param name="Param_Out_NsSystemTime">Recebe a hora do sistema que corresponde ao tempo de relógio retornado em Param_Out_ClockTime, em unidades de 100 nanosegundos.</param>
CarenResult CarenMFPresentationTimeSource::GetCorrelatedTime(UInt32 Param_ValorReservado, [Out] Int64% Param_Out_ClockTime, [Out] Int64% Param_Out_NsSystemTime)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	INT64 vi_OutClockTime = 0;
	INT64 vi_OutNsSystemTime = 0;

	//Chama o método para obter a hora correlacionada
	Hr = PonteiroTrabalho->GetCorrelatedTime(Param_ValorReservado, &vi_OutClockTime, &vi_OutNsSystemTime);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os parametros de saida
	Param_Out_ClockTime = vi_OutClockTime;
	Param_Out_NsSystemTime = vi_OutNsSystemTime;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera as propriedades do relógio.
/// </summary>
/// <param name="Param_Out_PropriedadesRelogio">Retorna a estrutura que contém as propriedades do relógio atual.</param>
CarenResult CarenMFPresentationTimeSource::GetProperties([Out] Estruturas::CA_MFCLOCK_PROPERTIES^% Param_Out_PropriedadesRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	MFCLOCK_PROPERTIES vi_OutPropsClock = { };

	//Chama o método para obter as propriedades do relogio.
	Hr = PonteiroTrabalho->GetProperties(&vi_OutPropsClock);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_PropriedadesRelogio = Util.ConverterMFCLOCK_PROPERTIESUnamaged_ToManaged(&vi_OutPropsClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o estado atual do relógio.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_EstadoRelogio">Retorna o valor da enumeração que define o estado atual do relógio.</param>
CarenResult CarenMFPresentationTimeSource::GetState(UInt32 Param_ValorReservado, [Out] Enumeracoes::CA_MFCLOCK_STATE% Param_Out_EstadoRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MFCLOCK_STATE vi_OutStateClock;

	//Chama o método para obter o estado do relogio.
	Hr = PonteiroTrabalho->GetState(Param_ValorReservado, &vi_OutStateClock);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o estado do relogio no parametro de saida.
	Param_Out_EstadoRelogio = static_cast<CA_MFCLOCK_STATE>(vi_OutStateClock);

Done:;
	//Retorna o resultado
	return Resultado;
}