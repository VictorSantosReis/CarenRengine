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
#include "CarenMFMediaTypeHandler.h"


//Destruidor.
CarenMFMediaTypeHandler::~CarenMFMediaTypeHandler()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
CarenMFMediaTypeHandler::CarenMFMediaTypeHandler(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFMediaTypeHandler* vi_pOutTypeHandler = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreateSimpleTypeHandler(&vi_pOutTypeHandler);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutTypeHandler;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
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
CarenResult CarenMFMediaTypeHandler::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFMediaTypeHandler::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaTypeHandler*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaTypeHandler::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaTypeHandler*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaTypeHandler::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaTypeHandler::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaTypeHandler::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaTypeHandler::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaTypeHandler::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaTypeHandler::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaTypeHandler::LiberarReferencia()
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
void CarenMFMediaTypeHandler::LimparDados()
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
void CarenMFMediaTypeHandler::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFMediaTypeHandler();
}




//
// Métodos da interface proprietaria
//


/// <summary>
/// (GetCurrentMediaType) - Recupera o tipo de mídia atual do objeto.
/// </summary>
/// <param name="Param_Out_MidiaType">Retorna o Tipo de midia atual.</param>
CarenResult CarenMFMediaTypeHandler::GetCurrentMediaType([Out] ICarenMFMediaType^% Param_Out_MidiaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados COM
	ResultadoCOM  Hr = E_FAIL;
	
	//Variaveis utilizadas pelo método
	ICarenMFMediaType^ InterfaceTipoMidia = nullptr;
	IMFMediaType *pTipoMidiaAtual = NULL;

	//Chama o método para obter o tipo de midia atual.
	Hr = PonteiroTrabalho->GetCurrentMediaType(&pTipoMidiaAtual);

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

	//Cria a interface que vai conter o tipo de mídia.
	InterfaceTipoMidia = gcnew CarenMFMediaType(false);

	//Chama o método para definir o ponteiro na interface.
	InterfaceTipoMidia->AdicionarPonteiro(pTipoMidiaAtual);

	//Define a interface no retorno do parametro.
	Param_Out_MidiaType = InterfaceTipoMidia;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetMajorType) - Obtém o tipo de mídia principal do objeto.
/// </summary>
/// <param name="Param_Out_GuidMidiaPrincipal">Retorna o GUID do tipo da mídia principal.</param>
/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração que define o tipo principal da mídia.</param>
CarenResult CarenMFMediaTypeHandler::GetMajorType([Out] String^% Param_Out_GuidMidiaPrincipal, [Out] Enumeracoes::CA_MAJOR_MEDIA_TYPES% Param_Out_TipoPrincipal)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas no método
	ResultadoCOM  Hr = E_FAIL;
	GUID GuidTipoPrincipal = GUID_NULL;
	Utilidades Util;

	//Obtém o guid o formato principal da mídia.
	Hr = PonteiroTrabalho->GetMajorType(&GuidTipoPrincipal);

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
		Param_Out_TipoPrincipal = CA_MAJOR_MEDIA_TYPES::TP_Audio;
	
		//Define o Guid
		Param_Out_GuidMidiaPrincipal = Util.ConverterGuidToString(MFMediaType_Audio);
	}
	else if (GuidTipoPrincipal == MFMediaType_Video)
	{
		//O tipo principal da mídia é Vídeo.
		Param_Out_TipoPrincipal = CA_MAJOR_MEDIA_TYPES::TP_Video;
	
		//Define o Guid
		Param_Out_GuidMidiaPrincipal = Util.ConverterGuidToString(MFMediaType_Video);
	}
	else
	{
		//Tipo desconhecido.
		Param_Out_TipoPrincipal = CA_MAJOR_MEDIA_TYPES::TP_Desconhecido;
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetMediaTypeByIndex) - Recupera um tipo de mídia da lista do objeto de tipos de mídia com suporte.
/// </summary>
/// <param name="Param_Id">Índice baseado em zero do tipo de mídia para recuperar. Para obter o número de tipos de mídia na lista, chame o método (GetMediaTypeCount).</param>
/// <param name="Param_Out_MidiaType">Retorna o tipo da mídia no Id especificado.</param>
CarenResult CarenMFMediaTypeHandler::GetMediaTypeByIndex(UInt32 Param_Id, [Out] ICarenMFMediaType^% Param_Out_MidiaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	ICarenMFMediaType^ InterfaceTipoMidia = nullptr;
	IMFMediaType *pTipoMidiaAtual = NULL;

	//Chama o método para obter o tipo de midia no index especificado.
	Hr = PonteiroTrabalho->GetMediaTypeByIndex(Param_Id ,&pTipoMidiaAtual);

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

	//Cria a interface que vai conter o tipo de mídia.
	InterfaceTipoMidia = gcnew CarenMFMediaType(false);

	//Chama o método para definir o ponteiro na interface.
	InterfaceTipoMidia->AdicionarPonteiro(pTipoMidiaAtual);

	//Define a interface no retorno do parametro.
	Param_Out_MidiaType = InterfaceTipoMidia;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetMediaTypeCount) - Recupera o número de tipos de mídia na lista do objeto de tipos de mídia com suporte.
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna a quantidade de tipos de mídia na interface.</param>
CarenResult CarenMFMediaTypeHandler::GetMediaTypeCount([Out] UInt32% Param_Out_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	DWORD CountTiposMidia = 0;

	//Chama o método para obter a quantidade de tipos de midia.
	Hr = PonteiroTrabalho->GetMediaTypeCount(&CountTiposMidia);

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

	//Define a quantidade de tipos de midia no parametro.
	Param_Out_Quantidade = safe_cast<UInt32>(CountTiposMidia);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (IsMediaTypeSupported) - Consulta se o objeto oferece suporte a um tipo de mídia especificado.
/// Para uma fonte de mídia, isso significa que a fonte pode gerar dados que estejam de acordo com esse 
/// tipo de mídia. Para um coletor de mídia, isso significa que o coletor pode receber dados que está de 
/// acordo com esse tipo de mídia.
/// NOTA: O método falha com (ER_MF_TIPO_MIDIA_INVALIDA) se o tipo da mídia não é suportado.
/// </summary>
/// <param name="Param_MidiaType">O Tipo de mídia a ser verificado se é suportado pela (Fonte de mídia ou Pelo Coletor de Mídia) que gerou essa interface.</param>
/// <param name="Param_Out_MidiaAproximada">Recebe o tipo de mídia que pode se aproximar ou não da mídia verificada. 
/// Se o método retorna sucesso, valor dessa parametro é (NULO).</param>
CarenResult  CarenMFMediaTypeHandler::IsMediaTypeSupported(ICarenMFMediaType^ Param_MidiaType, [Out] ICarenMFMediaType^% Param_Out_MidiaAproximada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaType *pTipoMidiaAVerificar = NULL;
	IMFMediaType *pTipoMidiaAproximada = NULL;
	ICarenMFMediaType^ InterfaceTipoMidiaAproximada = nullptr;

	//Chama o método para obter um ponteiro para a interface não gerenciada
	//na interface do parametro.
	Resultado = Param_MidiaType->RecuperarPonteiro((LPVOID*)&pTipoMidiaAVerificar);

	//Verifica se não houve erro
	if(Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Nenhuma interface disponivel.
		goto Done;
	}

	//Chama o método para verificar se o tipo é suportado.
	Hr = PonteiroTrabalho->IsMediaTypeSupported(pTipoMidiaAVerificar, &pTipoMidiaAproximada);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);
	
    //Verifica se foi informado um tipo de midia aproximado do solicitado.
    if (Hr == MF_E_INVALIDMEDIATYPE)
	{
		//Indica que o objeto não suporta o tipo de mídia indicada.
		Resultado.AdicionarCodigo(ResultCode::ER_MF_E_INVALIDMEDIATYPE, false);

		//Verifica se o método retornou uma suposta tipo de mídia aproximada do valor verificado.
		if (pTipoMidiaAproximada == NULL)
		{
			//Nenhum tipo de midia aproximada foi retornado pelo método.
		}
		else
		{
			//Um tipo de midia foi retornada pelo método
			//Cria a interface que vai conter e retornar no parametro.
			InterfaceTipoMidiaAproximada = gcnew CarenMFMediaType(false);

			//Chama o método que vai definir o ponteiro de trabalho na interface.
			InterfaceTipoMidiaAproximada->AdicionarPonteiro(pTipoMidiaAproximada);

			//Define no parametro de retorno.
			Param_Out_MidiaAproximada = InterfaceTipoMidiaAproximada;
		}

		//Sai do método.
		goto Done;
	}

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//O tipo de mídia é suportado.

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetCurrentMediaType) - Define o tipo de mídia do objeto.
/// Para fontes de mídia, a configuração do tipo de mídia significa que a fonte gerará dados que estejam 
/// de acordo com esse tipo de mídia. Para coletores de mídia, definindo o tipo de mídia significa que o 
/// coletor pode receber dados que está de acordo com esse tipo de mídia.
/// </summary>
/// <param name="Param_MidiaType">O tipo de mídia a ser definido no objeto.</param>
CarenResult CarenMFMediaTypeHandler::SetCurrentMediaType(ICarenMFMediaType^ Param_MidiaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultados COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaType *pTipoMidiaAdd = NULL;

	//Chama o método para obter um ponteiro para a interface não gerenciada
	//na interface do parametro.
	Resultado = Param_MidiaType->RecuperarPonteiro((LPVOID*)&pTipoMidiaAdd);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Nenhuma interface disponivel.
		goto Done;
	}

	//Chama o método para definir o tipo de mídia atual.
	Hr = PonteiroTrabalho->SetCurrentMediaType(pTipoMidiaAdd);

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

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}