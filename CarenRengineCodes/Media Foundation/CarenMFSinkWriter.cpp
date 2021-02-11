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
#include "CarenMFSinkWriter.h"


//Destruidor.
CarenMFSinkWriter::~CarenMFSinkWriter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFSinkWriter::CarenMFSinkWriter()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenMFSinkWriter::CarenMFSinkWriter(ICarenMFMediaSink^ Param_MediaSink, ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaSink* vi_pMediaSink = Nulo;
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IMFSinkWriter* vi_pOutSinkWriter = Nulo;

	//Verfifica se a interface do Media Sink é valida.
	if (!ObjetoGerenciadoValido(Param_MediaSink))
		throw gcnew NullReferenceException("A interface no parâmetro (Param_MediaSink) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_MediaSink, &vi_pMediaSink);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do Media Sink.");

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
	Hr = MFCreateSinkWriterFromMediaSink(vi_pMediaSink, vi_pAttributes, &vi_pOutSinkWriter);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutSinkWriter;
}

CarenMFSinkWriter::CarenMFSinkWriter(String^ Param_OutputUrl, ICarenMFByteStream^ Param_Stream, ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	PWSTR vi_pOutputUrl = Nulo; //Pode ser Nulo se vi_pByteStream não for
	IMFByteStream* vi_pByteStream = Nulo; //Pode ser Nulo se vi_pOutputUrl não for.
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IMFSinkWriter* vi_pOutSinkWriter = Nulo;

	//Verifica se a url foi informada e converte a string.
	if (StringObjetoValido(Param_OutputUrl))
		vi_pOutputUrl = Util.ConverterStringToWCHAR(Param_OutputUrl);

	//Verifica se o fluxo de bytes foi informado e obtem o ponteiro.
	if (ObjetoGerenciadoValido(Param_Stream))
	{
		//Tenta recuperar o ponteiro para a interface.
		Resultado = RecuperarPonteiroCaren(Param_Stream, &vi_pByteStream);

		//Verifica se não houve algum erro
		if (!CarenSucesso(Resultado))
			throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");
	}

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
	Hr = MFCreateSinkWriterFromURL(const_cast<PWSTR>(vi_pOutputUrl), vi_pByteStream, vi_pAttributes, &vi_pOutSinkWriter);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutSinkWriter;

	//Libera a memória utilizada pela string se valida
	DeletarStringAllocatedSafe(&vi_pOutputUrl);
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
CarenResult CarenMFSinkWriter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFSinkWriter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSinkWriter*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFSinkWriter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSinkWriter*>(Param_PonteiroNativo);

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
CarenResult CarenMFSinkWriter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFSinkWriter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFSinkWriter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFSinkWriter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSinkWriter::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSinkWriter::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSinkWriter::LiberarReferencia()
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
void CarenMFSinkWriter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFSinkWriter();
}



//
// Métodos da interface Proprietaria
//



/// <summary>
/// (AddStream) - Adiciona um fluxo para o gravador de coletor.
/// </summary>
/// <param name="Param_TipoMidia">Esse tipo de mídia especifica o formato das amostras que serão gravados no arquivo ou Hardware. 
/// Ele não precisa corresponder ao formato de entrada. Para definir o formato de entrada, chame o método: SetInputMediaType</param>
/// <param name="Param_Out_IdFluxoAdicionado">Recebe o índice baseado em zero do novo fluxo.</param>
CarenResult CarenMFSinkWriter::AddStream(ICarenMFMediaType^ Param_TipoMidia, [Out] UInt32% Param_Out_IdFluxoAdicionado)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFMediaType *vi_pMediaTypeAdd = Nulo;
	DWORD vi_OutIdAdded = 0;

	//Chama o método para recuperar o ponteiro de trabalho na interface gerenciada.
	CarenGetPointerFromICarenSafe(Param_TipoMidia, vi_pMediaTypeAdd);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//O ponteiro de trabalho não é valido.
		goto Done;
	}

	//Chama o método para definir o tipo da midia
	Hr = PonteiroTrabalho->AddStream(vi_pMediaTypeAdd, &vi_OutIdAdded);

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

	//Define o Id do fluxo adicionado
	Param_Out_IdFluxoAdicionado = safe_cast<UInt32>(vi_OutIdAdded);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (BeginWriting) - Inicializa o gravador de coletor para gravação.
/// Chame esse método depois de configurar os fluxos de entrada e antes de enviar 
/// os dados para o gravador de coletor.
/// </summary>
CarenResult CarenMFSinkWriter::BeginWriting()
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para iniciar o escritor de dados.
	Hr = PonteiroTrabalho->BeginWriting();

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
/// (Finalize) - Conclui todas as operações de gravação no gravador de coletor.
/// </summary>
CarenResult CarenMFSinkWriter::_Finalize()
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para completa todas as operações no escritor.
	Hr = PonteiroTrabalho->Finalize();

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
/// (Flush) - Libera um ou mais fluxos.
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo a ser liberado. Se (Param_TodosFluxos) for True, desconsidere esse valor.</param>
/// <param name="Param_TodosFluxos">Define se deve liberar todos os fluxos deste escritor. Equivale ao valor: MF_SINK_WRITER_ALL_STREAMS</param>
CarenResult CarenMFSinkWriter::Flush(UInt32 Param_IdFluxo, Boolean Param_TodosFluxos)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Flush(Param_TodosFluxos ? 
		MF_SINK_WRITER_ALL_STREAMS :
		static_cast<DWORD>(Param_IdFluxo));

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
/// (GetServiceForStream) - Consulta o coletor de mídia subjacente ou codificador para uma interface.
/// </summary>
/// <param name="Param_IdFluxo">Um Indice baseado em zero de um fluxo para a consulta. Desconsidere esse valor se o parâmetro (Param_Escritor)
/// for True.</param>
/// <param name="Param_ConsultarColetor">Define que o objeto de consulta é o Coletor de Mídia associado. Esse valor representa o: MF_SINK_WRITER_MEDIASINK</param>
/// <param name="Param_GuidServiço">O Guid para o (Identificador de Serviço). Se o valor for (NULO), o método chama (QueryInterface) para obter
/// interface solicitada.</param>
/// <param name="Param_GuidInterfaceSolicitada">O Guid para a interface solicitada.</param>
/// <param name="Param_Out_Interface">Recebe a interface solicitada.</param>
CarenResult CarenMFSinkWriter::GetServiceForStream(
	UInt32 Param_IdFluxo,
	Boolean Param_ConsultarColetor,
	String^ Param_GuidServiço,
	String^ Param_GuidInterfaceSolicitada,
	ICaren^ Param_Out_Interface)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variariveis utilizadas no método
	Utilidades Util;
	GUID GuidService = GUID_NULL;
	GUID GuidInterface = GUID_NULL;
	LPVOID OutInterfaceNativa = NULL;

	//Chama o método para obter o guid da interface.
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterfaceSolicitada);

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

	//Define o ponteiro para o ponteiro de trabalho
	CarenSetPointerToICarenSafe(reinterpret_cast<IUnknown*>(OutInterfaceNativa), Param_Out_Interface, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetStatistics) - Obtém estatísticas sobre o desempenho do gravador de coletor.
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo de consulta. Se (Param_ConsularColetor) for True, desconsidere esse valor.</param>
/// <param name="Param_ConsultarColetor">Define se deve obter as estatísticas do (Coletor de Mídia) propriamente dito.</param>
/// <param name="Param_Out_StatusDesempenho">Retorna a estrutura que contém todas as informações de Desempenho </param>
CarenResult CarenMFSinkWriter::GetStatistics(UInt32 Param_IdFluxo, Boolean Param_ConsultarColetor, [Out] Estruturas::CA_MF_SINK_WRITER_STATISTICS^% Param_Out_StatusDesempenho)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	MF_SINK_WRITER_STATISTICS* EstuturaNativaEstatisticasColetor = CriarEstrutura<MF_SINK_WRITER_STATISTICS>();
	Utilidades Util;

	//Define o tamanho da estrutura
	EstuturaNativaEstatisticasColetor->cb = sizeof(MF_SINK_WRITER_STATISTICS);

	//Verifica se deve obter as estatiticas do coletor diretamente
	if (Param_ConsultarColetor)
	{
		//Chama o método para consultar as estatísticas do proprio coletor.
		Hr = PonteiroTrabalho->GetStatistics(MF_SINK_WRITER_ALL_STREAMS, EstuturaNativaEstatisticasColetor);
	}
	else
	{
		//Chama o método para consultar o fluxo no id especificado.
		Hr = PonteiroTrabalho->GetStatistics(Param_IdFluxo, EstuturaNativaEstatisticasColetor);
	}

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

	//Converte e define no parametro de saida.
	Param_Out_StatusDesempenho = Util.ConverterMF_SINK_WRITER_STATISTICSUnamagedToManaged(EstuturaNativaEstatisticasColetor);
Done:;
	//Deleta a estrutura não gerenciada
	DeletarEstruturaSafe(&EstuturaNativaEstatisticasColetor);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (NotifyEndOfSegment) - Notifica o coletor de mídia que um fluxo atingiu o final de um segmento.
/// </summary>
/// <param name="Param_IdFluxo">O indica para o fluxo que vai ser notificado que foi atingido o final de um segmento. Desconsidere esse valor se (Param_NotificarTodos)
/// for True.</param>
/// <param name="Param_NotificarTodos">Indica que vai notificar que todos os fluxos atingiram o final de um segmento.</param>
CarenResult CarenMFSinkWriter::NotifyEndOfSegment(UInt32 Param_IdFluxo, Boolean Param_NotificarTodos)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Verifica se deve notificar todos os fluxos
	if (Param_NotificarTodos)
	{
		//Chama o método para notificar todos os fluxos.
		Hr = PonteiroTrabalho->NotifyEndOfSegment(MF_SINK_WRITER_ALL_STREAMS);
	}
	else
	{
		//Chama o método para notificar o fluxo especificado.
		Hr = PonteiroTrabalho->NotifyEndOfSegment(Param_IdFluxo);
	}

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
/// Coloca um marcador no fluxo especificado.
/// Para usar esse método, você deve fornecer um retorno de chamada assíncrono(MF_SINK_WRITER_ASYNC_CALLBACK) quando você cria o Gravador de Coletor(ICarenMFSinkWriter).
/// Caso contrario, o método retorna o código: ER_MF_REQUISICAO_INVALIDA
/// </summary>
/// <param name="Param_IdFluxo">O Id para o fluxo que vai ter o marcador adicionado.</param>
/// <param name="Param_Valor">A interface que contém o valor desconhecido a ser definido.</param>
CarenResult CarenMFSinkWriter::PlaceMarker(UInt32 Param_IdFluxo, ICaren^ Param_Valor)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	LPVOID vi_pInterfaceValue = NULL;

	//Verifica se foi fornecida a interface opcional e recupera seu ponteiro.
	if (!ObjetoGerenciadoValido(Param_Valor))
		CarenGetPointerFromICarenSafe(Param_Valor, vi_pInterfaceValue);
	
	//Chama o método para definir o marcador
	Hr = PonteiroTrabalho->PlaceMarker(Param_IdFluxo, vi_pInterfaceValue);

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
/// (SendStreamTick) - Indica uma lacuna em um fluxo de entrada.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
/// <param name="Param_IdFluxo">A posição no fluxo onde ocorre a lacuna nos dados. O valor é fornecido em 100-nanosecond unidades, 
/// em relação ao início do fluxo..</param>
CarenResult CarenMFSinkWriter::SendStreamTick(UInt32 Param_IdFluxo, Int64 Param_TimeStamp)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.

	//Chama o método para enviar a Lacuna para o fluxo especificado.
	Hr = PonteiroTrabalho->SendStreamTick(static_cast<DWORD>(Param_IdFluxo), Param_TimeStamp);
	
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
/// (SetInputMediaType) - Define o Formatar de entrada para um fluxo no gravador de coletor.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
/// <param name="Param_TipoMidia">A interface que representa o tipo da mídia. O tipo de mídia especifica o 
/// formato de entrada.</param>
/// <param name="Param_ParametrosEncode">Use o repositório de atributos para configurar o codificador. 
/// Este parâmetro pode ser nulo.</param>
CarenResult CarenMFSinkWriter::SetInputMediaType(UInt32 Param_IdFluxo, ICarenMFMediaType^ Param_TipoMidia, ICarenMFAttributes^ Param_ParametrosEncode)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFMediaType *vi_pMediaTypeEntry = Nulo;
	IMFAttributes *vi_pAttributesEncode = Nulo;

	//Chama o método para obter o tipo de midia de entrada
	CarenGetPointerFromICarenSafe(Param_TipoMidia, vi_pMediaTypeEntry);

	//Verifica se está adicionando os atributos de configuração para o decodificador.
	if (ObjetoGerenciadoValido(Param_ParametrosEncode))
		CarenGetPointerFromICarenSafe(Param_ParametrosEncode, vi_pAttributesEncode);

	//Chama o método para definir o tipo da midia de entrada.
	Hr = PonteiroTrabalho->SetInputMediaType(static_cast<DWORD>(Param_IdFluxo), vi_pMediaTypeEntry, vi_pAttributesEncode);

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
/// (WriteSample) - Fornece uma amostra para o gravador de coletor.
/// Você deve chamar o método (BeginWriting) antes de chamar esse método. Caso contrário, o método retornará 
/// o código: ER_MF_REQUISICAO_INVALIDA.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo para este exemplo.</param>
/// <param name="Param_AmostraMidia">A interface que contém a amostra a ser escrita.</param>
CarenResult CarenMFSinkWriter::WriteSample(UInt32 Param_IdFluxo, ICarenMFSample^ Param_AmostraMidia)
{
	//Define falha na operação.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFSample *vi_pWriteSample = NULL;

	//Chama o método para obter a amostra a ser escrita.
	CarenGetPointerFromICarenSafe(Param_AmostraMidia, vi_pWriteSample);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface não é valida

		//Sai do método.
		goto Done;
	}

	//Chama o método para escrever a amostra no id especificado para o arquivo ou Hardware
	Hr = PonteiroTrabalho->WriteSample(static_cast<DWORD>(Param_IdFluxo), vi_pWriteSample);

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