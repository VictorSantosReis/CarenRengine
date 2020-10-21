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

//Importa o namespace que contém as interfaces da API primária.
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
/// (Concluido - Fase de Testes) - Classe responsável por representar um fluxo de bytes de alguma fonte de dados, que pode ser um arquivo local, um arquivo de rede ou alguma outra fonte. 
/// </summary>
public ref class CarenMFByteStream : public ICarenMFByteStream
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFByteStream).
	IMFByteStream* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenMFByteStream();


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
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenMFByteStream">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMFByteStream^% Param_Out_CarenMFByteStream)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenMFByteStream = gcnew CarenMFByteStream();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
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


	//Métodos da interface(ICarenMFByteStream)
public:
	/// <summary>
	/// (BeginRead) - Inicia uma operação de leitura assíncrona do fluxo.
	/// Quando todos os dados forem lidos no buffer, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
	/// ICarenMFByteStream::ConcluirLeituraAsync para concluir a solicitação assíncrona.
	/// </summary>
	/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar o buffer.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
	/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
	/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
	/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	virtual CarenResult LerAsync(
		ICarenBuffer^ Param_Buffer,
		UInt64 Param_TamanhoBuffer,
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjetoEstado);

	/// <summary>
	/// (BeginWrite) - Inicia uma operação de gravação assíncrona no fluxo.
	/// Quando todos os dados foram gravados no fluxo, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
	/// ICarenMFByteStream::ConcluirEscritaAsync para concluir a solicitação assíncrona.
	/// </summary>
	/// <param name="Param_Buffer">Um ponteiro para o buffer a ser escrito no fluxo.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
	/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
	/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
	/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	virtual CarenResult EscreverAsync(
		ICarenBuffer^ Param_Buffer,
		UInt64 Param_TamanhoBuffer,
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjetoEstado);

	/// <summary>
	/// (Close) - Fecha o fluxo e libera todos os recursos associados ao fluxo, como soquetes ou identificadores de arquivo. Esse método também cancela todas as solicitações
	/// de E / S assíncronas pendentes.
	/// </summary>
	virtual CarenResult Close();

	/// <summary>
	/// (EndRead) - Conclui uma operação de leitura assíncrona.
	/// </summary>
	/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
	/// ICarenMFAsyncCallback::Invoke.</param>
	/// <param name="Param_Out_TotalLido">Recebe o total de bytes que foi lido do fluxo.</param>
	virtual CarenResult ConcluirLeituraAsync(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalLido);

	/// <summary>
	/// (EndWrite) - Conclui uma operação de gravação assíncrona.
	/// </summary>
	/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
	/// ICarenMFAsyncCallback::Invoke.</param>
	/// <param name="Param_Out_TotalEscrito">Recebe o número de bytes que foram escritos.</param>
	virtual CarenResult ConcluirEscritaAsync(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalEscrito);

	/// <summary>
	/// (Flush) - Limpa todos os buffers internos usados pelo fluxo. Se você estiver gravando no fluxo, os dados em buffer serão gravados no arquivo ou dispositivo subjacente.
	/// </summary>
	virtual CarenResult Flush();

	/// <summary>
	/// (GetCapabilities) - Recupera as características do fluxo de bytes.
	/// </summary>
	/// <param name="Param_Out_CaracteristicasFluxo">Retorna uma ou mais bandeiras da enumeração (CA_CARACTERISTICAS_BYTESTREAM) que definem as caracteristicas do fluxo de bytes.</param>
	virtual CarenResult ObterCaracteristicas([Out] CA_CARACTERISTICAS_BYTESTREAM% Param_Out_CaracteristicasFluxo);

	/// <summary>
	/// (GetCurrentPosition) - Recupera a posição atual de leitura ou gravação no fluxo.
	/// </summary>
	/// <param name="Param_Out_Posicao">Retorna a posição atual, em bytes.</param>
	virtual CarenResult ObterPosicaoAtual([Out] UInt64% Param_Out_Posicao);

	/// <summary>
	/// (GetLength) - Recupera o comprimento do fluxo.
	/// </summary>
	/// <param name="Param_Out_Largura">Recebe o comprimento do fluxo, em bytes. Se o comprimento for desconhecido, este valor é -1.</param>
	virtual CarenResult ObterLargura([Out] UInt64% Param_Out_Largura);

	/// <summary>
	/// (IsEndOfStream) - Consulta se a posição atual atingiu o final do fluxo.
	/// </summary>
	/// <param name="Param_Out_FinalFluxo">Retorna o valor TRUE se a posiçao atual for o final do fluxo, caso contrário FALSE.</param>
	virtual CarenResult VerificarFinalFluxo([Out] Boolean% Param_Out_FinalFluxo);

	/// <summary>
	/// (Read) - Lê dados do fluxo.
	/// </summary>
	/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar esse buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
	/// <param name="Param_Out_TotalLido">Recebe o número de bytes lidos no buffer.</param>
	virtual CarenResult Ler(
		ICarenBuffer^ Param_Buffer,
		UInt64 Param_Tamanho,
		[Out] UInt64% Param_Out_TotalLido);

	/// <summary>
	/// (Seek) - Move a posição atual no fluxo por um deslocamento especificado.
	/// </summary>
	/// <param name="Param_Origem">Especifica a origem da busca como membro da enumeração CA_MFBYTESTREAM_SEEK_ORIGIN. O deslocamento é calculado em relação a esta posição.</param>
	/// <param name="Param_Offset">Especifica a nova posição, como um byte offset da origem da busca.</param>
	/// <param name="Param_Flags">Especifica zero ou mais bandeiras da enumeração CA_MFBYTESTREAM_SEEK_FLAGS.</param>
	/// <param name="Param_Out_NovaPosicao">Recebe a nova posição após a busca.</param>
	virtual CarenResult Seek(
		CA_MFBYTESTREAM_SEEK_ORIGIN Param_Origem,
		Int64 Param_Offset,
		CA_MFBYTESTREAM_SEEK_FLAGS Param_Flags,
		[Out] UInt64% Param_Out_NovaPosicao);

	/// <summary>
	/// (SetCurrentPosition) - Define a posição atual de leitura ou gravação.
	/// </summary>
	/// <param name="Param_Posicao">Nova posição no fluxo, como um byte offset desde o início do fluxo.</param>
	virtual CarenResult DefinirPosicaoAtual(UInt64 Param_Posicao);

	/// <summary>
	/// (SetLength) - Define o comprimento do fluxo.
	/// </summary>
	/// <param name="Param_LarguraFluxo">A largura do fluxo em bytes.</param>
	virtual CarenResult DefinirLargura(UInt64 Param_LarguraFluxo);

	/// <summary>
	/// (Write) - Grava dados no fluxo.
	/// </summary>
	/// <param name="Param_Buffer">Um ponteiro para o buffer que contém os dados a serem escritos.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
	/// <param name="Param_Out_TotalEscrito">Recebe o numero de bytes que foram escritos no buffer.</param>
	virtual CarenResult Escrever(
		ICarenBuffer^ Param_Buffer,
		UInt64 Param_Tamanho,
		[Out] UInt64% Param_Out_TotalEscrito);
};