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
#include "../Caren/CarenEvent.h"


//Construtor
CarenEvent::CarenEvent()
{
	//Nada é realizado aqui.
}

//Destruidor.
CarenEvent::~CarenEvent()
{
	//Descarta os dados não gerenciados.

	//Verifica se a classe já não foi descartada.
	if (DisposedClasse)
	{
		//A classe já foi descartada.
	}
	else
	{
		//Verifica se o ponteiro é valido e deleta
		if (PonteiroTrabalho != NULL)
		{
			//Fecha o evento.
			this->LiberarEvento();
		}

		//Define que a classe foi descartada
		Prop_DisposedClasse = true;
	}
}





//
// Métodos da interface ICarenEvent
//

/// <summary>
/// (CreateEventW) - Cria ou abre um objeto de evento nomeado ou sem nome.
/// </summary>
/// <param name="Param_AtributosEvento">Uma estrutura CA_SECURITY_ATTRIBUTES. Se este parâmetro é NULO, o evento não pode 
/// ser herdado por um processo filho.
/// A estrutura especifica um descritor de segurança para o novo evento. Sendo NULO, o evento recebe um descritor de 
/// segurança padrão. Os ACLs no descritor de segurança padrão para um evento vêm do símbolo primário ou de representação 
/// do criador.</param>
/// <param name="Param_ManualReset">Se este parâmetro for TRUE,a função cria um objeto de evento de redefinição manual,
/// que requer o uso da função (ResetarEvento) para definir o estado do evento para não sinalizado. Se este parâmetro for 
/// FALSE, a função cria um objeto de evento de redefinição automática e o sistema redefine automaticamente o estado do evento
/// para não sinalizado após a lançamento de um único thread.</param>
/// <param name="Param_EstadoInicial">Se este parâmetro é TRUE,o estado inicial do objeto do evento é sinalizado; caso contrário, não é sinalizado.</param>
/// <param name="Param_NomeObjetoEvento">O nome do objeto do evento. O nome é limitado a 260(MAX_PATH) caracteres. A comparação do nome é sensível ao caso(Case-Sensitive).
/// Se o (Param_NomeObjetoEvento) corresponde ao nome de um objeto de evento nomeado existente, esta função solicita o 
/// EVENT_ALL_ACCESS direito de acesso. Neste caso, os parâmetros (Param_ManualReset) e (Param_EstadoInicial) são ignorados porque já foram definidos pelo processo de criação. 
/// Se o parâmetro (Param_AtributosEvento) não é NULO, ele determina se o identificador pode ser herdado, mas seu membro descritor de segurança é ignorado.
/// Se o parâmetro (Param_NomeObjetoEvento) corresponde ao nome de outro tipo de objeto no mesmo espaço de nome (como um semáforo existente, mutex, temporâmico, trabalho ou 
/// objeto de mapeamento de arquivos), a função falha.</param>
CarenResult CarenEvent::CriarEvento(
	Estruturas::CA_SECURITY_ATTRIBUTES^ Param_AtributosEvento,
	Boolean Param_ManualReset,
	Boolean Param_EstadoInicial,
	String^ Param_NomeObjetoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	Utilidades Util;
	LPWSTR NomeObjetoEvento = NULL;
	SECURITY_ATTRIBUTES* pAtributos = NULL;

	//Verifica se a estrutura de atributos é valida
	if (ObjetoGerenciadoValido(Param_AtributosEvento))
	{
		//Chama o método para converter a estrutura gerenciada para nativa.
		pAtributos = Util.ConverterSECURITY_ATTRIBUTESManagedToUnamaged(Param_AtributosEvento);
	}

	//Verifica se um nome de objeto foi definido
	if (!String::IsNullOrEmpty(Param_NomeObjetoEvento))
	{
		//Converte a string gerenciada para um ponteiro nativo.
		NomeObjetoEvento = Util.ConverterStringToWCHAR(Param_NomeObjetoEvento);
	}

	//Chama o método para realizar a operação
	PonteiroTrabalho = CreateEventW(
		pAtributos? pAtributos: NULL, 
		static_cast<BOOL>(Param_ManualReset), 
		static_cast<BOOL>(Param_EstadoInicial), 
		NomeObjetoEvento? NomeObjetoEvento: NULL);

	//Obtém o resultado
	Hr = GetLastError();

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
	//Libera a memoria para os objetos se validos.
	SafeDeleteMemory(&NomeObjetoEvento);
	DeletarEstruturaSafe(&pAtributos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateEventExW) - Cria ou abre um objeto de evento nomeado ou sem nome. Permite especificar a mascara de acesso para o objeto.
/// </summary>
/// <param name="Param_AtributosEvento">Uma estrutura CA_SECURITY_ATTRIBUTES. Se este parâmetro é NULO, o evento não pode 
/// ser herdado por um processo filho.
/// A estrutura especifica um descritor de segurança para o novo evento. Sendo NULO, o evento recebe um descritor de 
/// segurança padrão. Os ACLs no descritor de segurança padrão para um evento vêm do símbolo primário ou de representação 
/// do criador.</param>
/// <param name="Param_NomeObjetoEvento">O nome do objeto do evento. O nome é limitado a 260(MAX_PATH) caracteres. A comparação do nome é sensível ao caso(Case-Sensitive).
/// Se o (Param_NomeObjetoEvento) corresponde ao nome de um objeto de evento nomeado existente, esta função solicita o 
/// EVENT_ALL_ACCESS direito de acesso. Neste caso, os parâmetros (Param_ManualReset) e (Param_EstadoInicial) são ignorados porque já foram definidos pelo processo de criação. 
/// Se o parâmetro (Param_AtributosEvento) não é NULO, ele determina se o identificador pode ser herdado, mas seu membro descritor de segurança é ignorado.
/// Se o parâmetro (Param_NomeObjetoEvento) corresponde ao nome de outro tipo de objeto no mesmo espaço de nome (como um semáforo existente, mutex, temporâmico, trabalho ou 
/// objeto de mapeamento de arquivos), a função falha.</param>
/// <param name="Param_Flags">Flags para criação do evento.</param>
/// <param name="Param_MascaraAcesso">A máscara de acesso para o objeto do evento. Consulte o (Synchronization Object Security and Access Rights) para saber os possiveis valores
/// para esse paramêtro.</param>
CarenResult CarenEvent::CriarEventoEx(
	Estruturas::CA_SECURITY_ATTRIBUTES^ Param_AtributosEvento,
	String^ Param_NomeObjetoEvento,
	Enumeracoes::CA_WIN_EVENT_FLAGS Param_Flags,
	UInt32 Param_MascaraAcesso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	Utilidades Util;
	LPWSTR NomeObjetoEvento = NULL;
	SECURITY_ATTRIBUTES* pAtributos = NULL;
	DWORD FlagsCreateEvent = static_cast<DWORD>(Param_Flags);

	//Verifica se a estrutura de atributos é valida
	if (ObjetoGerenciadoValido(Param_AtributosEvento))
	{
		//Chama o método para converter a estrutura gerenciada para nativa.
		pAtributos = Util.ConverterSECURITY_ATTRIBUTESManagedToUnamaged(Param_AtributosEvento);
	}

	//Verifica se um nome de objeto foi definido
	if (!String::IsNullOrEmpty(Param_NomeObjetoEvento))
	{
		//Converte a string gerenciada para um ponteiro nativo.
		NomeObjetoEvento = Util.ConverterStringToWCHAR(Param_NomeObjetoEvento);
	}

	//Chama o método para realizar a operação
	PonteiroTrabalho = CreateEventExW(
		pAtributos ? pAtributos : NULL,
		NomeObjetoEvento ? NomeObjetoEvento : NULL,
		FlagsCreateEvent,
		Param_MascaraAcesso);

	//Obtém o resultado
	Hr = GetLastError();

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
	//Libera a memoria para os objetos se validos.
	SafeDeleteMemory(&NomeObjetoEvento);
	DeletarEstruturaSafe(&pAtributos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Associa um determinado evento a classe atual.
/// O método vai retornar o código de erro(ER_FALHA), se um evento já existir.
/// </summary>
/// <param name="Param_PonteiroEvento">O ponteiro para um evento já criado.</param>
CarenResult CarenEvent::AssociarEvento(IntPtr Param_PonteiroEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	Utilidades Util;

	//Define o novo ponteiro de evento.
	PonteiroTrabalho = Util.ConverterPonteiroGerenciadorParaNativo(Param_PonteiroEvento);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
/// </summary>
/// <param name="Param_Out_Evento">O ponteiro para um evento já criado.</param>
CarenResult CarenEvent::RecuperarEvento([Out] IntPtr% Param_Out_Evento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas pelo método.
	Utilidades Util;

	//Verifcia se o evento é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Deixa o método continuar.
	}
	else
	{
		//O evento é invalido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Define o evento no parametro de saida
	Param_Out_Evento = Util.ConverterHandleToIntPtr(PonteiroTrabalho);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
/// </summary>
/// <param name="Param_Out_Evento">O ponteiro para a handle do evento.</param>
CarenResult CarenEvent::RecuperarEvento(LPVOID* Param_Out_Evento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas pelo método.
	Utilidades Util;

	//Verifcia se o evento é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Deixa o método continuar.
	}
	else
	{
		//O evento é invalido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Define o evento no parametro de saida
	*Param_Out_Evento = PonteiroTrabalho;

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (WaitForSingleObject) - Espera até que o objeto especificado esteja no estado sinalizado ou o intervalo do intervalo do tempo limite decorra.
/// </summary>
/// <param name="Param_TempoMilliseconds">O intervalo de tempo, em milissegundos. Se um valor não zero for especificado, a função aguarda até que o objeto seja sinalizado ou o intervalo 
/// decorra. Se (Param_TempoMilliseconds) é zero, a função não entra em um estado de espera se o objeto não for sinalizado; ele sempre retorna imediatamente. Se Param_TempoMilliseconds é 
/// infinito(1e+300 * 1e+300), a função retornará somente quando o objeto é sinalizado.</param>
CarenResult CarenEvent::AguardarObjetoUnico(UInt32 Param_TempoMilliseconds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = WaitForSingleObject(PonteiroTrabalho, Param_TempoMilliseconds);

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
/// (WaitForSingleObjectEx) - Espera até que o objeto especificado está no estado sinalizado, uma rotina de conclusão I / O ou chamada procedimento assíncrono (APC) é enfileirado para o 
/// segmento(Thread), ou o intervalo de intervalo de tempo decorrido.
/// </summary>
/// <param name="Param_TempoMilliseconds">O intervalo de tempo, em milissegundos. Se um valor não zero for especificado, a função aguarda até que o objeto seja sinalizado ou o intervalo 
/// decorra. Se (Param_TempoMilliseconds) é zero, a função não entra em um estado de espera se o objeto não for sinalizado; ele sempre retorna imediatamente. Se Param_TempoMilliseconds é 
/// infinito(1e+300 * 1e+300), a função retornará somente quando o objeto é sinalizado.</param>
/// <param name="Param_Alertavel">Se este parâmetro é TRUE e a linha está no estado de espera, a função retorna quando o sistema enfileira uma rotina da conclusão de I/O ou Um APC, e a 
/// linha funciona a rotina ou a função. Caso contrário, a função não retorna, e a rotina de conclusão ou a função APC não é executada.
/// Uma rotina de conclusão é enfileirada quando a função ReadFileEx ou WriteFileEx na qual foi especificada foi concluída. </param>
CarenResult CarenEvent::AguardarObjetoUnicoEx(UInt32 Param_TempoMilliseconds, Boolean Param_Alertavel)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = WaitForSingleObjectEx(PonteiroTrabalho, Param_TempoMilliseconds, Param_Alertavel? TRUE: FALSE);

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
/// (ResetEvent) - Define o objeto de evento da classe atual para o estado não sinalizado.
/// </summary>
CarenResult CarenEvent::ResetarEvento()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado BOOL
	BOOL ResultMetodo = FALSE;

	//Chama o método para realizar a operação.
	ResultMetodo = ResetEvent(PonteiroTrabalho);

	//Verifica se a operação obteve sucesso.
	if (ResultMetodo)
	{
		//Deixa continuar.
	}
	else
	{
		//Define falha na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetEvent) - Define o objeto do evento da classe atual para o estado sinalizado.
/// </summary>
CarenResult CarenEvent::SinalizarEvento()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado BOOL
	BOOL ResultMetodo = FALSE;

	//Chama o método para realizar a operação.
	ResultMetodo = SetEvent(PonteiroTrabalho);

	//Verifica se a operação obteve sucesso.
	if (ResultMetodo)
	{
		//Deixa continuar.
	}
	else
	{
		//Define falha na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CloseHandle) - Fecha a alça do evento criado ou aberto anteriormente.
/// </summary>
CarenResult CarenEvent::LiberarEvento()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado BOOL
	BOOL ResultMetodo = FALSE;

	//Chama o método para realizar a operação.
	ResultMetodo = CloseHandle(PonteiroTrabalho);

	//Verifica se a operação obteve sucesso.
	if (ResultMetodo)
	{
		//Deixa continuar.
	}
	else
	{
		//Define falha na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}