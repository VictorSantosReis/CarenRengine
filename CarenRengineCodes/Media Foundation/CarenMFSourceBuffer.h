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

#pragma once
#include "../SDK_MediaFoundation.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenMFMediaTimeRange.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um buffer que contém dados de mídia para um ICarenMFMediaSourceExtension. 
/// </summary>
public ref class CarenMFSourceBuffer : public ICarenMFSourceBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceBuffer).
	IMFSourceBuffer* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFSourceBuffer();
	
	~CarenMFSourceBuffer();

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


	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenMFSourceBuffer)
public:
	/// <summary>
	/// Aborta o processamento do segmento de mídia atual.
	/// </summary>
	virtual CarenResult Abort();

	/// <summary>
	/// Anexa o segmento de mídia especificado ao ICarenMFSourceBuffer.
	/// </summary>
	/// <param name="Param_Buffer">Os dados da mídia para anexar.</param>
	/// <param name="Param_LarguraBuffer">O comprimento dos dados de mídia armazenados em Param_Buffer.</param>
	virtual CarenResult Append(
	ICarenBuffer^ Param_Buffer, 
	UInt32 Param_LarguraBuffer);

	/// <summary>
	/// Anexa o segmento de mídia do fluxo de byte especificado para o ICarenMFSourceBuffer.
	/// </summary>
	/// <param name="Param_Fluxo">Os dados do fluxo de mídia.</param>
	/// <param name="Param_Ref_LarguraMaxima">A duração máxima dos dados do segmento de mídia.</param>
	virtual CarenResult AppendByteStream(
	ICarenMFByteStream^ Param_Fluxo, 
	UInt64% Param_Ref_LarguraMaxima);

	/// <summary>
	/// Obtém o carimbo de tempo para o fim da janela de acrescimo.
	/// </summary>
	/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o fim.</param>
	virtual void GetAppendWindowEnd([Out] double% Param_Out_Timestamp);

	/// <summary>
	/// Obtém o carimbo de tempo para o início da janela de acrescimo.
	/// </summary>
	/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o inicio.</param>
	virtual void GetAppendWindowStart([Out] double% Param_Out_Timestamp);

	/// <summary>
	/// Obtém o intervalo de tempo em Buffer.
	/// </summary>
	/// <param name="Param_Out_Buffered">Retorna uma interface com o intervalo de tempo Buffered.</param>
	virtual CarenResult GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered);

	/// <summary>
	/// Obtém a compensação de carimbo de tempo para fluxos de mídia anexados ao ICarenMFSourceBuffer.
	/// </summary>
	/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo compesado para fluxos anexados.</param>
	virtual void GetTimeStampOffset([Out] double% Param_Out_Timestamp);

	/// <summary>
	/// Obtém um valor que indica se Append, AppendByteStream ou Remove está em processo.
	/// </summary>
	/// <param name="Param_Out_Valor">Retorna um valor booleano indicando se alguns dos métodos está em processo atualmente.</param>
	virtual void GetUpdating([Out] Boolean% Param_Out_Valor);

	/// <summary>
	/// Remove os segmentos de mídia definidos pelo intervalo de tempo especificado do ICarenMFSourceBuffer.
	/// </summary>
	/// <param name="Param_Inicio">O início do intervalo de tempo.</param>
	/// <param name="Param_Fim">O fim do intervalo de tempo.</param>
	virtual CarenResult Remove(double Param_Inicio, double Param_Fim);

	/// <summary>
	/// Define o carimbo de tempo para o fim da janela de acrescimo.
	/// </summary>
	/// <param name="Param_Time">O carimbo de data e hora para o fim da janela de acrescimo.</param>
	virtual CarenResult SetAppendWindowEnd(double Param_Time);

	/// <summary>
	/// Define o carimbo de tempo para o início da janela de acrescimo.
	/// </summary>
	/// <param name="Param_Time">O carimbo de data e hora para o início da janela de acrescimo.</param>
	virtual CarenResult SetAppendWindowStart(double Param_Time);

	/// <summary>
	/// Define a compensação de carimbo de tempo para segmentos de mídia anexados ao ICarenMFSourceBuffer.
	/// </summary>
	/// <param name="Param_Offset">O valor offset para o timestamp dos fluxos de mídia anexados.</param>
	virtual CarenResult SetTimeStampOffset(double Param_Offset);
};