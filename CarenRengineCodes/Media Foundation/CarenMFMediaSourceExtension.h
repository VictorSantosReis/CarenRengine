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
#include "../SDK_MediaFoundation.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenMFSourceBuffer.h"
#include "CarenMFSourceBufferList.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe  responsável por fornecer funcionalidade para o Media Source Extension (MSE).
/// </summary>
public ref class CarenMFMediaSourceExtension : public ICarenMFMediaSourceExtension
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaSourceExtension).
	IMFMediaSourceExtension* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaSourceExtension();
	
	~CarenMFMediaSourceExtension();

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


	//Métodos da interface(ICarenMFMediaSourceExtension)
public:
	/// <summary>
	/// Adiciona um ICarenMFSourceBuffer à coleção de buffers associados ao ICarenMFMediaSourceExtension.
	/// </summary>
	/// <param name="Param_Type">(NOT PRESENT DOCUMENTATION)</param>
	/// <param name="Param_Notify">(NOT PRESENT DOCUMENTATION)</param>
	/// <param name="Param_Out_BufferFonte">(NOT PRESENT DOCUMENTATION)</param>
	virtual CarenResult AddSourceBuffer(
	String^ Param_Type, 
	ICarenMFSourceBufferNotify^ Param_Notify, 
	[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte);

	/// <summary>
	/// Obtém os buffers de origem que estão fornecendo ativamente dados de mídia para a fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_ListBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) que contém uma lista dos buffers ativos.</param>
	virtual void GetActiveSourceBuffers([Out] ICarenMFSourceBufferList^% Param_Out_ListBuffers);

	/// <summary>
	/// Obtém a duração da fonte de mídia em unidades de 100 nanossegundos.
	/// </summary>
	/// <param name="Param_Out_Duracao">Retorna a duração da midia em unidades de 100 nanossegundos.</param>
	virtual void GetDuration([Out] double% Param_Out_Duracao);

	/// <summary>
	/// Obtém o estado pronto da fonte da mídia.
	/// </summary>
	/// <param name="Param_Out_ReadyState">Retorna uma bandeira da enumeração(CA_MF_MSE_READY) que indica o estado pronto da fonte de mídia.</param>
	virtual void GetReadyState([Out] CA_MF_MSE_READY% Param_Out_ReadyState);

	/// <summary>
	/// Obtém o ICarenMFSourceBuffer no índice especificado na coleção de buffers.
	/// </summary>
	/// <param name="Param_Index">O Index para o buffer na coleção.</param>
	/// <param name="Param_Out_BufferFonte">Retorna um ponteiro para a interface(ICarenMFSourceBuffer) da fonte do buffer no index especificado. </param>
	virtual void GetSourceBuffer(
	UInt32 Param_Index, 
	[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte);

	/// <summary>
	/// Obtém a coleção de buffers de origem associados a esta fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_ListaBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) de coleção de buffers.</param>
	virtual void GetSourceBuffers([Out] ICarenMFSourceBufferList^% Param_Out_ListaBuffers);

	/// <summary>
	/// Obtém um valor que indica se o tipo MIME especificado é suportado pela fonte de mídia.
	/// </summary>
	/// <param name="Param_Type">O tipo de mídia para verificar o suporte.</param>
	/// <param name="Param_Out_Resultado">TRUE se o tipo de mídia for suportado; caso contrário, FALSE.</param>
	virtual void IsTypeSupported(
	String^ Param_Type, 
	[Out] Boolean% Param_Out_Resultado);

	/// <summary>
	/// Remove o buffer de origem especificado da coleta de buffers de origem gerenciados pelo objeto IMFMediaSourceExtension.
	/// </summary>
	/// <param name="Param_BufferFonte">Um ponteiro para a interface do buffer fonte a ser removido</param>
	virtual CarenResult RemoveSourceBuffer(ICarenMFSourceBuffer^ Param_BufferFonte);

	/// <summary>
	/// Define a duração da fonte de mídia em unidades de 100 nanossegundos.
	/// </summary>
	/// <param name="Param_Duracao">A duração da fonte de mídia em unidades de 100 nanossegundos</param>
	virtual CarenResult SetDuration(double Param_Duracao);

	/// <summary>
	/// Indique que o fim da transmissão de mídia foi alcançado.
	/// </summary>
	/// <param name="Param_Error">Usado para passar informações de erro.</param>
	virtual CarenResult SetEndOfStream(CA_MF_MSE_ERROR Param_Error);
};