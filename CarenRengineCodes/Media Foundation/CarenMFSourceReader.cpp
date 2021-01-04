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
#include "CarenMFSourceReader.h"


//Destruidor.
CarenMFSourceReader::~CarenMFSourceReader()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFSourceReader::CarenMFSourceReader()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenMFSourceReader::CarenMFSourceReader(String^ Param_Url, ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	PWSTR vi_pUrl = Nulo; //Pode ser Nulo se vi_pByteStream não for
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IMFSourceReader* vi_pOutSourceReader = Nulo;

	//Verifica se a url foi informada e converte a string.
	if (!StringObjetoValido(Param_Url))
		throw gcnew NullReferenceException("A url para o arquivo no parâmetro (Param_Url) não pode ser NULA e nem vazia.");

	//Converte a string com a url para o arquivo.
	vi_pUrl = Util.ConverterStringToWCHAR(Param_Url);

	//Recupera o ponteiro para a interface de atributos se informada
	if (ObjetoGerenciadoValido(Param_Atributos))
	{
		//Tenta recuperar o ponteiro para a interface.
		Resultado = RecuperarPonteiroCaren(Param_Atributos, &vi_pAttributes);

		//Verifica se não houve algum erro
		if (!CarenSucesso(Resultado))
			throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface de atributos informada.");
	}

	//Chama o método para criar a interface.
	Hr = MFCreateSourceReaderFromURL(const_cast<PWSTR>(vi_pUrl), vi_pAttributes, &vi_pOutSourceReader);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutSourceReader;

	//Libera a memória utilizada pela string se valida
	DeletarStringAllocatedSafe(&vi_pUrl);
}

CarenMFSourceReader::CarenMFSourceReader(ICarenMFMediaSource^ Param_MediaSource, ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaSource* vi_pMediaSource = Nulo;
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IMFSourceReader* vi_pOutSourceReader = Nulo;

	//Verfifica se a interface do Media Source é valida.
	if (!ObjetoGerenciadoValido(Param_MediaSource))
		throw gcnew NullReferenceException("A interface no parâmetro (Param_MediaSource) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_MediaSource, &vi_pMediaSource);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface da fonte de mídia(Media Source).");

	//Recupera o ponteiro para a interface de atributos se informada
	if (ObjetoGerenciadoValido(Param_Atributos))
	{
		//Tenta recuperar o ponteiro para a interface.
		Resultado = RecuperarPonteiroCaren(Param_Atributos, &vi_pAttributes);

		//Verifica se não houve algum erro
		if (!CarenSucesso(Resultado))
			throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface de atributos informada.");
	}

	//Chama o método para criar a interface.
	Hr = MFCreateSourceReaderFromMediaSource(vi_pMediaSource, vi_pAttributes, &vi_pOutSourceReader);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutSourceReader;
}

CarenMFSourceReader::CarenMFSourceReader(ICarenMFByteStream^ Param_ByteStream, ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IMFSourceReader* vi_pOutSourceReader = Nulo;

	//Verfifica se a interface para o fluxo de bytes é válida.
	if (!ObjetoGerenciadoValido(vi_pByteStream))
		throw gcnew NullReferenceException("A interface no parâmetro (Param_ByteStream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ByteStream, &vi_pByteStream);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");

	//Recupera o ponteiro para a interface de atributos se informada
	if (ObjetoGerenciadoValido(Param_Atributos))
	{
		//Tenta recuperar o ponteiro para a interface.
		Resultado = RecuperarPonteiroCaren(Param_Atributos, &vi_pAttributes);

		//Verifica se não houve algum erro
		if (!CarenSucesso(Resultado))
			throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface de atributos informada.");
	}

	//Chama o método para criar a interface.
	Hr = MFCreateSourceReaderFromByteStream(vi_pByteStream, vi_pAttributes, &vi_pOutSourceReader);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutSourceReader;
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
		if (!String::IsNullOrEmpty(Param_Guid))
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
CarenResult CarenMFSourceReader::GetCurrentMediaType(UInt32 Param_IdFluxo, [Out] ICarenMFMediaType^% Param_Out_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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
	MidiaTypeInterface = gcnew CarenMFMediaType(false);

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
CarenResult CarenMFSourceReader::GetNativeMediaType(UInt32 Param_IdFluxo, UInt32 Param_IdMediaTypeIndice, [Out] ICarenMFMediaType^% Param_Out_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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
	MidiaTypeInterface = gcnew CarenMFMediaType(false);

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
CarenResult CarenMFSourceReader::GetPresentationAttribute(UInt32 Param_IdFluxo, String^ Param_GuidAtributo, [Out] Estruturas::CA_PropVariant^% Param_Out_ValorAtributo)
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
	Param_Out_ValorAtributo = Util.ConvertPropVariantUnmanagedToManaged(PropVar);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa a PropVariant.
	PropVariantClear(&PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Consulta a fonte subjacente de mídia ou decodificador para uma interface.
/// </summary>
/// <param name="Param_IdFluxo">O fluxo ou objeto para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID). Se o valor for ID_FONTE_MIDIA, 
/// o método consultará a fonte de mídia. Caso contrário, ele consulta o decodificador que está associado com o fluxo especificado.</param>
/// <param name="Param_GuidServiço">Um identificador de serviço GUID, consulte a estrutura(MFInterfacesServiço) para  obter um GUID. Se o valor for (NULO), 
/// o método chama (ConsultarInterface) para obter a interface solicitada. Caso contrário, o método chama o ICarenMFGetService.ObterServiço.</param>
/// <param name="Param_GuidInterface">O identificador de interface (IID) da interface que está sendo solicitada..</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface que foi solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceReader::GetServiceForStream(UInt32 Param_IdFluxo, String^ Param_GuidServiço, String^ Param_GuidInterface, ICaren^ Param_Out_InterfaceDesconhecida)
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
CarenResult CarenMFSourceReader::GetStreamSelection(UInt32 Param_IdFluxo, [Out] Boolean% Param_Out_ResultadoFluxoSelecionado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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
/// ‎Lê a próxima amostra disponivel da fonte de mídia.‎ 
/// ‎Este método pode completar de forma sincrona ou assincrona. Se você fornecer um ponteiro de retorno de chamada(ICarenMFSourceReaderCallback) ao criar o leitor de origem, o método será assincrono. 
/// Caso contrário, o método é sincrono.
/// Para realizar uma chamada Assincrona, Ignore todos os parametros de saida(que contém o Out no nome). Caso contrario, o método retorna ER_E_INVALIDARG
/// </summary>
/// <param name="Param_StreamIndex">O index para o fluxo a ser extraido a amostra. Esse valor pode ser um UInt32 para um ID de fluxo valido ou um dos valores da enumeração (CA_SOURCE_READER_ID).</param>
/// <param name="Param_ControlFlags">Um ‎‎Bitwise‎‎ OR de zero ou mais bandeiras da enumeração ‎‎(CA_MF_SOURCE_READER_CONTROL_FLAG).‎</param>
/// <param name="Param_Out_ActualStreamIndex">Retorna o index baseado em zero para o fluxo atual.</param>
/// <param name="Param_Out_StreamFlags">Retorna um ‎‎Bitwise‎‎ OR de zero ou mais bandeiras da enumeração ‎‎(‎‎MF_SOURCE_READER_FLAG) que indicam o status da chamada.</param>
/// <param name="Param_Out_Timestamp">‎Retorna o carimbo de hora(Timestamp) da amostra ou a hora do evento de fluxo indicado em ‎‎(Param_Out_StreamFlags)‎‎. O tempo é dado em unidades de 100 nanossegundos.‎</param>
/// <param name="Param_Out_Sample">Retorna uma interface (ICarenMFSample) ou (NULO). Se este parametro nao for NULO, o usuário é responsável por liberar a interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
/// <returns></returns>
CarenResult CarenMFSourceReader::ReadSample
(
	UInt32 Param_StreamIndex,
	CA_MF_SOURCE_READER_CONTROL_FLAG Param_ControlFlags,
	CarenParameterResolver<UInt32> Param_Out_ActualStreamIndex,
	CarenParameterResolver<CA_MF_SOURCE_READER_FLAG> Param_Out_StreamFlags,
	CarenParameterResolver<Int64> Param_Out_Timestamp,
	CarenParameterResolver<ICarenMFSample^> Param_Out_Sample
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutActualStreamIndex = 0;
	DWORD vi_OutStreamFlags = 0;
	INT64 vi_OutTimestamp = 0;
	IMFSample* vi_pOutSample = Nulo;
	BOOL vi_IsAsync = Param_Out_Sample.IgnoreParameter ? TRUE : FALSE; //Define se o método será executado de forma assincrona ou não.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReadSample(
		static_cast<DWORD>(Param_StreamIndex),
		static_cast<DWORD>(Param_ControlFlags),
		Param_Out_ActualStreamIndex.IgnoreParameter? Nulo: &vi_OutActualStreamIndex,
		Param_Out_StreamFlags.IgnoreParameter ? Nulo : &vi_OutStreamFlags,
		Param_Out_Timestamp.IgnoreParameter ? Nulo : &vi_OutTimestamp,
		Param_Out_Sample.IgnoreParameter ? Nulo : &vi_pOutSample
	);

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

	//Define os parametros de saida se o método tiver sido chamado de forma Sincrona.
	if (vi_IsAsync)
	{
		//Define os dados dos parametros de saida.
		Param_Out_ActualStreamIndex.ObjetoParametro = static_cast<UInt32>(vi_OutActualStreamIndex);
		Param_Out_StreamFlags.ObjetoParametro = static_cast<CA_MF_SOURCE_READER_FLAG>(vi_OutStreamFlags);
		Param_Out_Timestamp.ObjetoParametro = vi_OutTimestamp;

		//Verifica se a amostra lida é valida.
		//MESMO O MÉTODO TENDO RETORNADO `SUCESSO` A AMOSTRA AINDA PODE SER NULA DE ACORDO COM A DOCUMENTAÇÃO DO MSDN.
		if (ObjetoValido(vi_pOutSample))
		{
			//Define a amostra no parametro de saida.
			CarenSetPointerToICarenSafe(vi_pOutSample, Param_Out_Sample.ObjetoParametro, true);
		}
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
CarenResult CarenMFSourceReader::SetCurrentMediaType(UInt32 Param_IdFluxo, UInt32 Param_ValorReservado, ICarenMFMediaType^ Param_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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
CarenResult CarenMFSourceReader::SetCurrentPosition(Int64 Param_PosiçãoNanoSegundos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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
CarenResult CarenMFSourceReader::SetStreamSelection(UInt32 Param_IdFluxo, Boolean Param_EstadoSeleção)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
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

	//Resultado COM.
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

	//Resultado COM.
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
CarenResult CarenMFSourceReader::ExRecuperarTiposMidia([Out] List<CA_MAJOR_MEDIA_TYPES>^% Param_Out_TiposMidias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFMediaType* pTipoMidia = NULL;
	GUID GUID_TipoPrincipalFluxo = GUID_NULL;
	int IdFluxo = 0;

	//Cria a lista a ser retornada
	List<CA_MAJOR_MEDIA_TYPES>^ ListaRetorno = gcnew List<CA_MAJOR_MEDIA_TYPES>(1);

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
				ListaRetorno->Add(CA_MAJOR_MEDIA_TYPES::TP_Audio);
			}
			else if (GUID_TipoPrincipalFluxo == MFMediaType_Video)
			{
				//O tipo da midia no fluxo id obtido é : Video.

				//Adiciona o tipo de mídia na lista.
				ListaRetorno->Add(CA_MAJOR_MEDIA_TYPES::TP_Video);
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