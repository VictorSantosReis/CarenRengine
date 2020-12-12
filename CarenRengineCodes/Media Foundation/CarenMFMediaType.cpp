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
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A operação falhou.
		

		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}


	//Retorna o resultado
	return Resultado;}

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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenMFMediaType::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
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

	//Chama o finalizador da classe
	this->~CarenMFMediaType();
}





//Métodos da interface ICarenMFMediaType.


/// <summary>
/// (GetMajorType) - Obtém o tipo principal da midia: Vídeo ou Áudio.
/// </summary>
/// <param name="Param_Out_GuidTipoMidia">Retorna o GUID do tipo principal da mídia.</param>
/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração com o tipo principal da mídia.</param>
CarenResult CarenMFMediaType::GetMajorType([Out] String^% Param_Out_GuidTipoMidia, [Out] CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal)
{
	//Variavel que vai retornar o resultado do método.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis de retorno do método.
	CA_Midia_TipoPrincipal TipoMidiaEnum;

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
		TipoMidiaEnum = CA_Midia_TipoPrincipal::TP_Audio;
	}

	//Verifica se o tipo principal é vídeo.
	else if (GuidTipoMidia == MFMediaType_Video)
	{
		//Fluxo de Vídeo.
		TipoMidiaEnum = CA_Midia_TipoPrincipal::TP_Video;
	}

	//O tipo não é válido para essa biblioteca.
	else
	{
		//Formato Desconhecido.
		TipoMidiaEnum = CA_Midia_TipoPrincipal::TP_Desconhecido;
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
CarenResult CarenMFMediaType::IsEqual(ICarenMFMediaType^ Param_MidiaCompare, [Out] CA_MEDIA_TYPE_EQUAL% Param_Out_ResultadoCompare)
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


//
//Métodos da interface ICarenMidiaAtribute
//

/// <summary>
/// Compara os atributos neste objeto com os atributos em outro objeto.
/// </summary>
/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
CarenResult CarenMFMediaType::Compare(ICarenMFAttributes^ Param_InterfaceCompare, CA_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, [Out] Boolean% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFAttributes *pAtributosCompare = NULL;
	MF_ATTRIBUTES_MATCH_TYPE Comparador;
	BOOL ResultadoCompare = FALSE;

	//Chama o método para obter a interface(IMFAttributes) que será comparada a está.
	Resultado = Param_InterfaceCompare->RecuperarPonteiro((LPVOID*)&pAtributosCompare);

	//Obtém o tipo de comparação a ser realizada.
	Comparador = (MF_ATTRIBUTES_MATCH_TYPE)((int)Param_TipoComparação);

	//Chama o método para comparar os itens
	Hr = PonteiroTrabalho->Compare(pAtributosCompare, Comparador, &ResultadoCompare);

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
	Param_Out_Resultado = ResultadoCompare ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PropVariant.
/// CA_PropVariant é um Wrapper da PropVariant não gerenciada.
/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PropVariant) é diferente do (Valor) no Atributo,
/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
/// </summary>
/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
CarenResult CarenMFMediaType::CompareItem(String^ Param_GuidChave, CA_PropVariant^ Param_Valor, [Out] Boolean% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	BOOL ResultadoComp = FALSE;
	BLOB BlobData = {};
	char* DadosStringConvertido = NULL;
	WCHAR* DadosWcharToBstr = NULL;
	PROPVARIANT PropVar;

	//Converte a string para guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Verifica se o Guid é valido
	if (GuidChave == GUID_NULL)
	{
		//O guid informado é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Inicia a PropVariant
	PropVariantInit(&PropVar);

	//Chama o método para converter a propvariant gerenciada para nativa.
	bool ConvertPropVariant = Util.ConvertPropVariantManagedToUnamaged(Param_Valor, PropVar);

	//Verifica se obteve sucesso
	if (!ConvertPropVariant)
	{
		//Define falha na conversão da propvariant
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método.
		Sair;
	}

	//Chama o método para compar o item.
	Hr = PonteiroTrabalho->CompareItem(GuidChave, PropVar, &ResultadoComp);

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
	Param_Out_Resultado = ResultadoComp ? true : false;

Done:;
	//Libera as string se forem validas
	if (DadosStringConvertido != NULL)
	{
		//Deleta os dados da string
		delete DadosStringConvertido;
	}
	if (DadosWcharToBstr != NULL)
	{
		//Deleta os dados da string
		delete DadosWcharToBstr;
	}

	//Libera a memória utilizada pela PropVariant.
	PropVariantClear(&PropVar);

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
	IMFAttributes *pAtributoInterfaceDestino;

	//Verifica se a interface é valida
	if (Param_Out_InterfaceDestino == nullptr)
	{
		//O argumento passado é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_INVALIDARG, false);

		//Sai do método.
		goto Done;
	}

	//Chama o método para obter o ponteiro de trabalho na interface
	Resultado = Param_Out_InterfaceDestino->RecuperarPonteiro((LPVOID*)&pAtributoInterfaceDestino);

	//Verifica o resultado da obtenção do ponteiro de trabalho
	//Se ele for nulo, o método Retornado ER_NO_INTERFACE.
	if (Resultado.StatusCode == ResultCode::SS_OK)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O ponteiro de trabalho na interface de destino não é valido.

		//Sai do método
		goto Done;
	}

	//Chama o método que vai copiar os atributos do ponteiro de trabalho dessa classe
	//para o da interface de destino.
	Hr = PonteiroTrabalho->CopyAllItems(pAtributoInterfaceDestino);

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
	
	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

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

	//Chama o método para deletar todos os itens
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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	
	//Converte a string para guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Verifica se o Guid é valido
	if (GuidChave == GUID_NULL)
	{
		//O guid informado é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Chama o método para deletar o item
	//O método retornar S_OK mesmo se a chave não existir no atributo.
	Hr = PonteiroTrabalho->DeleteItem(GuidChave);

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


//Métodos (GET) da interface IMFAttributes.



/// <summary>
/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
/// memória para a matriz.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
CarenResult CarenMFMediaType::GetAllocatedBlob(String^ Param_GuidChave, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	UINT8 *pBuffDados = NULL;
	UINT32 LarguraBuffer = 0;
	GUID GuidChave = GUID_NULL;

	//Converte a string para o GUID.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAllocatedBlob(GuidChave, &pBuffDados, &LarguraBuffer);

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
	Param_Out_Buffer = gcnew CA_BlobData();

	//Define a largura do buffer
	Param_Out_Buffer->SizeData = LarguraBuffer;

	//Cria a interface que vai conter os dados do buffer.
	Param_Out_Buffer->BufferDados = gcnew CarenBuffer();

	//Copia os dados para o buffer
	Param_Out_Buffer->BufferDados->CriarBuffer(IntPtr(pBuffDados), true, Param_Out_Buffer->SizeData, Param_Out_Buffer->SizeData);

Done:;
	//Libera a memória para o buffer se válido.
	if (ObjetoValido(pBuffDados))
		CoTaskMemFree(pBuffDados);

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
	Utilidades Util;
	LPWSTR StringValorRetornado = NULL;
	UINT32 LarguraBuffer = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter a String alocada internamente.
	Hr = PonteiroTrabalho->GetAllocatedString(GuidChave, &StringValorRetornado, &LarguraBuffer);

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
	Param_Out_String = gcnew String(StringValorRetornado);

Done:;
	//Verifica se o Buffer é valido e exclui
	if (StringValorRetornado != NULL)
	{
		//Chama um CoTaskMemFree -> Método indicado pelo Microsoft.
		CoTaskMemFree(StringValorRetornado);
	}

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
CarenResult CarenMFMediaType::GetBlob(String^ Param_GuidChave, UInt32 Param_TamanhoBuffer, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	UINT8 *pBuffDados = NULL;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Cria o buffer que vai conter os dados.
	pBuffDados = CriarMatrizUnidimensional<UINT8>(static_cast<DWORD>(Param_TamanhoBuffer));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBlob(GuidChave, pBuffDados, Param_TamanhoBuffer, NULL);

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
	Param_Out_Buffer = gcnew CA_BlobData();

	//Define a largura do buffer
	Param_Out_Buffer->SizeData = Param_TamanhoBuffer;

	//Cria a interface que vai conter os dados.
	Param_Out_Buffer->BufferDados = gcnew CarenBuffer();
	
	//Copia os dados para a interface do buffer.
	Param_Out_Buffer->BufferDados->CriarBuffer(IntPtr(pBuffDados), true, Param_Out_Buffer->SizeData, Param_Out_Buffer->SizeData);

Done:;
	//Libera a memória utilizada pela matriz.
	DeletarMatrizUnidimensionalSafe(&pBuffDados);

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
	Utilidades Util;
	UINT32 ValorRequisitado = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Obtém o tamanho do blob no guid informado
	Hr = PonteiroTrabalho->GetBlobSize(GuidChave, &ValorRequisitado);

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
	Param_Out_TamanhoBuffer = ValorRequisitado;

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
	UINT32 CountAtributos = 0;

	//Chama o método para obter a quantidade de atributos.
	Hr = PonteiroTrabalho->GetCount(&CountAtributos);

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
	 Param_QuantidadeAtributos = CountAtributos;
	 
	 //Define sucesso na operação
	 Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

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
	Utilidades Util;
	double ValorRequisitado = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetDouble(GuidChave, &ValorRequisitado);

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
	Param_Out_Valor = ValorRequisitado;

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
	GUID ValorRequisitado = GUID_NULL;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetGUID(GuidChave, &ValorRequisitado);

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
	Param_Out_Valor = Util.ConverterGuidToString(ValorRequisitado);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o valor desconhecido associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PropVariant) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetItem(String^ Param_GuidChave, [Out] CA_PropVariant^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	PROPVARIANT PropVar;
	

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Inicializa a PropVariant.
	PropVariantInit(&PropVar);

	//Chama o método para obter o dado
	Hr = PonteiroTrabalho->GetItem(GuidChave, &PropVar);

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
	Param_Out_Valor = Util.ConvertPropVariantUnmanagedToManaged(PropVar);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa a PropVariant.
	PropVariantClear(&PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um atributo no índice especificado.
/// </summary>
/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFMediaType::GetItemByIndex(UInt32 Param_IdItem, [Out] String^% Param_Out_GuidChave, [Out] CA_PropVariant^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	PROPVARIANT PropVar;
	

	//Inicializa a PropVariant.
	PropVariantInit(&PropVar);

	//Chama o método para obter o dado
	Hr = PonteiroTrabalho->GetItemByIndex(Param_IdItem, &GuidChave, &PropVar);

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
	Param_Out_Valor = Util.ConvertPropVariantUnmanagedToManaged(PropVar);

	//Define o guid do valor obtido.
	Param_Out_GuidChave = Util.ConverterGuidToString(GuidChave);

Done:;
	//Limpa a PropVariant.
	PropVariantClear(&PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o tipo de dados do valor associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
CarenResult CarenMFMediaType::GetItemType(String^ Param_GuidChave, [Out] CA_ATTRIBUTE_TYPE% Param_Out_TipoDado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);
	
	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	MF_ATTRIBUTE_TYPE ValorRequisitado;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetItemType(GuidChave, &ValorRequisitado);
	
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

	//Converte o valor retornado para um gerenciado representado pela enumeração CA_ATTRIBUTE_TYPE.
	Param_Out_TipoDado = Util.ConverterMF_ATTRIBUTE_TYPEUnmanagedToManaged(ValorRequisitado);

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
	Utilidades Util;
	WCHAR *ValorRequisitado = NULL;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Inicializa a matriz que vai conter a string
	ValorRequisitado = new wchar_t[Param_LagruraString];

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetString(GuidChave, ValorRequisitado, Param_LagruraString, NULL);

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
	Param_Out_Valor = gcnew String(ValorRequisitado);

Done:;
	//Deleta a string contida aqui
	if (ValorRequisitado != NULL)
	{
		//Deleta o buffer criado para armazenar os dados.
		delete ValorRequisitado;
	}

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
	Utilidades Util;
	UINT32 ValorRequisitado = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter a largura da string.
	Hr = PonteiroTrabalho->GetStringLength(GuidChave, &ValorRequisitado);

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
	Param_Out_Largura = ValorRequisitado;

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
	Utilidades Util;
	UINT32 ValorRequisitado = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetUINT32(GuidChave, &ValorRequisitado);

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
	Param_Out_Valor = ValorRequisitado;

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
	Utilidades Util;
	UINT64 ValorRequisitado = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter o valor
	Hr = PonteiroTrabalho->GetUINT64(GuidChave, &ValorRequisitado);

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
	Param_Out_Valor = ValorRequisitado;

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
	Utilidades Util;
	UINT32 Valor_Numerador = 0;
	UINT32 Valor_Denominador = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter os valores.
	Hr = MFGetAttributeRatio(PonteiroTrabalho, GuidChave, &Valor_Numerador, &Valor_Denominador);

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
	Param_Out_Numerador = Valor_Numerador;
	Param_Out_Denominador = Valor_Denominador;

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
	UINT32 Valor_Largura = 0;
	UINT32 Valor_Altura = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter os valores.
	Hr = MFGetAttributeSize(PonteiroTrabalho, GuidChave, &Valor_Largura, &Valor_Altura);

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
	Param_Out_Largura = Valor_Largura;
	Param_Out_Altura = Valor_Altura;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro par ao objeto desconhecido. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenMFMediaType::GetUnknown(String^ Param_GuidChave, String^ Param_GuidInterfaceSolicitada, ICaren^ Param_Out_InterfaceDesconhecida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis que seram utilizadas pelo método.
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	GUID GuidInterfaceSolicitada = GUID_NULL;
	LPVOID pInterfaceRetornada = NULL;

	//Chama o método para obter os guids.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);
	GuidInterfaceSolicitada = Util.CreateGuidFromString(Param_GuidInterfaceSolicitada);

	//Verifica se os guids foram criados com sucesso
	if (GuidChave == GUID_NULL || GuidInterfaceSolicitada == GUID_NULL)
	{
		//O guid informado não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Chama o método para obter a interface.
	Hr = PonteiroTrabalho->GetUnknown(GuidChave, GuidInterfaceSolicitada, &pInterfaceRetornada);
	
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
	Param_Out_InterfaceDesconhecida->AdicionarPonteiro(pInterfaceRetornada);

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

	//Chama o método que vai bloquear o armazenamento de atributos para outros threads.
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



//Métodos (SET) da interface IMFAttributes.




/// <summary>
/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Buffer">A matriz de bytes a ser associada a chave especificada.</param>
CarenResult CarenMFMediaType::SetBlob(String^ Param_GuidChave, cli::array<Byte>^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	BYTE* pBlobData = NULL;
	UINT32 ArraySize = 0;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Obtém a largura do buffer
	ArraySize = Param_Buffer->Length;

	//Cria o buffer que vai conter os dados.
	pBlobData = new BYTE[ArraySize];

	//Copia os dados para o buffer
	Marshal::Copy(Param_Buffer, 0, IntPtr(pBlobData), ArraySize);

	//Chama o método para definir o BlobData.
	//O método vai realizar uma copia da matriz.
	Hr = PonteiroTrabalho->SetBlob(GuidChave, pBlobData, ArraySize);

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
	//Deleta a matriz se ela for valida.
	if (pBlobData != NULL)
	{
		//Deleta os dados.
		delete[] pBlobData;
	}

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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para definir o valor
	Hr = PonteiroTrabalho->SetDouble(GuidChave, Param_Valor);

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
	Utilidades Util;
	GUID Chave = Util.CreateGuidFromString(Param_GuidChave);
	GUID Valor = Util.CreateGuidFromString(Param_Valor);

	//Chama o método que vai definir o valor do Guid no atributo.
	Hr = PonteiroTrabalho->SetGUID(Chave, Valor);

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
	//Limpa os dados.
	Chave = GUID_NULL;
	Valor = GUID_NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Adiciona um valor de atributo com uma chave especificada.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
CarenResult CarenMFMediaType::SetItem(String^ Param_GuidChave, Estruturas::CA_PropVariant^ Param_PropVariantValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	PROPVARIANT PropVar;
	BLOB BlobData = {};
	IUnknown *pInterfaceDesconhecida = NULL;
	char* StringData = NULL;
	bool ResultCreatePropVariant = false;

	//Inicializa a PropVariant.
	PropVariantInit(&PropVar);

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);


	//Converte os dados gerenciados para o nativo
	ResultCreatePropVariant = Util.ConvertPropVariantManagedToUnamaged(Param_PropVariantValor, PropVar);

	//Verifica o resultado
	if (!ResultCreatePropVariant)
	{
		//Define falha ao converter.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para definir o valor.
	Hr = PonteiroTrabalho->SetItem(GuidChave, PropVar);

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
	//Limpa a string
	if (StringData != NULL)
	{
		//Deleta os dados armazenados.
		delete StringData;
	}

	//Deleta o BlobData.
	if (BlobData.pBlobData != NULL)
	{
		//Deleta o Blob da memoria.
		delete BlobData.pBlobData;
	}

	//Limpa a PropVariant.
	PropVariantClear(&PropVar);

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
	GUID GuidChave = GUID_NULL;
	LPCWSTR wCharData = NULL;
	char* DadosConvertidos = NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Converte a string
	DadosConvertidos = Util.ConverterStringToChar(Param_Valor);

	//Converte o char para um WCHAR
	wCharData = Util.ConverterConstCharToConstWCHAR(DadosConvertidos);

	//Chama o método para definir o valor
	//O método vai criar uma copia da string.
	Hr = PonteiroTrabalho->SetString(GuidChave, wCharData);

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
	//Deleta as strings.
	if (DadosConvertidos != NULL)
	{
		//Deleta a memoria para os dados.
		delete DadosConvertidos;
	}
	if (wCharData != NULL)
	{
		//Deleta a memoria para os dados.
		delete wCharData;
	}

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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para definir o valor
	Hr = PonteiroTrabalho->SetUINT32(GuidChave, Param_Valor);

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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para definir o valor
	Hr = PonteiroTrabalho->SetUINT64(GuidChave, Param_Valor);

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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método que vai definir os valores do Ratio.
	Hr = MFSetAttributeRatio(PonteiroTrabalho, GuidChave, Param_Numerador, Param_Denominador);

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
	Utilidades Util;
	GUID GuidChave = GUID_NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método que vai definir os valores de altura e largura.
	Hr = MFSetAttributeSize(PonteiroTrabalho, GuidChave, Param_Largura, Param_Altura);

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
	GUID GuidChave = GUID_NULL;
	LPVOID pNativeInterfaceDesconhecida = NULL;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidChave);

	//Chama o método para obter a interface desconhecida a ser adicionada.
	Resultado = Param_InterfaceDesconhecida->RecuperarPonteiro(&pNativeInterfaceDesconhecida);

	//Verifica se obteve com sucesso o ponteiro desconhecido
	if (Resultado.StatusCode == ResultCode::SS_OK)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao obter o ponteiro. O método já define o erro ocorrido.

		//Sai do método
		goto Done;
	}

	//Chama o método para definir o ponteiro desconhecido nos atributos.
	Hr = PonteiroTrabalho->SetUnknown(GuidChave, (IUnknown*)pNativeInterfaceDesconhecida);

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

	//Chama o método para desbloquear o armazenado.
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




//
// Métodos da interface ICarenMidiaExtensões
//


/// <summary>
/// (Extensão) - Método responsável por obter o tipo principal da mídia. 
/// </summary>
/// <param name="Param_Out_TipoPrincipal">Recebe o tipo principal da mídia(Áudio ou Vídeo).</param>
/// <param name="Param_Out_Guid">Recebe o Guid do formato principal.</param>
CarenResult CarenMFMediaType::ObterTipoPrincipalMidia([Out] Enumeracoes::CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal, [Out] String^% Param_Out_Guid)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas no método
	ResultadoCOM  Hr = E_FAIL;
	GUID GuidTipoPrincipal = GUID_NULL;
	Utilidades Util;

	//Obtém o guid o formato principal da mídia.
	Hr = PonteiroTrabalho->GetGUID(MF_MT_MAJOR_TYPE, &GuidTipoPrincipal);

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

	//Verifica o tipo principal da midia
	if (GuidTipoPrincipal == MFMediaType_Audio)
	{
		//O tipo principal da mídia é Áudio.
		Param_Out_TipoPrincipal = CA_Midia_TipoPrincipal::TP_Audio;
		//Define o Guid
		Param_Out_Guid = Util.ConverterGuidToString(MFMediaType_Audio);
	}
	else if (GuidTipoPrincipal == MFMediaType_Video)
	{
		//O tipo principal da mídia é Vídeo.
		Param_Out_TipoPrincipal = CA_Midia_TipoPrincipal::TP_Video;
		//Define o Guid
		Param_Out_Guid = Util.ConverterGuidToString(MFMediaType_Video);
	}
	else
	{
		//Tipo desconhecido.
		Param_Out_TipoPrincipal = CA_Midia_TipoPrincipal::TP_Desconhecido;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}


/// <summary>
/// (Extensão) - Método responsável por retornar o formato do tipo principal da mídia. 
/// </summary>
/// <param name="Param_Out_FormatoMidia">Recebe o subtipo(Formato) da mídia principal.</param>
/// <param name="Param_Out_GuidFormato">Recebe o Guid do subtipo(Formato).</param>
CarenResult CarenMFMediaType::ObterFormatoMidia([Out] CA_Midia_SubTipo% Param_Out_FormatoMidia, [Out] String^% Param_Out_GuidFormato)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas no método
	ResultadoCOM  Hr = E_FAIL;
	GUID GuidFormatoMidia = GUID_NULL;
	Utilidades Util;

	//Obtém o guid para o Subtipo da midia
	//O subtipo é o formato da mídia principal.
	Hr = PonteiroTrabalho->GetGUID(MF_MT_SUBTYPE, &GuidFormatoMidia);

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

		//Obtém o formato de midia.
	Param_Out_FormatoMidia = Util.ConverterGUIDSubtipoMidia_ToMidia_SubTipo(GuidFormatoMidia);

	//Converte o GUID do formato para String
	Param_Out_GuidFormato = Util.ConverterGuidToString(GuidFormatoMidia);

Done:;
	//Retorna o valor
	return Resultado;
}
