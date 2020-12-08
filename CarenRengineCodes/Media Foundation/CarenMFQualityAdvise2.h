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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável permitir que um objeto de pipeline ajuste sua própria qualidade de áudio ou vídeo, em resposta a mensagens de qualidade.
/// </summary>
public ref class CarenMFQualityAdvise2 : public ICarenMFQualityAdvise2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFQualityAdvise2).
	IMFQualityAdvise2* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFQualityAdvise2();
	
	~CarenMFQualityAdvise2();

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


	//Métodos da interface(ICarenMFQualityAdvise2)
public:
	/// <summary>
	/// Encaminhe um evento MEQualityNotify do sink da mídia.
	/// </summary>
	/// <param name="Param_Evento">Uma interface ICarenMFMediaEvent para o evento.</param>
	/// <param name="Param_Out_Flags">Recebe um Or bitwise de zero ou mais bandeiras da enumeração CA_MF_QUALITY_ADVISE_FLAGS.</param>
	virtual CarenResult NotifyQualityEvent(
	ICarenMFMediaEvent^ Param_Evento,
	OutParam CA_MF_QUALITY_ADVISE_FLAGS% Param_Out_Flags);


	//Métodos da interface(ICarenMFQualityAdvise)
public:
	/// <summary>
	/// Dropa as amostras em um intervalo de tempo especificado.
	/// </summary>
	/// <param name="Param_NsAmountToDrop">Quantidade de tempo para dropar, em unidades de 100 nanossegundos. Esse valor é sempre absoluto. Se o método for chamado várias vezes, não adicione os horários das chamadas anteriores.</param>
	virtual CarenResult DropTime(UInt64 Param_NsAmountToDrop);

	/// <summary>
	/// Recupera o modo de drop atual.
	/// </summary>
	/// <param name="Param_Out_DropMode">Recebe o modo de drop, especificado como membro da enumeração CA_MF_QUALITY_DROP_MODE.</param>
	virtual CarenResult GetDropMode([Out] CA_MF_QUALITY_DROP_MODE% Param_Out_DropMode);

	/// <summary>
	/// Recupera o nível de qualidade atual.
	/// </summary>
	/// <param name="Param_Out_NivelQualidade">Recebe o nível de qualidade, especificado como membro da enumeração CA_MF_QUALITY_LEVEL.</param>
	virtual CarenResult GetQualityLevel([Out] CA_MF_QUALITY_LEVEL% Param_Out_NivelQualidade);

	/// <summary>
	/// Define o modo de drop. No modo de drop, um componente dropa amostras, mais ou menos agressivamente dependendo do nível do modo de drop.
	/// Se esse método for chamado a uma fonte de mídia, a fonte de mídia pode alternar entre saídas diluídas e não diluídas. Se isso ocorrer, os fluxos afetados enviarão um evento MEStreamThinMode para indicar a transição. A operação é assíncroda; após o retorno do SetDropMode, você pode receber amostras que estavam na fila antes da transição. O evento MEStreamThinMode marca o ponto exato no fluxo onde a transição ocorre.
	/// </summary>
	/// <param name="Param_DropMode">Modo de queda solicitado, especificado como membro da enumeração CA_MF_QUALITY_DROP_MODE.</param>
	virtual CarenResult SetDropMode(CA_MF_QUALITY_DROP_MODE Param_DropMode);

	/// <summary>
	/// Define o nível de qualidade. O nível de qualidade determina como o componente consome ou produz amostras.
	/// </summary>
	/// <param name="Param_NivelQualidade">Nível de qualidade solicitado, especificado como membro da enumeração CA_MF_QUALITY_LEVEL.</param>
	virtual CarenResult SetQualityLevel(CA_MF_QUALITY_LEVEL Param_NivelQualidade);
};