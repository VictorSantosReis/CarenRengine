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


#include "..\pch.h"
#include "CarenMFSourceReader.h"


//Destruidor.
CarenMFSourceReader::~CarenMFSourceReader()
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
CarenResult CarenMFSourceReader::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFSourceReader::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceReader*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFSourceReader::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceReader*>(Param_PonteiroNativo);

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
CarenResult CarenMFSourceReader::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceReader::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceReader::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFSourceReader::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSourceReader::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSourceReader::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceReader::LiberarReferencia()
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
void CarenMFSourceReader::LimparDados()
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
void CarenMFSourceReader::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFSourceReader();
}



//
// Métodos da interface proprietaria
//


/// <summary>
/// Obtém o tipo de mídia atual para um fluxo.
/// </summary>
/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
CarenResult CarenMFSourceReader::ObterTipoMidiaAtual(UInt32 Param_IdFluxo, [Out] ICarenMFMediaType^% Param_Out_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaType *pTipoMidia = NULL;
	ICarenMFMediaType^ MidiaTypeInterface = nullptr;

	//Chama o método que vai obter o tipo da midia atual.
	Hr = PonteiroTrabalho->GetCurrentMediaType(Param_IdFluxo, &pTipoMidia);

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

	//Cria a interface gerenciada que vai conter o tipo da midia
	MidiaTypeInterface = gcnew CarenMFMediaType();

	//Chama o método que vai definir o ponteiro de trabalho na interface.
	MidiaTypeInterface->AdicionarPonteiro(pTipoMidia);

	//Define a interface a ser retornada.
	Param_Out_TipoMidia = MidiaTypeInterface;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um formato que é suportado nativamente pelo fonte de mídia.
/// Este método consulta a fonte de mídia subjacente para seu (Formato) de (Saída Nativo). 
/// Potencialmente, cada fluxo de origem pode produzir mais de um formato de saída. 
/// Use o parâmetro Param_IdMediaTypeIndice para percorrer os formatos disponíveis
/// </summary>
/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
/// <param name="Param_IdMediaTypeIndice">O Id para o tipo de mídia na lista a ser obtida. O valor pode ser qualquer um dos seguintes. Indice baseado em 0 ou o valor: 0xffffffff que representa o tipo da mídia nativa atual. </param>
/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
CarenResult CarenMFSourceReader::ObterTipoMidiaNativa(UInt32 Param_IdFluxo, UInt32 Param_IdMediaTypeIndice, [Out] ICarenMFMediaType^% Param_Out_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaType *pTipoMidia = NULL;
	ICarenMFMediaType^ MidiaTypeInterface = nullptr;

	//Chama o método que vai obter o tipo da midia atual.
	Hr = PonteiroTrabalho->GetNativeMediaType(Param_IdFluxo, Param_IdMediaTypeIndice, &pTipoMidia);

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

	//Cria a interface gerenciada que vai conter o tipo da midia
	MidiaTypeInterface = gcnew CarenMFMediaType();

	//Chama o método que vai definir o ponteiro de trabalho na interface.
	MidiaTypeInterface->AdicionarPonteiro(pTipoMidia);

	//Define a interface a ser retornada.
	Param_Out_TipoMidia = MidiaTypeInterface;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um determinado atributo da fonte de mídia atual.
/// </summary>
/// <param name="Param_IdFluxo">O fluxo ou objeto de consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID) para espeficar um valor padrão ao sistema.</param>
/// <param name="Param_GuidAtributo">Um GUID que identifica o atributo para recuperar. Se o Param_IdFluxo parâmetro é igual a ID_FONTE_MIDIA, 
/// Param_GuidAtributo pode especificar os atributos de: MFAtributos_DescritorApresentação, MF_SOURCE_READER_MEDIASOURCE_CHARACTERISTICS.
/// Se Param_IdFluxo espeficifica um Fluxo, Param_GuidAtributo deve especificar um atributo do Descritor de Fluxo(GUIDs_MFAtributos_DescritorFluxo) </param>
/// <param name="Param_Out_ValorAtributo">Retorna o valor do atributo solicitado</param>
CarenResult CarenMFSourceReader::ObterAtributoApresentacao(UInt32 Param_IdFluxo, String^ Param_GuidAtributo, [Out] Estruturas::CA_PropVariant^% Param_Out_ValorAtributo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidChave = GUID_NULL;
	PROPVARIANT PropVar;
	PropVariantManager PropManager;

	//Chama o método para obter o guid.
	GuidChave = Util.CreateGuidFromString(Param_GuidAtributo);

	//Verifica se o guid foi criado com sucesso
	if (GuidChave == GUID_NULL)
	{
		//O guid informado não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Inicializa a PropVariant.
	PropVariantInit(&PropVar);

	//Chama o método para obter o dados do atributo.
	Hr = PonteiroTrabalho->GetPresentationAttribute(Param_IdFluxo, GuidChave, &PropVar);

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

	//Converte a estrutura nativa para gerenciada e define na estrutura de saida.
	Param_Out_ValorAtributo = PropManager.ConvertPropVariantUnmanagedToManaged(PropVar);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa a PropVariant.
	PropVariantClear(&PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// () - Consulta a fonte subjacente de mídia ou decodificador para uma interface.
/// </summary>
/// <param name="Param_IdFluxo">O fluxo ou objeto para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID). Se o valor for ID_FONTE_MIDIA, 
/// o método consultará a fonte de mídia. Caso contrário, ele consulta o decodificador que está associado com o fluxo especificado.</param>
/// <param name="Param_GuidServiço">Um identificador de serviço GUID, consulte a estrutura(MFInterfacesServiço) para  obter um GUID. Se o valor for (NULO), 
/// o método chama (ConsultarInterface) para obter a interface solicitada. Caso contrário, o método chama o ICarenMFGetService.ObterServiço.</param>
/// <param name="Param_GuidInterface">O identificador de interface (IID) da interface que está sendo solicitada..</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface que foi solicitada. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceReader::ObterServiceParaFluxo(UInt32 Param_IdFluxo, String^ Param_GuidServiço, String^ Param_GuidInterface, ICaren^ Param_Out_InterfaceDesconhecida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidService = GUID_NULL;
	GUID GuidInterface = GUID_NULL;
	LPVOID OutInterfaceNativa = NULL;

	//Chama o método para obter o guid da interface.
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Verifica se o guid foi criado com sucesso
	if (GuidInterface == GUID_NULL)
	{
		//O guid informado não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se o Guid de seriço é valido.
	//Essa função pode consultar a interface diretamente sem o guid de serviço.
	if (!String::IsNullOrEmpty(Param_GuidServiço))
	{
		//Chama o método para obter o guid do serviço.
		GuidService = Util.CreateGuidFromString(Param_GuidServiço);

		//Verifica se o guid foi criado com sucesso
		if (GuidService == GUID_NULL)
		{
			//O guid informado não é valido
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//Sai do método.
			goto Done;
		}
	}
	else
	{
		//Deixa o método continuar.
	}

	//Chama o método para consultar.
	Hr = PonteiroTrabalho->GetServiceForStream(Param_IdFluxo, GuidService, GuidInterface, &OutInterfaceNativa);

	//Verifica o resultado da operação
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	
	else
	{
		//Define falha no método.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o código de erro
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		goto Done;
	}

	//Define o ponteiro para o ponteiro de trabalho
	Param_Out_InterfaceDesconhecida->AdicionarPonteiro(OutInterfaceNativa);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Consulta se um determinado fluxo, baseado em seu (Id) está selecionado.
/// </summary>
/// <param name="Param_IdFluxo">O Fluxo para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
/// <param name="Param_Out_ResultadoFluxoSelecionado">Recebe true se o fluxo é selecionado e irá gerar dados. Recebe false se o fluxo não está selecionado 
/// e não irá gerar dados.</param>
CarenResult CarenMFSourceReader::ConsultarFluxoSelecionado(UInt32 Param_IdFluxo, [Out] Boolean% Param_Out_ResultadoFluxoSelecionado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	BOOL EstadoSelection = FALSE;

	//Chama o método para obter o estado de seleção para o fluxo especificado no ID.
	Hr = PonteiroTrabalho->GetStreamSelection(Param_IdFluxo, &EstadoSelection);

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
/// Método responsável por ler a proxima amostra de mídia disponivel na fonte de mídia.
/// Esse método pode retornar (Sucesso) e ainda assim retornar uma amostra de mídia (NULA).
/// Consulte o resultado do parametro (Param_Out_FlagsLeituraAmostra) que vai indicar o resultado da leitura e o que se deve fazer.
/// </summary>
/// <param name="Param_IdFluxo">O Id do fluxo que vai extrair os dados de mídia. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
/// <param name="Param_ControlFlag">Um flag para realizar a leitura da amostra de mídia. Pode deixar Zero, ou definir um valor da enumeração(CA_SOURCE_READER_CONTROL_FLAG)</param>
/// <param name="Param_Out_ResultadoLeitura">Retorna o resultado da leitura de uma amostra.</param>
/// <param name="Param_Out_IdFluxoLido">Retorna o Id do fluxo que foi extraido a amostra de mídia.</param>
/// <param name="Param_Out_FlagsLeituraAmostra">Retorna um (Flag) que indca um resultado adicional a leitura da amostra. Utilize essa valor para decidir como deve processar o resultado do método.</param>
/// <param name="Param_Out_TimSpanAmostra">Retorna o (TimeSpan) da amostra de mídia lida. TimeSpan indica a Data/Hora que deve iniciar uma amostra. Esse valor é dado em (unidades de 100 Nanosegundos).</param>
/// <param name="Param_Out_Amostra">Retorna a interface que contém a amostra de mídia que foi lida.</param>
CarenResult CarenMFSourceReader::LerAmostra(UInt32 Param_IdFluxo, UInt32 Param_ControlFlag, [Out] Enumeracoes::CA_AMOSTRA_RESULTADO% Param_Out_ResultadoLeitura, [Out] UInt32% Param_Out_IdFluxoLido, [Out] Enumeracoes::CA_SOURCE_READER_FLAGS% Param_Out_FlagsLeituraAmostra, [Out] Int64% Param_Out_TimSpanAmostra, [Out] ICarenMFSample^% Param_Out_Amostra)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	ICarenMFSample^ AmostraMidia = nullptr;
	IMFSample *pSampleAmostra = NULL;
	DWORD IdFluxoLido = 0;
	INT64 TimeSpanAmostra = 0;
	DWORD ReaderFlagsNative = 0;

	//Chama o método para ler a amostra de mídia.
	Hr = PonteiroTrabalho->ReadSample(Param_IdFluxo, Param_ControlFlag, &IdFluxoLido, &ReaderFlagsNative, &TimeSpanAmostra, &pSampleAmostra);

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

	//Determina o Id do fluxo.
	Param_Out_IdFluxoLido = IdFluxoLido;
	//Determina os flags de leitura da amostra de mídia.
	Param_Out_FlagsLeituraAmostra = (CA_SOURCE_READER_FLAGS)ReaderFlagsNative;
	//Define o TimeSpan da amostra
	Param_Out_TimSpanAmostra = TimeSpanAmostra;

	//Verifica os Flags para determina o retorno

	//Determina que o tipo de dados(Formato) foi modificado.
	if (ReaderFlagsNative & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
	{
		//Determina que já chegou no final do fluxo.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::TipoModificado;

		//Sai do método
		goto Done;
	}

	//Indica que já alcançou o final de fluxo e não há mais Simples a serem lidas.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_ENDOFSTREAM)
	{
		//Determina que já chegou no final do fluxo.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::FimFluxo;

		//Sai do método
		goto Done;
	}

	//Indica que houve um erro ao ler os dados.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_ERROR)
	{
		//Determina que houve uma falha ao ler os dados da midia.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::Erro;

		//Sai do método
		goto Done;
	}

	//Indica que houve uma lacuna no fluxo.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_STREAMTICK)
	{
		//Define que houve uma lacuna no fluxo.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::LacunaFluxo;

		//Sai do método
		goto Done;
	}

	//Indica que o tipo da midia nativa foi modificada.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED)
	{
		//Define que o tipo nativo foi modificado.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::TipoNativoModificado;

		//Sai do método
		goto Done;
	}

	//Indica que o decodificador definido pelo usuário foi removido manualmente ou devido a uma modificação do tipo da midia sendo lida.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_ALLEFFECTSREMOVED)
	{
		//Define que o decodificador foi removido
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::DecodificadorRemovido;

		//Sai do método
		goto Done;
	}

	//(MF_SOURCE_READERF_NEWSTREAM) Indica que novos fluxos de midia foram adicionados. O usuário deve selecionar novamente o fluxo a ser decodificado.
	else if (ReaderFlagsNative & MF_SOURCE_READERF_NEWSTREAM)
	{
		//Define que um novo Stream de midia foi adicionado e que é necessário selcionar novamente o fluxo de midia desejado.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::NovoFluxo;

		//Sai do método
		goto Done;
	}

	//Pode continuar normalmente.
	else
	{	
		//Deixa o método continuar.
	}

	//Indica que não há Samples não posição lida. Deve ler a proxima amostra de mídia.
	if (pSampleAmostra == NULL)
	{
		//Determina que não há dados e que deve ler a proxima amostra de mídia.
		Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::NoData;

		//Sai do método
		goto Done;
	}

	//Cria a interface gerenciada que vai conter a amostra
	AmostraMidia = gcnew CarenMFSample();

	//Chama o método para definir o ponteiro de trabalho na interface
	AmostraMidia->AdicionarPonteiro(pSampleAmostra);

	//Define a interface com a amostra lida.
	Param_Out_Amostra = AmostraMidia;

	//Determina que há dados para serem processados.
	Param_Out_ResultadoLeitura = CA_AMOSTRA_RESULTADO::Sucesso;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por ler a proxima amostra de mídia disponivel na fonte de mídia de modo assincrono.
/// Esse método retorna imediatamente após a chamada.
/// </summary>
/// <param name="Param_IdFluxo">O Id do fluxo que vai extrair os dados de mídia. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
/// <param name="Param_ControlFlag">Um flag para realizar a leitura da amostra de mídia. Pode deixar Zero, ou definir um valor da enumeração(CA_SOURCE_READER_CONTROL_FLAG)</param>
CarenResult CarenMFSourceReader::LerAmostraAsync(UInt32 Param_IdFluxo, UInt32 Param_ControlFlag)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para ler a amostra de mídia de forma Assincrona.
	Hr = PonteiroTrabalho->ReadSample(Param_IdFluxo, Param_ControlFlag, NULL, NULL, NULL, NULL);

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
/// Define o tipo de mídia para um fluxo.
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo a ter o tipo de mídia definido. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
/// <param name="Param_ValorReservado">Valor reservado. Define como: 0</param>
/// <param name="Param_TipoMidia">A interface com o (Tipo Mídia) a ser definida como o tipo atual.</param>
CarenResult CarenMFSourceReader::DefinirTipoMidiaAtual(UInt32 Param_IdFluxo, UInt32 Param_ValorReservado, ICarenMFMediaType^ Param_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaType *pTipoMidia = NULL;

	//Chama o método que vai obter a interface não gerenciada (IMFMediaTypes).
	Resultado = Param_TipoMidia->RecuperarPonteiro((LPVOID*)&pTipoMidia);

	//Verifica se obteve sucesso
	if (Resultado.StatusCode == ResultCode::SS_OK)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Sai do método
		goto Done;
	}

	//Chama o método que vai obter o tipo da midia atual.
	Hr = PonteiroTrabalho->SetCurrentMediaType(Param_IdFluxo, NULL, pTipoMidia);

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
/// Define uma nova posição para ler as amostras de midia com base no tempo da apresentação.
/// </summary>
/// <param name="Param_PosiçãoNanoSegundos">A posição para leitura dos dados. O valor é dado em unidades de 100 nanosegundos.</param>
CarenResult CarenMFSourceReader::DefinirPosicaoLeitura(Int64 Param_PosiçãoNanoSegundos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	PROPVARIANT PropVarPosition;

	//Chama o método para criar a propVariant.
	InitPropVariantFromInt64(Param_PosiçãoNanoSegundos, &PropVarPosition);

	/*
	//Define o tipo da PropVariant
	PropVarPosition.vt = VT_I8;

	//Define a posição em nanosegundos -> Long Long
	PropVarPosition.hVal.QuadPart = Param_PosiçãoNanoSegundos;
	*/

	//Chama o método que vai definir a posição de leitura.
	//GUID_NULL -> Informa que o formato do tempo é baseado em unidades de 100 nanosegundos.
	Hr = PonteiroTrabalho->SetCurrentPosition(GUID_NULL, PropVarPosition);

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
	//Limpa a PropVariant
	PropVariantClear(&PropVarPosition);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Seleciona ou Desseleciona um ou mais fluxos.
/// [ATENCAO] - Se você (não vai precisar) de (dados) de um dos (Fluxos), é uma boa ideia para cancelar a seleção desse fluxo. Se o fluxo for 
/// seleccionado, a fonte de mídia pode segurar uma fila de dados não lidos, e a fila pode crescer indefinidamente, consumindo memória e 
/// consequentemente, gerando um Vazamento de memória(Memory Leak).
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo a ser selecionado. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
/// <param name="Param_EstadoSeleção">Define se deve (Selecionar) ou (Desselecionar) o fluxo especificado.</param>
CarenResult CarenMFSourceReader::DefinirEstadoSelecaoFluxo(UInt32 Param_IdFluxo, Boolean Param_EstadoSeleção)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir a seleção do fluxo
	Hr = PonteiroTrabalho->SetStreamSelection(Param_IdFluxo, Param_EstadoSeleção ? TRUE : FALSE);

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
/// Libera um ou mais fluxos.
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo a ser (Liberado). Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
CarenResult CarenMFSourceReader::Flush(UInt32 Param_IdFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para liberar o fluxo especificado.
	Hr = PonteiroTrabalho->Flush(Param_IdFluxo);

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
// Métodos da interface de (Extensão) ICarenLeitorMidiaExtensões
//


/// <summary>
/// (Extensão) - Método responsável por retornar a quantidade de fluxos na mídia carregada pelo leitor.
/// </summary>
/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na mídia carregada.</param>
CarenResult CarenMFSourceReader::ExRecuperarQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizados no método.
	long CountFluxos = 0;
	int Idfluxo = 0;

	//Abre um laço para ficar obtendo os tipos de midia para calcular a quantidade de Fluxos.
	while (true)
	{
		//Vai conter o tipo temporario.
		IMFMediaType* pTipo = NULL;

		//Obtém o tipo no ID de fluxo.
		Hr = PonteiroTrabalho->GetCurrentMediaType(Idfluxo, &pTipo);

		//Verifica o resultado do método.
		if (Sucesso(Hr))
		{
			//Incrementa a quantidade de fluxos no arquivo.
			CountFluxos += 1;

			//Libera os dados do IMFMediaType.
			pTipo->Release();
			pTipo = NULL;

			//Define suceso até segunda ordem.
			Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
		}

		//Não existe mais fluxos no arquivo. Sai do laço.
		else if (Hr == MF_E_INVALIDSTREAMNUMBER)
		{
			//Não existe mais fluxos no arquivo

			//Sai do laço
			break;
		}

		//Falhou ao obter o tipo atual.
		else
		{
			//Define que o método falhou.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do for
			break;
		}

		//Incrementa o Id de fluxo
		Idfluxo += 1;
	}

	//Verifica o resultado
	if (Resultado.StatusCode == ResultCode::SS_OK)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define o código de erro
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		goto Done;
	}

	//Define a quantidade de fluxos.
	Param_Out_QuantidadeFluxos = CountFluxos;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Extensão) - Método responsável por retornar todos os tipos principais de mídia do arquivo carregado pelo leitor.
/// </summary>
/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de mídia no fluxo carregado</param>
CarenResult CarenMFSourceReader::ExRecuperarTiposMidia([Out] List<CA_Midia_TipoPrincipal>^% Param_Out_TiposMidias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados Com.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFMediaType* pTipoMidia = NULL;
	GUID GUID_TipoPrincipalFluxo = GUID_NULL;
	int IdFluxo = 0;

	//Cria a lista a ser retornada
	List<CA_Midia_TipoPrincipal>^ ListaRetorno = gcnew List<CA_Midia_TipoPrincipal>(1);

	//Abre um laço que vai obter os tipos de midia principal.
	while (true)
	{
		//Chama o método para obter o Tipo da midia no fluxo especificado.
		Hr = PonteiroTrabalho->GetCurrentMediaType(IdFluxo, &pTipoMidia);

		//Verifica se obteve o tipo com sucesso.
		if (Sucesso(Hr))
		{
			//Chama o método para obter o Tipo principal do fluxo(Audio ou Video).
			Hr = pTipoMidia->GetMajorType(&GUID_TipoPrincipalFluxo);

			//Verifica se não falhou
			if (Falha(Hr))
			{
				//A operação falhou
				Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

				//Sai do laço.
				break;
			}

			//Verifica qual o tipo da midia
			if (GUID_TipoPrincipalFluxo == MFMediaType_Audio)
			{
				//O tipo da midia no fluxo id obtido é : Audio.

				//Adiciona o tipo de mídia na lista.
				ListaRetorno->Add(CA_Midia_TipoPrincipal::TP_Audio);
			}
			else if (GUID_TipoPrincipalFluxo == MFMediaType_Video)
			{
				//O tipo da midia no fluxo id obtido é : Video.

				//Adiciona o tipo de mídia na lista.
				ListaRetorno->Add(CA_Midia_TipoPrincipal::TP_Video);
			}
			else
			{
				//A midia contém um tipo não suportado.
				Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

				//Limpa os dados utilizados para obter as informações.
				pTipoMidia->Release();

				//Sai do While
				break;
			}

			//Define sucesso até segunda ordem
			Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

			//Limpa os dados utilizados para obter as informações.
			pTipoMidia->Release();
		}

		//Verifica se já não obteve todos os fluxos.
		else if (Hr == MF_E_INVALIDSTREAMNUMBER)
		{
			//Não existe mais fluxos.

			//Sai do laço
			break;
		}

		//Falhou ao realizar o método.
		else
		{
			//Falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);;

			//Sai do laço
			break;
		}

		//Incrementa o id de fluxo.
		IdFluxo += 1;
	}

	//Verifica o resultado
	if (Resultado.StatusCode == ResultCode::SS_OK)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define o código de erro
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		goto Done;
	}

	//Define a lista de retorno.
	Param_Out_TiposMidias = ListaRetorno;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}