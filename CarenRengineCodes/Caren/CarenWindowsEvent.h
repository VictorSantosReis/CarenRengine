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


#pragma once
#include "../SDK_Base.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Enumeração de retorno de função.


//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar e gerenciar um Evento do sistema. 
/// </summary>
public ref class CarenWindowsEvent : public ICarenWindowsEvent
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a alça do evento.
	HANDLE PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenWindowsEvent();
	CarenWindowsEvent();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}


	//Métodos da interface (ICarenWindowsEvent)
public:
	/// <summary>
	/// (CreateEventW) - Cria ou abre um objeto de evento nomeado ou sem nome.
	/// </summary>
	/// <param name="Param_AtributosEvento">Uma estrutura CA_ATRIBUTOS_SEGURANCA. Se este parâmetro é NULO, o evento não pode 
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
	virtual CarenResult CriarEvento(
		Estruturas::CA_ATRIBUTOS_SEGURANCA^ Param_AtributosEvento,
		Boolean Param_ManualReset,
		Boolean Param_EstadoInicial,
		String^ Param_NomeObjetoEvento);

	/// <summary>
	/// (CreateEventExW) - Cria ou abre um objeto de evento nomeado ou sem nome. Permite especificar a mascara de acesso para o objeto.
	/// </summary>
	/// <param name="Param_AtributosEvento">Uma estrutura CA_ATRIBUTOS_SEGURANCA. Se este parâmetro é NULO, o evento não pode 
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
	virtual CarenResult CriarEventoEx(
		Estruturas::CA_ATRIBUTOS_SEGURANCA^ Param_AtributosEvento,
		String^ Param_NomeObjetoEvento,
		Enumeracoes::CA_WIN_EVENT_FLAGS Param_Flags,
		UInt32 Param_MascaraAcesso);

	/// <summary>
	/// Associa um determinado evento a classe atual.
	/// O método vai retornar o código de erro(ER_FALHA), se um evento já existir.
	/// </summary>
	/// <param name="Param_PonteiroEvento">O ponteiro para um evento já criado.</param>
	virtual CarenResult AssociarEvento(IntPtr Param_PonteiroEvento);

	/// <summary>
	/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
	/// </summary>
	/// <param name="Param_Out_Evento">O ponteiro para um evento já criado.</param>
	virtual CarenResult RecuperarEvento([Out] IntPtr% Param_Out_Evento);

	/// <summary>
	/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
	/// </summary>
	/// <param name="Param_Out_Evento">O ponteiro para a handle do evento.</param>
	virtual CarenResult RecuperarEvento(LPVOID* Param_Out_Evento);

	/// <summary>
	/// (WaitForSingleObject) - Espera até que o objeto especificado esteja no estado sinalizado ou o intervalo do intervalo do tempo limite decorra.
	/// </summary>
	/// <param name="Param_TempoMilliseconds">O intervalo de tempo, em milissegundos. Se um valor não zero for especificado, a função aguarda até que o objeto seja sinalizado ou o intervalo 
	/// decorra. Se (Param_TempoMilliseconds) é zero, a função não entra em um estado de espera se o objeto não for sinalizado; ele sempre retorna imediatamente. Se Param_TempoMilliseconds é 
	/// infinito(1e+300 * 1e+300), a função retornará somente quando o objeto é sinalizado.</param>
	virtual CarenResult AguardarObjetoUnico(UInt32 Param_TempoMilliseconds);

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
	virtual CarenResult AguardarObjetoUnicoEx(UInt32 Param_TempoMilliseconds, Boolean Param_Alertavel);

	/// <summary>
	/// (ResetEvent) - Define o objeto de evento da classe atual para o estado não sinalizado.
	/// </summary>
	virtual CarenResult ResetarEvento();

	/// <summary>
	/// (SetEvent) - Define o objeto do evento da classe atual para o estado sinalizado.
	/// </summary>
	virtual CarenResult SinalizarEvento();

	/// <summary>
	/// (CloseHandle) - Fecha a alça do evento criado ou aberto anteriormente.
	/// </summary>
	virtual CarenResult LiberarEvento();
};

