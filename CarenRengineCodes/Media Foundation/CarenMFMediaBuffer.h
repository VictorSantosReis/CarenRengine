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
#include "..\SDK_MediaFoundation.h"
#include "..\Caren\Caren.h"
#include "..\Caren\CarenBuffer.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// [Concluido - Fase de testes] - Falta documentar
/// </summary>
public ref class CarenMFMediaBuffer : public ICarenMFMediaBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaBuffer).
	IMFMediaBuffer* PonteiroTrabalho = NULL;



	//Contrutor e destruidor da classe.
public:
	~CarenMFMediaBuffer();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância da classe de armazenamento de buffer de mídia.
	/// Atenção: Utilize esse método apenas se você desejar criar manualmente um novo armazenamento e buffers de mídia.
	/// </summary>
	/// <param name="Param_TamanhoMaximoBuffer">Define o tamanho maximo deste buffer.</param>
	/// <param name="Param_Out_MidiaBuffer">Recebe a interface que gerencia buffers de midia.</param>
	static CarenResult CriarInstancia(UInt32 Param_TamanhoMaximoBuffer, [Out] ICarenMFMediaBuffer^% Param_Out_MidiaBuffer)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que vai conter o resultado COM.
		ResultadoCOM Hr;

		//Variavel que vai conter o Buffer.
		IMFMediaBuffer *pBufferData = NULL;

		//Instancia da classe atual
		ICarenMFMediaBuffer^ MediaBufferInterface = nullptr;

		//Chama o método para criar um buffer da memoria.
		Hr = MFCreateMemoryBuffer(Param_TamanhoMaximoBuffer, &pBufferData);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}
		
		//Cria a instância da classe
		MediaBufferInterface = gcnew CarenMFMediaBuffer();

		//Chama o método para definir o ponteiro de trabalho na interface a ser retornada.
		Resultado = MediaBufferInterface->AdicionarPonteiro(pBufferData);	

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Houve uma falha.

			//Descarta o ponteiro criado.
			SafeReleasePointer(&pBufferData);

			//Sai do método
			goto Done;
		}
		else
		{
			//Deixa o método continuar.

		}

		//Define a interface de retorno.
		Param_Out_MidiaBuffer = MediaBufferInterface;

	Done:;
		//Retorna o resultado.
		return Resultado;
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





	//Métodos da interface ICarenMidiabuffer
public:
	/// <summary>
	/// Recupera o comprimento dos dados válidos no buffer.
	/// </summary>
	/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos, em bytes. Se o buffer não contiver nenhum dado válido, o valor será zero.</param>
	virtual CarenResult ObterLarguraAtual([Out] UInt32% Param_Out_LarguraAtual);


	/// <summary>
	/// Recupera o Dimensionar alocado do buffer. Esse o valor da largura total
	/// de dados que podem ser adicioandos. Se o buffer conter dados, a largura dos dados
	/// podem ser menor que a lagrura máxima. Consulte (ObterLarguraAtual) para obter o 
	/// valor real da largura dos dados neste Buffer.
	/// </summary>
	/// <param name="Param_Out_LarguraMaxima">Recebe a largura total de dados que esse buffer pode conter.</param>
	virtual CarenResult ObterLarguraMaxima([Out] UInt32% Param_Out_LarguraMaxima);


	/// <summary>
	/// Force acesso aos dados que estão presentes neste buffer, para leitura ou gravação.
	/// Esse método fornece o acesso do chamador para o buffer inteiro, até o tamanho máximo retornado no Param_LarguraMaximaEscrita parâmetro. O valor retornado em Param_LarguraAtual 
	/// é o tamanho de todos os dados válidos já no buffer, que pode ser menor do que o tamanho do buffer total.
	/// </summary>
	/// <param name="Param_Out_BufferMidia">Recebe a interface responsável por gerenciar o buffer preso(Lock). Você poder: Escrever e Ler para o buffer.</param>
	/// <param name="Param_Out_LarguraMaximaEscrita">Recebe a quantidade máxima de dados que podem ser gravados para o buffer. Este parâmetro pode ser (NULO).</param>
	/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos no buffer, em bytes. Este parâmetro pode ser (NULO).</param>
	virtual CarenResult Lock([Out] ICarenBuffer^% Param_Out_BufferMidia, [Out] UInt32% Param_Out_LarguraMaximaEscrita, [Out] UInt32% Param_Out_LarguraAtual);


	/// <summary>
	/// Desbloqueia um buffer que foi bloqueado anteriormente. Chame esse método uma vez para cada chamada no método (Lock).
	/// É um erro chamar Unlock se você não chamar Lock anteriormente. Depois de chamar esse método, (Não Use) a interface 
	/// retornada pelo Lock método. Não é mais garantido que o buffer que contenha nela seja valido.
	/// </summary>
	virtual CarenResult Unlock();


	/// <summary>
	/// Define o comprimento dos dados válidos no buffer.
	/// ATENCAO: Chame esse método se você gravar dados no buffer.
	/// </summary>
	/// <param name="Param_LarguraAtual">Comprimento dos dados válidos, em bytes. Esse valor não pode ser maior do que o tamanho alocado do buffer,
	/// que é retornado pelo método (ObterLarguraMaxima).</param>
	virtual CarenResult DefinirLarguraAtual(UInt32 Param_LarguraAtual);

};

