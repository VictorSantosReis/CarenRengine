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
#include "CarenMFAttributes.h"


//Destruidor.
CarenMFAttributes::~CarenMFAttributes()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Construtores
CarenMFAttributes::CarenMFAttributes()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenMFAttributes::CarenMFAttributes(UInt32 Param_QuantidadeAtributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFAttributes* vi_pOutAtributos = Nulo;
	
	//Chama o método para criar a interface.
	Hr = MFCreateAttributes(&vi_pOutAtributos, Param_QuantidadeAtributos);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define o ponteiro criado no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutAtributos;
}
CarenMFAttributes::CarenMFAttributes(ICarenMFCollection^ Param_ColecaoAtributosMuxStream)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variavel de resultado de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFCollection* vi_pCollectionMuxStreamAttributes = Nulo;
	IMFAttributes* vi_pOutAtributos = Nulo;

	//Verifica se a interface de coleção é valida
	if (!ObjetoGerenciadoValido(Param_ColecaoAtributosMuxStream))
		throw gcnew NullReferenceException("A interface no parâmetro (Param_ColecaoAtributosMuxStream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ColecaoAtributosMuxStream, &vi_pCollectionMuxStreamAttributes);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Não foi possivel recuperar o ponteiro da interface com a coleção de atributos.");

	//Chama o método para criar a interface.
	Hr = MFCreateMuxStreamAttributes(vi_pCollectionMuxStreamAttributes, &vi_pOutAtributos);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define o ponteiro criado no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutAtributos;
}



// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFAttributes::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAttributes::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAttributes*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAttributes**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAttributes::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAttributes*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAttributes**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAttributes::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAttributes::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFAttributes::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFAttributes::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFAttributes::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFAttributes::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFAttributes::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFAttributes();
}





// Métodos da interface ICarenMFAttributes


/// <summary>
/// Compara os atributos neste objeto com os atributos em outro objeto.
/// </summary>
/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
CarenResult CarenMFAttributes::Compare(
		ICarenMFAttributes^ Param_InterfaceCompare, 
		CA_MF_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, 
		[Out] Boolean% Param_Out_Resultado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::Compare(PonteiroTrabalho,
		Param_InterfaceCompare,
		Param_TipoComparação,
		Param_Out_Resultado
	);
}

/// <summary>
/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PROPVARIANT.
/// CA_PROPVARIANT é um Wrapper da PropVariant não gerenciada.
/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PROPVARIANT) é diferente do (Valor) no Atributo,
/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
/// </summary>
/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
CarenResult CarenMFAttributes::CompareItem(
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_Valor, 
		[Out] Boolean% Param_Out_Resultado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::CompareItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor,
		Param_Out_Resultado
	);
}

/// <summary>
/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
/// </summary>
/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
CarenResult CarenMFAttributes::CopyAllItems(ICarenMFAttributes^ Param_Out_InterfaceDestino)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::CopyAllItems(PonteiroTrabalho,
		Param_Out_InterfaceDestino
	);
}

/// <summary>
/// Remove todos os pares chave/valor da lista de atributos do objeto.
/// </summary>
CarenResult CarenMFAttributes::DeleteAllItems()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::DeleteAllItems(PonteiroTrabalho);
}

/// <summary>
/// Remove um emparelhar chave/valor da lista de atributos do objeto.
/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
/// </summary>
/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
CarenResult CarenMFAttributes::DeleteItem(String^ Param_GuidChave)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::DeleteItem(PonteiroTrabalho,
		Param_GuidChave
	);
}


// GET METHODS


/// <summary>
/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
/// memória para a matriz.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
CarenResult CarenMFAttributes::GetAllocatedBlob(
		String^ Param_GuidChave, 
		[Out] CA_BlobData% Param_Out_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetAllocatedBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Buffer
	);
}

/// <summary>
/// Obtém uma sequência de caracteres largos associada a uma chave. 
/// Este método aloca a memória para a seqüência de caracteres.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
CarenResult CarenMFAttributes::GetAllocatedString(
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_String, 
		[Out] UInt32% Param_Out_LarguraString)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetAllocatedString(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_String,
		Param_Out_LarguraString
	);
}

/// <summary>
/// Recupera uma matriz de byte associada a uma chave. 
/// Esse método copia a matriz em um buffer alocado pelo chamador.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (GetBlobSize) para obter o valor para esse parametro.</param>
CarenResult CarenMFAttributes::GetBlob(
		String^ Param_GuidChave, 
		UInt32 Param_TamanhoBuffer, 
		[Out] CA_BlobData% Param_Out_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_TamanhoBuffer,
		Param_Out_Buffer
	);
}

/// <summary>
/// Recupera o comprimento de uma matriz de byte associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
CarenResult CarenMFAttributes::GetBlobSize(
	String^ Param_GuidChave, 
	[Out] UInt32% Param_Out_TamanhoBuffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetBlobSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_TamanhoBuffer
	);
}

/// <summary>
/// Recupera o número de atributos que são definidos neste objeto.
/// </summary>
/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
CarenResult CarenMFAttributes::GetCount([Out] UInt32% Param_QuantidadeAtributos)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetCount(PonteiroTrabalho,
		Param_QuantidadeAtributos
	);
}

/// <summary>
/// Recupera um valor (Double) associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetDouble(
		String^ Param_GuidChave, 
		[Out] Double% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetDouble(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um valor GUID associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetGUID(
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetGUID(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o valor desconhecido associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PROPVARIANT) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetItem(
		String^ Param_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um atributo no índice especificado.
/// </summary>
/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetItemByIndex(
		UInt32 Param_IdItem, 
		[Out] String^% Param_Out_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItemByIndex(PonteiroTrabalho,
		Param_IdItem,
		Param_Out_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o tipo de dados do valor associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
CarenResult CarenMFAttributes::GetItemType(
		String^ Param_GuidChave, 
		[Out] CA_MF_ATTRIBUTE_TYPE% Param_Out_TipoDado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItemType(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_TipoDado
	);
}

/// <summary>
/// Recupera uma sequência de caracteres largos associada a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: GetStringLength</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
CarenResult CarenMFAttributes::GetString(
		String^ Param_GuidChave, 
		UInt32 Param_LagruraString, 
		[Out] String^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetString(PonteiroTrabalho,
		Param_GuidChave,
		Param_LagruraString,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
CarenResult CarenMFAttributes::GetStringLength(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetStringLength(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Largura
	);
}

/// <summary>
/// Recupera um valor de UInt32 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt32) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetUINT32(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUINT32(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um valor de UInt64 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFAttributes::GetUINT64(
		String^ Param_GuidChave, 
		[Out] UInt64% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUINT64(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
/// Ese método recuperar o Numerador e Denominador de uma chave.
/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
CarenResult CarenMFAttributes::_MFGetAttributeRatio(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Numerador, 
		[Out] UInt32% Param_Out_Denominador)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFGetAttributeRatio(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Numerador,
		Param_Out_Denominador
	);
}

/// <summary>
/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
CarenResult CarenMFAttributes::_MFGetAttributeSize(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura, 
		[Out] UInt32% Param_Out_Altura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFGetAttributeSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Largura,
		Param_Out_Altura
	);
}

/// <summary>
/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro par ao objeto desconhecido. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFAttributes::GetUnknown(
		String^ Param_GuidChave, 
		String^ Param_GuidInterfaceSolicitada, 
		ICaren^ Param_Out_InterfaceDesconhecida)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUnknown(PonteiroTrabalho,
		Param_GuidChave,
		Param_GuidInterfaceSolicitada,
		Param_Out_InterfaceDesconhecida
	);
}

/// <summary>
/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
/// </summary>
CarenResult CarenMFAttributes::LockStore()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::LockStore(PonteiroTrabalho);
}


//SET METHODS


/// <summary>
/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Buffer">Uma interface (ICarenBuffer) que contém os dados a serem associados a chave especificada.</param>
CarenResult CarenMFAttributes::SetBlob(
		String^ Param_GuidChave, 
		ICarenBuffer^ Param_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_Buffer
	);
}

/// <summary>
/// Associa um valor duplo com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetDouble(
		String^ Param_GuidChave, 
		Double Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetDouble(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um valor GUID com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetGUID(
		String^ Param_GuidChave, 
		String^ Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetGUID(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Adiciona um valor de atributo com uma chave especificada.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetItem(
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_PropVariantValor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_PropVariantValor
	);
}

/// <summary>
/// Associa uma seqüência de caracteres largos com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetString(
		String^ Param_GuidChave, 
		String^ Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetString(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um valor de UINT32 com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetUINT32(
		String^ Param_GuidChave, 
		UInt32 Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUINT32(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um UINT64 valor com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFAttributes::SetUINT64(
		String^ Param_GuidChave, 
		UInt64 Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUINT64(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
/// Esse método define no valor da chave uma razão(Numerador e Denominador).
/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Numerador">Define o valor do: Numerador</param>
/// <param name="Param_Denominador">Define o valor do: Denominador</param>
CarenResult CarenMFAttributes::_MFSetAttributeRatio(
		String^ Param_GuidChave, 
		UInt32 Param_Numerador, 
		UInt32 Param_Denominador)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFSetAttributeRatio(PonteiroTrabalho,
		Param_GuidChave,
		Param_Numerador,
		Param_Denominador
	);
}

/// <summary>
/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
/// largura e altura em um único valor de UInt64 .
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Largura">A Largura do vídeo em pixels.</param>
/// <param name="Param_Altura">A Altura do vídeo em pixels.</param>
CarenResult CarenMFAttributes::_MFSetAttributeSize(
		String^ Param_GuidChave, 
		UInt32 Param_Largura, 
		UInt32 Param_Altura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFSetAttributeSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Largura,
		Param_Altura
	);
}

/// <summary>
/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
CarenResult CarenMFAttributes::SetUnknown(
		String^ Param_GuidChave, 
		ICaren^ Param_InterfaceDesconhecida)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUnknown(PonteiroTrabalho,
		Param_GuidChave,
		Param_InterfaceDesconhecida
	);
}

/// <summary>
/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
/// </summary>
CarenResult CarenMFAttributes::UnlockStore()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::UnlockStore(PonteiroTrabalho);
}