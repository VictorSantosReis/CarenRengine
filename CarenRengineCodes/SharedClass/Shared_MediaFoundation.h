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


//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// 
/// </summary>
class Shared_MFAttributes
{
	//Métodos da interface(ICarenMFAttributes)
public:
	/// <summary>
	/// Compara os atributos neste objeto com os atributos em outro objeto.
	/// </summary>
	/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
	/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
	static CarenResult Compare(
		IMFAttributes* Param_MyPointerWork,
		ICarenMFAttributes^ Param_InterfaceCompare, 
		CA_MF_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, 
		[Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PROPVARIANT.
	/// CA_PROPVARIANT é um Wrapper da PropVariant não gerenciada.
	/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PROPVARIANT) é diferente do (Valor) no Atributo,
	/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
	/// </summary>
	/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
	/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
	static CarenResult CompareItem(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_Valor, 
		[Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
	/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
	/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
	/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
	/// </summary>
	/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
	static CarenResult CopyAllItems(
		IMFAttributes* Param_MyPointerWork, 
		ICarenMFAttributes^ Param_Out_InterfaceDestino);


	/// <summary>
	/// Remove todos os pares chave/valor da lista de atributos do objeto.
	/// </summary>
	static CarenResult DeleteAllItems(IMFAttributes* Param_MyPointerWork);


	/// <summary>
	/// Remove um emparelhar chave/valor da lista de atributos do objeto.
	/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
	/// </summary>
	/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
	static CarenResult DeleteItem(
		IMFAttributes* Param_MyPointerWork, 
		String^ Param_GuidChave);



	//Métodos (GET) da interface IMFAttributes.



	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
	/// memória para a matriz.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	static CarenResult GetAllocatedBlob(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] CA_BlobData% Param_Out_Buffer);


	/// <summary>
	/// Obtém uma seqüência de caracteres largos associada a uma chave. 
	/// Este método aloca a memória para a seqüência de caracteres.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
	/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
	static CarenResult GetAllocatedString(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_String, 
		[Out] UInt32% Param_Out_LarguraString);


	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. 
	/// Esse método copia a matriz em um buffer alocado pelo chamador.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (GetBlobSize) para obter o valor para esse parametro.</param>
	static CarenResult GetBlob(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt32 Param_TamanhoBuffer, 
		[Out] CA_BlobData% Param_Out_Buffer);


	/// <summary>
	/// Recupera o comprimento de uma matriz de byte associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
	/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
	static CarenResult GetBlobSize(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt32% Param_TamanhoBuffer);


	/// <summary>
	/// Recupera o número de atributos que são definidos neste objeto.
	/// </summary>
	/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
	static CarenResult GetCount(
		IMFAttributes* Param_MyPointerWork, 
		[Out] UInt32% Param_QuantidadeAtributos);


	/// <summary>
	/// Recupera um valor (Double) associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetDouble(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] Double% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor GUID associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetGUID(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o valor desconhecido associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PROPVARIANT) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetItem(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor);


	/// <summary>
	/// Recupera um atributo no índice especificado.
	/// </summary>
	/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
	/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetItemByIndex(
		IMFAttributes* Param_MyPointerWork,
		UInt32 Param_IdItem, 
		[Out] String^% Param_Out_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor);


	/// <summary>
	/// Recupera o tipo de dados do valor associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
	/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
	static CarenResult GetItemType(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] CA_MF_ATTRIBUTE_TYPE% Param_Out_TipoDado);


	/// <summary>
	/// Recupera uma sequência de caracteres largos associada a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: GetStringLength</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
	static CarenResult GetString(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt32 Param_LagruraString, 
		[Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
	/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
	static CarenResult GetStringLength(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura);


	/// <summary>
	/// Recupera um valor de UINT32 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT32) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetUINT32(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor de UInt64 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	static CarenResult GetUINT64(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt64% Param_Out_Valor);

	/// <summary>
	/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
	/// Ese método recuperar o Numerador e Denominador de uma chave.
	/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
	/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
	/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
	static CarenResult _MFGetAttributeRatio(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Numerador, 
		[Out] UInt32% Param_Out_Denominador);

	/// <summary>
	/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
	/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
	/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro para o objeto desconhecido. O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetUnknown(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		String^ Param_GuidInterfaceSolicitada, 
		ICaren^ Param_Out_InterfaceDesconhecida);

	/// <summary>
	/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
	/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
	/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
	static CarenResult _MFGetAttributeSize(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura, 
		[Out] UInt32% Param_Out_Altura);

	/// <summary>
	/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
	/// </summary>
	static CarenResult LockStore(IMFAttributes* Param_MyPointerWork);




	//Métodos (SET) da interface IMFAttributes.




	/// <summary>
	/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Buffer">Uma interface (ICarenBuffer) que contém os dados a serem associados a chave especificada.</param>
	static CarenResult SetBlob(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		ICarenBuffer^ Param_Buffer);


	/// <summary>
	/// Associa um valor duplo com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	static CarenResult SetDouble(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		Double Param_Valor);


	/// <summary>
	/// RAssocia um valor GUID com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	static CarenResult SetGUID(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		String^ Param_Valor);


	/// <summary>
	/// Adiciona um valor de atributo com uma chave especificada.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
	static CarenResult SetItem(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_PropVariantValor);


	/// <summary>
	/// Associa uma seqüência de caracteres largos com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	static CarenResult SetString(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		String^ Param_Valor);


	/// <summary>
	/// Associa um valor de UINT32 com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	static CarenResult SetUINT32(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt32 Param_Valor);


	/// <summary>
	/// Associa um UINT64 valor com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	static CarenResult SetUINT64(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt64 Param_Valor);

	/// <summary>
	/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
	/// Esse método define no valor da chave uma razão(Numerador e Denominador).
	/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Numerador">Define o valor do: Numerador</param>
	/// <param name="Param_Denominador">Define o valor do: Denominador</param>
	static CarenResult _MFSetAttributeRatio(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt32 Param_Numerador, 
		UInt32 Param_Denominador);

	/// <summary>
	/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
	/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
	/// largura e altura em um único valor de UInt64 .
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Largura">A largura do vídeo em pixels.</param>
	/// <param name="Param_Altura">A altura do vídeo em pixels.</param>
	static CarenResult _MFSetAttributeSize(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		UInt32 Param_Largura, 
		UInt32 Param_Altura);

	/// <summary>
	/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
	static CarenResult SetUnknown(
		IMFAttributes* Param_MyPointerWork,
		String^ Param_GuidChave, 
		ICaren^ Param_InterfaceDesconhecida);


	/// <summary>
	/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
	/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
	/// </summary>
	static CarenResult UnlockStore(IMFAttributes* Param_MyPointerWork);
};