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
#include "../Caren/Caren.h"
#include "../FunctionClass/PropVariantManager.h"
#include "../SDK_Utilidades.h"

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
/// [Testes não foram realizados] - Representa um evento gerado por um objeto do Media Foundation. Use essa interface para obter informações sobre o evento.
/// </summary> 
public ref class CarenMFMediaEvent : public ICarenMFMediaEvent
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaEvent).
	IMFMediaEvent* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFMediaEvent();


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


	//Cria uma instância da classe atual.
public:
	/// <summary>
	/// Método responsável por criar uma instância de um novo evento para ser enviado.
	/// </summary>
	/// <param name="Param_HResultCode">O código HRESULT para identificar o resultado geral do evento. Defina 0, se a operação tiver sido bem sucedida.</param>
	/// <param name="Param_TipoEvento">A enumeração que vai definir o tipo deste evento.</param>
	/// <param name="Param_GuidExtended">O Guid que extende o tipo para eventos personalizados. O valor pode ser NULO.</param>
	/// <param name="Param_ValorAssociado">Uma CA_PropVariant que contém dados que devem ser anexados ao evento. O valor pode ser NULO.</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém o evento criado.</param>
	static CarenResult CriarInstancia(Int32 Param_HResultCode, CA_MediaEventType Param_TipoEvento, String^ Param_GuidExtended, CA_PropVariant^ Param_ValorAssociado, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
	{
		//Variavel que vai retornar o resultado do método.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		Utilidades Util;
		IMFMediaEvent *pMidiaEvent = NULL;
		MediaEventType TipoEvento = MEError;
		GUID GuidExtendedType = GUID_NULL;
		PROPVARIANT PropVarData;
		ICarenMFMediaEvent^ InterfaceMidiaEvent = nullptr;

		//Verifica se o Guid extendido é valido e converte para o guid nativo.
		if (Param_GuidExtended != nullptr)
		{
			//O guid é valido.
			//Converte para o guid nativo.
			GuidExtendedType = Util.CreateGuidFromString(Param_GuidExtended);
		}

		//Verifica se a PropVariant é valida e cria uma não gerenciada
		if (Param_ValorAssociado != nullptr)
		{
			//Inicia a propvariant.
			PropVariantInit(&PropVarData);

			//Converte a PropVariant.
			Util.ConvertPropVariantManagedToUnamaged(Param_ValorAssociado, PropVarData);
		}

		//Converte o tipo do evento para o não gerenciado
		TipoEvento = static_cast<MediaEventType>((UINT32)Param_TipoEvento);

		//Chama o método para criar o Media Event.
		Hr = MFCreateMediaEvent(TipoEvento, GuidExtendedType, Param_HResultCode, Param_ValorAssociado != nullptr ? &PropVarData : NULL, &pMidiaEvent);

		//Verifica o resultado da operação
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define falha na operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o evento.
		InterfaceMidiaEvent = gcnew CarenMFMediaEvent();

		//Chama o método para definir o ponteiro.
		InterfaceMidiaEvent->AdicionarPonteiro(pMidiaEvent);

		//Define a interface criada no parametro de saida.
		Param_Out_MidiaEvent = InterfaceMidiaEvent;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

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





	//Métodos da interface proprietaria.
public:
	/// <summary>
	/// (GetStatus) - Recupera um HRESULT que especifica o status do evento.
	/// </summary>
	/// <param name="Param_Out_HResultCode">Recebe o código de status do evento.</param>
	virtual CarenResult ObterStatus([Out] int% Param_Out_HResultCode);

	/// <summary>		
	/// (GetType) - Recupera o tipo de evento. O tipo de evento indica o que aconteceu para acionar o evento. Também define o significado do valor do evento.
	/// </summary>
	/// <param name="Param_Out_TipoEvento">Recebe a enumeração que define o tipo do evento gerado.</param>
	virtual CarenResult ObterTipo([Out] Enumeracoes::CA_MediaEventType% Param_Out_TipoEvento);

	/// <summary>
	/// (GetExtendedType) - Recupera o tipo estendido do evento. Utilizado para da suporte a eventos personalizados.
	/// </summary>
	/// <param name="Param_Out_GuidExtendedType">Recebe o guid para o tipo extendido do evento.</param>
	virtual CarenResult ObterTipoExtendido([Out] String^% Param_Out_GuidExtendedType);

	/// <summary>
	/// (GetValue) - Recupera o valor associado ao evento, se houver. O valor é recuperado como uma estrutura CA_PropVariant. O tipo de dados real e o significado do valor 
	/// dependem do evento.
	/// </summary>
	/// <param name="Param_Out_ValorEvento">Recebe a PropVariant que contém o valor associado ao evento. Nem todos eventos possuem valores.</param>
	virtual CarenResult ObterValor([Out] Estruturas::CA_PropVariant^% Param_Out_ValorEvento);







	//Métodos da interface(ICarenMFAttributes)
public:
	/// <summary>
	/// Compara os atributos neste objeto com os atributos em outro objeto.
	/// </summary>
	/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
	/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
	virtual CarenResult Comparar(ICarenMFAttributes^ Param_InterfaceCompare, Enumeracoes::CA_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, [Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PropVariant.
	/// CA_PropVariant é um Wrapper da PropVariant não gerenciada.
	/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PropVariant) é diferente do (Valor) no Atributo,
	/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
	/// </summary>
	/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
	/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
	virtual CarenResult CompararItem(String^ Param_GuidChave, Estruturas::CA_PropVariant^ Param_Valor, [Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
	/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
	/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
	/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
	/// </summary>
	/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
	virtual CarenResult CopiarTodosItens(ICarenMFAttributes^ Param_Out_InterfaceDestino);


	/// <summary>
	/// Remove todos os pares chave/valor da lista de atributos do objeto.
	/// </summary>
	virtual CarenResult DeletarTodosItens();


	/// <summary>
	/// Remove um emparelhar chave/valor da lista de atributos do objeto.
	/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
	/// </summary>
	/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
	virtual CarenResult DeletarItem(String^ Param_GuidChave);



	//Métodos (GET) da interface IMFAttributes.



	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
	/// memória para a matriz.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	virtual CarenResult ObterAlocaçãoBlob(String^ Param_GuidChave, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer);


	/// <summary>
	/// Obtém uma seqüência de caracteres largos associada a uma chave. 
	/// Este método aloca a memória para a seqüência de caracteres.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
	/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
	virtual CarenResult ObterAlocaçãoString(String^ Param_GuidChave, [Out] String^% Param_Out_String, [Out] UInt32% Param_Out_LarguraString);


	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. 
	/// Esse método copia a matriz em um buffer alocado pelo chamador.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (ObterBlobSize) para obter o valor para esse parametro.</param>
	virtual CarenResult ObterBlob(String^ Param_GuidChave, UInt32 Param_TamanhoBuffer, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer);


	/// <summary>
	/// Recupera o comprimento de uma matriz de byte associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
	/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
	virtual CarenResult ObterBlobSize(String^ Param_GuidChave, [Out] UInt32% Param_TamanhoBuffer);


	/// <summary>
	/// Recupera o número de atributos que são definidos neste objeto.
	/// </summary>
	/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
	virtual CarenResult ObterCountAtributos([Out] UInt32% Param_QuantidadeAtributos);


	/// <summary>
	/// Recupera um valor (Double) associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterDouble(String^ Param_GuidChave, [Out] Double% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor GUID associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterGuid(String^ Param_GuidChave, [Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o valor desconhecido associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PropVariant) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterItem(String^ Param_GuidChave, [Out] Estruturas::CA_PropVariant^% Param_Out_Valor);


	/// <summary>
	/// Recupera um atributo no índice especificado.
	/// </summary>
	/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
	/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterItemPorIndex(UInt32 Param_IdItem, [Out] String^% Param_Out_GuidChave, [Out] Estruturas::CA_PropVariant^% Param_Out_Valor);


	/// <summary>
	/// Recupera o tipo de dados do valor associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
	/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
	virtual CarenResult ObterTipoDadosItem(String^ Param_GuidChave, [Out] Enumeracoes::CA_ATTRIBUTE_TYPE% Param_Out_TipoDado);


	/// <summary>
	/// Recupera uma sequência de caracteres largos associada a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: ObterLarguraString</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
	virtual CarenResult ObterString(String^ Param_GuidChave, UInt32 Param_LagruraString, [Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
	/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
	virtual CarenResult ObterLarguraString(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura);


	/// <summary>
	/// Recupera um valor de UINT32 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT32) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterUINT32(String^ Param_GuidChave, [Out] UInt32% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor de UInt64 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult ObterUINT64(String^ Param_GuidChave, [Out] UInt64% Param_Out_Valor);

	/// <summary>
	/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
	/// Ese método recuperar o Numerador e Denominador de uma chave.
	/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
	/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
	/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
	virtual CarenResult ObterRatioAtribute(String^ Param_GuidChave, [Out] UInt32% Param_Out_Numerador, [Out] UInt32% Param_Out_Denominador);

	/// <summary>
	/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
	/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
	/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro para o objeto desconhecido. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult ObterPonteiroDesconhecido(String^ Param_GuidChave, String^ Param_GuidInterfaceSolicitada, ICaren^ Param_Out_InterfaceDesconhecida);

	/// <summary>
	/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
	/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
	/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
	virtual CarenResult ObterSizeAttribute(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura, [Out] UInt32% Param_Out_Altura);

	/// <summary>
	/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
	/// </summary>
	virtual CarenResult BloquearArmazenamento();




	//Métodos (SET) da interface IMFAttributes.




	/// <summary>
	/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Buffer">A matriz de bytes a ser associada a chave especificada.</param>
	virtual CarenResult DefinirBlob(String^ Param_GuidChave, cli::array<Byte>^ Param_Buffer);


	/// <summary>
	/// Associa um valor duplo com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirDouble(String^ Param_GuidChave, Double Param_Valor);


	/// <summary>
	/// RAssocia um valor GUID com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirGUID(String^ Param_GuidChave, String^ Param_Valor);


	/// <summary>
	/// Adiciona um valor de atributo com uma chave especificada.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirItem(String^ Param_GuidChave, Estruturas::CA_PropVariant^ Param_PropVariantValor);


	/// <summary>
	/// Associa uma seqüência de caracteres largos com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirString(String^ Param_GuidChave, String^ Param_Valor);


	/// <summary>
	/// Associa um valor de UINT32 com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirUINT32(String^ Param_GuidChave, UInt32 Param_Valor);


	/// <summary>
	/// Associa um UINT64 valor com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult DefinirUINT64(String^ Param_GuidChave, UInt64 Param_Valor);

	/// <summary>
	/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
	/// Esse método define no valor da chave uma razão(Numerador e Denominador).
	/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Numerador">Define o valor do: Numerador</param>
	/// <param name="Param_Denominador">Define o valor do: Denominador</param>
	virtual CarenResult DefinirRatioAtribute(String^ Param_GuidChave, UInt32 Param_Numerador, UInt32 Param_Denominador);

	/// <summary>
	/// (MFGetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
	/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
	/// largura e altura em um único valor de UInt64 .
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Largura">A largura do vídeo em pixels.</param>
	/// <param name="Param_Altura">A altura do vídeo em pixels.</param>
	virtual CarenResult DefinirSizeAttribute(String^ Param_GuidChave, UInt32 Param_Largura, UInt32 Param_Altura);

	/// <summary>
	/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
	virtual CarenResult DefinirPonteiroDesconhecido(String^ Param_GuidChave, ICaren^ Param_InterfaceDesconhecida);


	/// <summary>
	/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
	/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
	/// </summary>
	virtual CarenResult DesbloquearAtributo();
};