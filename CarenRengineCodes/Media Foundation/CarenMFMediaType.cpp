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
#include "../pch.h"
#include "CarenMFMediaType.h"


//Destruidor.
CarenMFMediaType::~CarenMFMediaType()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaType::CarenMFMediaType(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFMediaType* vi_pOutMediaType = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreateMediaType(&vi_pOutMediaType);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutMediaType;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}

CarenMFMediaType::CarenMFMediaType(ICaren^ Param_StreamProperties)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IUnknown* vi_pStreamProps = Nulo;
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Recupera o ponteiro para o stream com as propriedades.
	CarenResult ResultGetProps = RecuperarPonteiroCaren(Param_StreamProperties, &vi_pStreamProps);

	//Verifica se não houve erro
	if (!CarenSucesso(ResultGetProps))
		throw gcnew Exception("Não foi possivel recuperar o ponteiro ou a interface do parametro (Param_StreamProperties) é inválida.");

	//Chama o método para criar a interface.
	Hr = MFCreateMediaTypeFromProperties(vi_pStreamProps, &vi_pOutMediaType);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutMediaType;
}

CarenMFMediaType::CarenMFMediaType(String^ Param_GuidRepresentation, ICarenBuffer^ Param_BufferRepresentation)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidRepresentation = GUID_NULL;
	GenPointer vi_pBuffer = DefaultGenPointer;
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Converte a string para o guid.
	vi_GuidRepresentation = Util.CreateGuidFromString(Param_GuidRepresentation);

	//Recupera o ponteiro do buffer.
	CarenResult ResultGetBuffer = Param_BufferRepresentation->GetInternalPointer(vi_pBuffer);

	//Verifica se não houve erro
	if (!CarenSucesso(ResultGetBuffer))
		throw gcnew Exception("Falhou ao recuperar o ponteiro para o buffer ou sua interface é inválida.");

	//Chama o método para criar a interface.
	Hr = MFCreateMediaTypeFromRepresentation(vi_GuidRepresentation, Util.ConverterIntPtrTo<LPVOID>(vi_pBuffer), &vi_pOutMediaType);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutMediaType;
}

CarenMFMediaType::CarenMFMediaType(ICarenMFCollection^ Param_MediaTypesToMux)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFCollection* vi_pCollectionToMux = Nulo;
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Verifica se a interface de coleção é valida
	if (!ObjetoGerenciadoValido(Param_MediaTypesToMux))
		throw gcnew NullReferenceException("A interface do parametro (Param_MediaTypesToMux) não pode ser NULA!");

	//Recupera o ponteiro para a interface de coleção.
	CarenResult ResultGetBuffer = RecuperarPonteiroCaren(Param_MediaTypesToMux, &vi_pCollectionToMux);

	//Verifica se não houve erro
	if (!CarenSucesso(ResultGetBuffer))
		throw gcnew Exception("Falhou ao recuperar o ponteiro para a interface de coleção.");

	//Chama o método para criar a interface.
	Hr = MFCreateMuxStreamMediaType(vi_pCollectionToMux, &vi_pOutMediaType);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutMediaType;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFMediaType::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaType::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFMediaType*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaType::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFMediaType*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaType::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaType::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaType::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaType::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaType::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaType::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaType::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaType::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaType();
}





//Métodos da interface ICarenMFMediaType.


/// <summary>
/// (GetMajorType) - Obtém o tipo principal da midia: Vídeo ou Áudio.
/// </summary>
/// <param name="Param_Out_GuidTipoMidia">Retorna o GUID do tipo principal da mídia.</param>
/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração com o tipo principal da mídia.</param>
CarenResult CarenMFMediaType::GetMajorType([Out] String^% Param_Out_GuidTipoMidia, [Out] CA_MAJOR_MEDIA_TYPES% Param_Out_TipoPrincipal)
{
	//Variavel que vai retornar o resultado do método.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis de retorno do método.
	CA_MAJOR_MEDIA_TYPES TipoMidiaEnum;

	//Variaveis utilizadas no método.
	GUID GuidTipoMidia = GUID_NULL;
	Utilidades Util;

	//Chama o método para obter o tipo principal da mídia
	Hr = PonteiroTrabalho->GetMajorType(&GuidTipoMidia);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica o tipo do guid retornado para definir a enumeração de retorno.

	//Verifica se o tipo principal Áudio.
	if (GuidTipoMidia == MFMediaType_Audio)
	{
		//Fluxo de Áudio.
		TipoMidiaEnum = CA_MAJOR_MEDIA_TYPES::TP_Audio;
	}

	//Verifica se o tipo principal é vídeo.
	else if (GuidTipoMidia == MFMediaType_Video)
	{
		//Fluxo de Vídeo.
		TipoMidiaEnum = CA_MAJOR_MEDIA_TYPES::TP_Video;
	}

	//O tipo não é válido para essa biblioteca.
	else
	{
		//Formato Desconhecido.
		TipoMidiaEnum = CA_MAJOR_MEDIA_TYPES::TP_Desconhecido;
	}

	//Define os parametros de saida
	Param_Out_GuidTipoMidia = Util.ConverterGuidToString(GuidTipoMidia);
	Param_Out_TipoPrincipal = TipoMidiaEnum;

	//Limpa
	GuidTipoMidia = GUID_NULL;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (IsCompressedFormat) - Consulta se o tipo de mídia é um formato compactado(CompressedFormat).
/// </summary>
/// <param name="Param_Out_FormatoCompactado">Retorna se o formato da mídia está compactado.</param>
CarenResult CarenMFMediaType::IsCompressedFormat([Out] Boolean% Param_Out_FormatoCompactado)
{
	//Variavel que vai retornar o resultado do método.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis de retorno do método.
	Boolean ResultadoCOMpressedFormato = false;

	//Variaveis utilizadas pelo método.
	BOOL _IsCompressed = FALSE;

	//Chama o método para obter o tipo principal da mídia
	Hr = PonteiroTrabalho->IsCompressedFormat(&_IsCompressed);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de saida.
	Param_Out_FormatoCompactado = _IsCompressed ? true : false;
Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (IsEqual) - Compara dois tipos de mídia e determina se eles são idênticos. 
/// Se eles não forem idênticos, o método indica como os dois formatos diferem.
/// </summary>
/// <param name="Param_MidiaCompare">A interface a ser comparada com a atual.</param>
/// <param name="Param_Out_ResultadoCompare">O resultado da comparação dos objetos.</param>
CarenResult CarenMFMediaType::IsEqual(ICarenMFMediaType^ Param_MidiaCompare, [Out] CA_MF_MEDIATYPE_EQUAL% Param_Out_ResultadoCompare)
{
	//Variavel que vai retornar o resultado do método.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFMediaType* pMediaTypeCompare = NULL;
	DWORD FlagsComparação = 0;

	//Obtém a interface não gerenciada na interface fornecedia pelo usuário
	Resultado = Param_MidiaCompare->RecuperarPonteiro((LPVOID*)&pMediaTypeCompare);

	//Verifica se obteve com sucesso a interface.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método.
		goto Done;
	}

	//Chama o método para comparar a interface.
	Hr = PonteiroTrabalho->IsEqual(pMediaTypeCompare, &FlagsComparação);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}





// Métodos da interface (ICarenMFAttributes)


/// <summary>
/// Compara os atributos neste objeto com os atributos em outro objeto.
/// </summary>
/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
CarenResult CarenMFMediaType::Compare(ICarenMFAttributes^ Param_InterfaceCompare, CA_MF_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, [Out] Boolean% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAttributesCompare = Nulo;
	MF_ATTRIBUTES_MATCH_TYPE vi_CompareType = static_cast<MF_ATTRIBUTES_MATCH_TYPE>(Param_TipoComparação);
	BOOL vi_Resultado = FALSE;

	//Chama o método para obter a interface(IMFAttributes) que será comparada a está.
	CarenGetPointerFromICarenSafe(Param_InterfaceCompare, vi_pAttributesCompare);

	//Chama o método para comparar os itens
	Hr = PonteiroTrabalho->Compare(
		vi_pAttributesCompare,
		vi_CompareType,
		&vi_Resultado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o resultado da comparação.
	Param_Out_Resultado = vi_Resultado ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
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
CarenResult CarenMFMediaType::CompareItem(String^ Param_GuidChave, CA_PROPVARIANT^ Param_Valor, [Out] Boolean% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_GuidChave = GUID_NULL;
	LPPROPVARIANT vi_PropVar = Nulo;
	BOOL vi_ResultadoCompare = FALSE;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para tentar converter a CA_PROPVARIANT gerenciada para a nativa.
	CarenConvertPropvariantToNativeSafe(Param_Valor, vi_PropVar);

	//Chama o método para compar o item.
	Hr = PonteiroTrabalho->CompareItem(
		const_cast<GUID&>(vi_GuidChave),
		const_cast<PROPVARIANT&>(*vi_PropVar),
		&vi_ResultadoCompare);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o resultado da comparação
	Param_Out_Resultado = vi_ResultadoCompare ? true : false;

Done:;
	//Libera a memória utilizada pela PropVariant.
	DeletarPropVariantSafe(&vi_PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
/// </summary>
/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
CarenResult CarenMFMediaType::CopyAllItems(ICarenMFAttributes^ Param_Out_InterfaceDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis que o método vai usar
	IMFAttributes* vi_pInterfaceDest = Nulo;

	//Tenta recuperar o ponteiro para a interface de destino que vai receber os atributos.
	CarenGetPointerFromICarenSafe(Param_Out_InterfaceDestino, vi_pInterfaceDest);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyAllItems(vi_pInterfaceDest);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os pares chave/valor da lista de atributos do objeto.
/// </summary>
CarenResult CarenMFMediaType::DeleteAllItems()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DeleteAllItems();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove um emparelhar chave/valor da lista de atributos do objeto.
/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
/// </summary>
/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
CarenResult CarenMFMediaType::DeleteItem(String^ Param_GuidChave)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DeleteItem(const_cast<GUID&>(vi_GuidChave));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}


// GET METHODS


/// <summary>
/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
/// memória para a matriz.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
CarenResult CarenMFMediaType::GetAllocatedBlob(String^ Param_GuidChave, [Out] Estruturas::CA_BlobData% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	PBYTE vi_pOutBuffer = NULL;
	UINT32 vi_OutLarguraBlob = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAllocatedBlob(const_cast<GUID&>(vi_GuidChave), &vi_pOutBuffer, &vi_OutLarguraBlob);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a estrutura a ser retornada com os dados.
	Param_Out_Buffer = CA_BlobData();

	//Define a largura do buffer
	Param_Out_Buffer.SizeData = vi_OutLarguraBlob;

	//Cria a interface que vai conter os dados do buffer.
	Param_Out_Buffer.BufferDados = gcnew CarenBuffer();

	//Copia os dados para o buffer
	static_cast<ICarenBuffer^>(Param_Out_Buffer.BufferDados)->CreateBuffer(IntPtr(vi_pOutBuffer), true, Param_Out_Buffer.SizeData, Param_Out_Buffer.SizeData);

Done:;
	//Libera a memória para o buffer se válido.
	if (ObjetoValido(vi_pOutBuffer))
		CoTaskMemFree(vi_pOutBuffer);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma sequência de caracteres largos associada a uma chave. 
/// Este método aloca a memória para a seqüência de caracteres.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
CarenResult CarenMFMediaType::GetAllocatedString(String^ Param_GuidChave, [Out] String^% Param_Out_String, [Out] UInt32% Param_Out_LarguraString)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	LPWSTR vi_pOutString = NULL;
	UINT32 vi_OutLarguraBuffer = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAllocatedString(const_cast<GUID&>(vi_GuidChave), &vi_pOutString, &vi_OutLarguraBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_String = gcnew String(vi_pOutString);
	Param_Out_LarguraString = vi_OutLarguraBuffer;

Done:;
	//Libera a memória utilizada pela String se válida.
	DeletarStringCoTaskSafe(&vi_pOutString);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma matriz de byte associada a uma chave. 
/// Esse método copia a matriz em um buffer alocado pelo chamador.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (GetBlobSize) para obter o valor para esse parametro.</param>
CarenResult CarenMFMediaType::GetBlob(String^ Param_GuidChave, UInt32 Param_TamanhoBuffer, [Out] Estruturas::CA_BlobData% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	PBYTE vi_pOutBuffer = NULL;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Cria o buffer que vai conter os dados.
	vi_pOutBuffer = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_TamanhoBuffer));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBlob(const_cast<GUID&>(vi_GuidChave), vi_pOutBuffer, Param_TamanhoBuffer, NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a estrutura que será retornada.
	Param_Out_Buffer = CA_BlobData();

	//Define a largura do buffer
	Param_Out_Buffer.SizeData = Param_TamanhoBuffer;

	//Cria a interface que vai conter os dados.
	Param_Out_Buffer.BufferDados = gcnew CarenBuffer();

	//Copia os dados para a interface do buffer.
	static_cast<ICarenBuffer^>(Param_Out_Buffer.BufferDados)->CreateBuffer(IntPtr(vi_pOutBuffer), true, Param_Out_Buffer.SizeData, Param_Out_Buffer.SizeData);

Done:;
	//Libera a memória utilizada pela matriz.
	DeletarMatrizUnidimensionalSafe(&vi_pOutBuffer);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o comprimento de uma matriz de byte associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
CarenResult CarenMFMediaType::GetBlobSize(String^ Param_GuidChave, [Out] UInt32% Param_Out_TamanhoBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	UINT32 vi_OutLargura = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBlobSize(const_cast<GUID&>(vi_GuidChave), &vi_OutLargura);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno.
	Param_Out_TamanhoBuffer = vi_OutLargura;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o número de atributos que são definidos neste objeto.
/// </summary>
/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
CarenResult CarenMFMediaType::GetCount([Out] UInt32% Param_QuantidadeAtributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variavel que vai conter a quantidade de atributos.
	UINT32 vi_OutCountAttributes = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCount(&vi_OutCountAttributes);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno.
	Param_QuantidadeAtributos = vi_OutCountAttributes;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor (Double) associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetDouble(String^ Param_GuidChave, [Out] Double% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	GUID vi_GuidChave = GUID_NULL;
	double vi_OutValue = 0;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDouble(const_cast<GUID&>(vi_GuidChave), &vi_OutValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno para o usuário.
	Param_Out_Valor = vi_OutValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor GUID associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetGUID(String^ Param_GuidChave, [Out] String^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	GUID vi_OutGuidValue = GUID_NULL;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGUID(const_cast<GUID&>(vi_GuidChave), &vi_OutGuidValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno para o usuário.
	Param_Out_Valor = Util.ConverterGuidToString(vi_OutGuidValue);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o valor desconhecido associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PROPVARIANT) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetItem(String^ Param_GuidChave, [Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_GuidChave = GUID_NULL;
	LPPROPVARIANT vi_OutPropVar = Nulo;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Inicializa a PropVariant.
	IniciarPropVariant(&vi_OutPropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetItem(const_cast<GUID&>(vi_GuidChave), vi_OutPropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define a estrutura no parametro de saida.
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutPropVar);

Done:;
	//Limpa a PropVariant.
	DeletarPropVariantSafe(&vi_OutPropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um atributo no índice especificado.
/// </summary>
/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetItemByIndex(UInt32 Param_IdItem, [Out] String^% Param_Out_GuidChave, [Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_OutGuidChave = GUID_NULL;
	LPPROPVARIANT vi_OutPropVar = Nulo;

	//Inicializa a PropVariant.
	IniciarPropVariant(&vi_OutPropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetItemByIndex(Param_IdItem, &vi_OutGuidChave, vi_OutPropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define a estrutura de retorno
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutPropVar);

	//Define o guid do valor obtido.
	Param_Out_GuidChave = Util.ConverterGuidToString(vi_OutGuidChave);

Done:;
	//Limpa a PropVariant.
	DeletarPropVariantSafe(&vi_OutPropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o tipo de dados do valor associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
CarenResult CarenMFMediaType::GetItemType(String^ Param_GuidChave, [Out] CA_MF_ATTRIBUTE_TYPE% Param_Out_TipoDado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MF_ATTRIBUTE_TYPE vi_OutItemType;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetItemType(const_cast<GUID&>(vi_GuidChave), &vi_OutItemType);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte o valor e define no parametro de saida.
	Param_Out_TipoDado = static_cast<CA_MF_ATTRIBUTE_TYPE>(vi_OutItemType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma sequência de caracteres largos associada a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: GetStringLength</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
CarenResult CarenMFMediaType::GetString(String^ Param_GuidChave, UInt32 Param_LagruraString, [Out] String^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	LPWSTR vi_pOutString = NULL;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Inicializa a matriz que vai conter a string
	vi_pOutString = CriarMatrizUnidimensional<WCHAR>(Param_LagruraString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetString(const_cast<GUID&>(vi_GuidChave), vi_pOutString, Param_LagruraString, NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno para o usuário.
	Param_Out_Valor = gcnew String(vi_pOutString);

Done:;
	//Libera a memória utilizada para alocar os dados para a string nativa.
	DeletarMatrizUnidimensionalSafe(&vi_pOutString);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
CarenResult CarenMFMediaType::GetStringLength(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	UINT32 vi_OutValue = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStringLength(const_cast<GUID&>(vi_GuidChave), &vi_OutValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno.
	Param_Out_Largura = vi_OutValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor de UInt32 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt32) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetUINT32(String^ Param_GuidChave, [Out] UInt32% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	UINT32 vi_OutValue = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetUINT32(const_cast<GUID&>(vi_GuidChave), &vi_OutValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno para o usuário.
	Param_Out_Valor = vi_OutValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor de UInt64 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetUINT64(String^ Param_GuidChave, [Out] UInt64% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	UINT64 vi_OutValue = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetUINT64(const_cast<GUID&>(vi_GuidChave), &vi_OutValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor de retorno para o usuário.
	Param_Out_Valor = vi_OutValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
/// Ese método recuperar o Numerador e Denominador de uma chave.
/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
CarenResult CarenMFMediaType::_MFGetAttributeRatio(String^ Param_GuidChave, [Out] UInt32% Param_Out_Numerador, [Out] UInt32% Param_Out_Denominador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	UINT32 vi_OutNumerador = 0;
	UINT32 vi_OutDenominador = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = MFGetAttributeRatio(PonteiroTrabalho, const_cast<GUID&>(vi_GuidChave), &vi_OutNumerador, &vi_OutDenominador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define os valores da razão
	Param_Out_Numerador = vi_OutNumerador;
	Param_Out_Denominador = vi_OutDenominador;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
CarenResult CarenMFMediaType::_MFGetAttributeSize(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura, [Out] UInt32% Param_Out_Altura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	UINT32 vi_OutLargura = 0;
	UINT32 vi_OutAltura = 0;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = MFGetAttributeSize(PonteiroTrabalho, const_cast<GUID&>(vi_GuidChave), &vi_OutLargura, &vi_OutAltura);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define os valores do Size.
	Param_Out_Largura = vi_OutLargura;
	Param_Out_Altura = vi_OutAltura;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro par ao objeto desconhecido. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFMediaType::GetUnknown(String^ Param_GuidChave, String^ Param_GuidInterfaceSolicitada, ICaren^ Param_Out_InterfaceDesconhecida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis que seram utilizadas pelo método.
	Utilidades Util;
	GUID vi_GuidChave = GUID_NULL;
	GUID vi_RIIDInterface = GUID_NULL;
	LPVOID vi_pOutInterface = NULL;

	//Chama o método para criar os GUIDs aparti das Strings gerenciadas.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);
	CarenCreateGuidFromStringSafe(Param_GuidInterfaceSolicitada, vi_RIIDInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetUnknown(const_cast<GUID&>(vi_GuidChave), const_cast<IID&>(vi_RIIDInterface), &vi_pOutInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Chama o método para definir o ponteiro desconhecido para a interface.
	CarenSetPointerToICarenSafe(reinterpret_cast<IUnknown*>(vi_pOutInterface), Param_Out_InterfaceDesconhecida, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
/// </summary>
CarenResult CarenMFMediaType::LockStore()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LockStore();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;
	}

	//Retorna o resultado.
	return Resultado;
}


//SET METHODS


/// <summary>
/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Buffer">Uma interface (ICarenBuffer) que contém os dados a serem associados a chave especificada.</param>
CarenResult CarenMFMediaType::SetBlob(String^ Param_GuidChave, ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	GenPointer vi_BufferBlob = DefaultGenPointer;
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Tenta recuperar o ponteiro para o buffer.
	CarenGetPointerFromICarenBufferSafe(Param_Buffer, vi_BufferBlob);

	//Verifica se o usuário informou o tamanho do buffer válido
	if (Param_Buffer->TamanhoValido == 0)
	{
		//O tamanho do buffer especificado na interface é inválido.

		//Define o erro.
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_TAMANHO_INVALIDO, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetBlob(
		const_cast<GUID&>(vi_GuidChave),
		reinterpret_cast<PBYTE>(vi_BufferBlob.ToPointer()),
		Param_Buffer->TamanhoValido);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Associa um valor duplo com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetDouble(String^ Param_GuidChave, Double Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDouble(const_cast<GUID&>(vi_GuidChave), Param_Valor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Associa um valor GUID com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetGUID(String^ Param_GuidChave, String^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	GUID vi_GuidChave = GUID_NULL;
	GUID vi_GuidValue = GUID_NULL;

	//Chama o método para converter as Strings gerenciadas para os GUIDs nativos.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);
	CarenCreateGuidFromStringSafe(Param_Valor, vi_GuidValue);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGUID(const_cast<GUID&>(vi_GuidChave), const_cast<GUID&>(vi_GuidValue));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Adiciona um valor de atributo com uma chave especificada.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetItem(String^ Param_GuidChave, Estruturas::CA_PROPVARIANT^ Param_PropVariantValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_GuidChave = GUID_NULL;
	LPPROPVARIANT vi_Propvar = Nulo;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Converte a PropVariant gerenciada para a nativa.
	CarenConvertPropvariantToNativeSafe(Param_PropVariantValor, vi_Propvar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetItem(const_cast<GUID&>(vi_GuidChave), const_cast<PROPVARIANT&>(*vi_Propvar));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada pela propvariant.
	DeletarPropVariantSafe(&vi_Propvar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Associa uma seqüência de caracteres largos com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetString(String^ Param_GuidChave, String^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	Utilidades Util;
	GUID vi_GuidChave = GUID_NULL;
	LPWSTR vi_pBufferValor = Nulo;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para converter a string gerenciada em nativa.
	vi_pBufferValor = Util.ConverterStringToWCHAR(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetString(const_cast<GUID&>(vi_GuidChave), vi_pBufferValor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada para alocar a string.
	DeletarStringAllocatedSafe(&vi_pBufferValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Associa um valor de UINT32 com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetUINT32(String^ Param_GuidChave, UInt32 Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetUINT32(const_cast<GUID&>(vi_GuidChave), Param_Valor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Associa um UINT64 valor com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetUINT64(String^ Param_GuidChave, UInt64 Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetUINT64(const_cast<GUID&>(vi_GuidChave), Param_Valor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
/// Esse método define no valor da chave uma razão(Numerador e Denominador).
/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Numerador">Define o valor do: Numerador</param>
/// <param name="Param_Denominador">Define o valor do: Denominador</param>
CarenResult CarenMFMediaType::_MFSetAttributeRatio(String^ Param_GuidChave, UInt32 Param_Numerador, UInt32 Param_Denominador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = MFSetAttributeRatio(PonteiroTrabalho, const_cast<GUID&>(vi_GuidChave), Param_Numerador, Param_Denominador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
/// largura e altura em um único valor de UInt64 .
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Largura">A Largura do vídeo em pixels.</param>
/// <param name="Param_Altura">A Altura do vídeo em pixels.</param>
CarenResult CarenMFMediaType::_MFSetAttributeSize(String^ Param_GuidChave, UInt32 Param_Largura, UInt32 Param_Altura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	GUID vi_GuidChave = GUID_NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para realizar a operação.
	Hr = MFSetAttributeSize(PonteiroTrabalho, const_cast<GUID&>(vi_GuidChave), Param_Largura, Param_Altura);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
CarenResult CarenMFMediaType::SetUnknown(String^ Param_GuidChave, ICaren^ Param_InterfaceDesconhecida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas pelo método.
	Utilidades Util;
	GUID vi_GuidChave = GUID_NULL;
	LPVOID vi_pInterfaceSet = NULL;

	//Chama o método para ciar o guid aparti da String gerenciada.
	CarenCreateGuidFromStringSafe(Param_GuidChave, vi_GuidChave);

	//Chama o método para tentar recuperar a interface.
	CarenGetPointerFromICarenSafe(Param_InterfaceDesconhecida, vi_pInterfaceSet);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetUnknown(const_cast<GUID&>(vi_GuidChave), reinterpret_cast<IUnknown*>(vi_pInterfaceSet));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
/// </summary>
CarenResult CarenMFMediaType::UnlockStore()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	HRESULT Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnlockStore();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}