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
#include "CarenMFTransform.h"

//Destruidor.
CarenMFTransform::~CarenMFTransform()
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
CarenResult CarenMFTransform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFTransform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFTransform*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFTransform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFTransform*>(Param_PonteiroNativo);

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
CarenResult CarenMFTransform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFTransform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFTransform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFTransform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFTransform::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFTransform::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFTransform::LiberarReferencia()
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
void CarenMFTransform::LimparDados()
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
void CarenMFTransform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFTransform();
}






//
// Métodos da interface proprietária(ICarenMFTransform)
//

/// <summary>
/// (AddInputStreams) - Adiciona um ou mais novos fluxos de entrada a esta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_Quantidade">Quantidade de fluxos a serem adicionados.</param> 
/// <param name="Param_ArrayIdentificadores">Matriz de identificadores de fluxo. Os novos identificadores de fluxo não devem corresponder a nenhum fluxo de entrada existente.</param> 
CarenResult CarenMFTransform::AdicionarFluxosEntrada(UInt32 Param_Quantidade, cli::array<UInt32>^ Param_ArrayIdentificadores)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DWORD* pArrayIdentificadores = CriarMatrizUnidimensional<DWORD>(Param_Quantidade);

	//Copia os dados para o array nativo.
	Util.CopiarItensTo_ArrayNativo(&pArrayIdentificadores, Param_ArrayIdentificadores, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddInputStreams(Param_Quantidade, pArrayIdentificadores);

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
	//Libera o array de identificadores
	DeletarMatrizUnidimensional(pArrayIdentificadores);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DeleteInputStream) - Remove um fluxo de entrada desta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_FluxoID"> O Id do fluxo a ser removido.</param>
CarenResult CarenMFTransform::DeletarFluxoEntrada(UInt32 Param_FluxoID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DeleteInputStream(Param_FluxoID);

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
/// (GetAttributes ) - Recebe a loja global de atributos para esta transformação da Media Foundation (MFT).
/// Use o ponteiro recuperado por este método para obter ou definir atributos que se aplicam a todo o MFT.
/// </summary>
/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface de atributos. O chamdor deve liberar a interface.</param>
CarenResult CarenMFTransform::ObterAtributos([Out] ICarenMFAttributes^% Param_Out_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* pAtributos = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributes(&pAtributos);

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

	//Cria a interface de retorno.
	Param_Out_Atributos = gcnew CarenMFAttributes();

	//Chama o método para definir o ponteiro.
	Param_Out_Atributos->AdicionarPonteiro(pAtributos);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
CarenResult CarenMFTransform::ObterTipoFluxoEntradaDisponivel(UInt32 Param_IDFluxoEntrada, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pMediaType = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputAvailableType(Param_IDFluxoEntrada, Param_TipoID, &pMediaType);

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

	//Cria a interface de retorno
	Param_Out_InterfaceTipoMidia = gcnew CarenMFMediaType();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceTipoMidia->AdicionarPonteiro(pMediaType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputCurrentType) - Obtém o tipo de mídia atual para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
CarenResult CarenMFTransform::ObterTipoFluxoEntradaAtual(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pMediaType = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputCurrentType(Param_IDFluxoEntrada, &pMediaType);

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

	//Cria a interface de retorno
	Param_Out_InterfaceTipoMidia = gcnew CarenMFMediaType();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceTipoMidia->AdicionarPonteiro(pMediaType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputStatus) - Consulta se um fluxo de entrada nesta transformação da Media Foundation (MFT) pode aceitar mais dados.
/// Se o método retornar a bandeira CA_MFT_INPUT_STATUS_ACCEPT_DATA, você pode fornecer uma amostra de entrada para o fluxo 
/// especificado ligando para ICarenMFTransform::ProcessarEntrada. Se o método for bem sucedido, mas não devolver nenhuma 
/// bandeira no parâmetro Param_Out_Flag, significa que o fluxo de entrada já tem o máximo de dados que pode aceitar.
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_INPUT_STATUS_FLAGS, ou zero. Se o valor for CA_MFT_INPUT_STATUS_ACCEPT_DATA, o fluxo especificado 
/// no Param_IDFluxoEntrada pode aceitar mais dados de entrada.</param>
CarenResult CarenMFTransform::ObterStatusEntrada(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STATUS_FLAGS% Param_Out_Flag)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD FlagsStatus = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputStatus(Param_IDFluxoEntrada, &FlagsStatus);

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

	//Define os flags no parametro de saida.
	Param_Out_Flag = static_cast<CA_MFT_INPUT_STATUS_FLAGS>(FlagsStatus);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputStreamAttributes) - Recebe a loja de atributos para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenMFTransform::ObterAtributosFluxoEntrada(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* pAtributosFluxoEntrada = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputStreamAttributes(Param_IDFluxoEntrada, &pAtributosFluxoEntrada);

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

	//Cria a interface de retorno.
	Param_Out_AtributosFluxo = gcnew CarenMFAttributes();

	//Chama o método para definir o ponteiro.
	Param_Out_AtributosFluxo->AdicionarPonteiro(pAtributosFluxoEntrada);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_INPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de entrada.</param>
CarenResult CarenMFTransform::ObterInfoFluxoEntrada(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STREAM_INFO^% Param_Out_InfoFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	_MFT_INPUT_STREAM_INFO InfoFluxo = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputStreamInfo(Param_IDFluxoEntrada, &InfoFluxo);

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

	//Converter a esturtura gerenciada para a nativa e define no parametro de saida.
	Param_Out_InfoFluxo = Util.ConverterMFT_INPUT_STREAM_INFOUnmanagedToManaged(&InfoFluxo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
CarenResult CarenMFTransform::ObterTipoFluxoSaidaDisponivel(UInt32 Param_IDFluxoSaida, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pTipoFluxo = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputAvailableType(Param_IDFluxoSaida, Param_TipoID, &pTipoFluxo);

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

	//Cria a interface de retorno
	Param_Out_InterfaceTipoMidia = gcnew CarenMFMediaType();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceTipoMidia->AdicionarPonteiro(pTipoFluxo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputCurrentType) - Obtém o tipo de mídia atual para um fluxo de saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
CarenResult CarenMFTransform::ObterTipoFluxoSaidaAtual(UInt32 Param_IDFluxoSaida, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pMediaType = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputCurrentType(Param_IDFluxoSaida, &pMediaType);

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

	//Cria a interface de retorno
	Param_Out_InterfaceTipoMidia = gcnew CarenMFMediaType();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceTipoMidia->AdicionarPonteiro(pMediaType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputStatus) - Questiona se a transformação da Media Foundation (MFT) está pronta para produzir dados de produção.
/// Se o método devolver a bandeira CA_MFT_OUTPUT_STATUS_SAMPLE_READY, significa que você pode gerar uma ou mais amostras de produção ligando 
/// para o ICarenMFTransform::ProcessarSaida.
/// </summary>
/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_OUTPUT_STATUS_FLAGS, ou zero. Se o valor for MFT_OUTPUT_STATUS_SAMPLE_READY, o MFT pode produzir 
/// uma amostra de saída.</param>
CarenResult CarenMFTransform::ObterStatusSaida([Out] CA_MFT_OUTPUT_STATUS_FLAGS% Param_Out_Flag)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD FlagsStatus = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputStatus(&FlagsStatus);

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

	//Define os flags no parametro de saida.
	Param_Out_Flag = static_cast<CA_MFT_OUTPUT_STATUS_FLAGS>(FlagsStatus);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputStreamAttributes) - Recebe a loja de atributos para um fluxo de saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenMFTransform::ObterAtributosFluxoSaida(UInt32 Param_IDFluxoSaida, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* pAtributosFluxoSaida = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputStreamAttributes(Param_IDFluxoSaida, &pAtributosFluxoSaida);

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

	//Cria a interface de retorno.
	Param_Out_AtributosFluxo = gcnew CarenMFAttributes();

	//Chama o método para definir o ponteiro.
	Param_Out_AtributosFluxo->AdicionarPonteiro(pAtributosFluxoSaida);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_OUTPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de saida.</param>
CarenResult CarenMFTransform::ObterInfoFluxoSaida(UInt32 Param_IDFluxoSaida, [Out] CA_MFT_OUTPUT_STREAM_INFO^% Param_Out_InfoFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	_MFT_OUTPUT_STREAM_INFO InfoFluxoSaida = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputStreamInfo(Param_IDFluxoSaida, &InfoFluxoSaida);

	//Verifica se a operação obteve sucesso.
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

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_InfoFluxo = Util.ConverterMFT_OUTPUT_STREAM_INFOUnmanagedToManaged(&InfoFluxoSaida);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetStreamCount) - Obtém o número atual de fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_Out_FluxoEntrada">Retorna a quantidade de fluxos de entrada.</param>
/// <param name="Param_Out_FluxoSaida">Retorna a quantidade de fluxos de saida.</param>
CarenResult CarenMFTransform::ObterQuantidadeFluxos([Out] UInt32% Param_Out_FluxoEntrada, [Out] UInt32% Param_Out_FluxoSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD OutFluxoEntrada = 0;
	DWORD OutFluxoSaida = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamCount(&OutFluxoEntrada, &OutFluxoSaida);

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

	//Define os valores nos parametros de saida.
	Param_Out_FluxoEntrada = OutFluxoEntrada;
	Param_Out_FluxoSaida = OutFluxoSaida;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetStreamIDs) - Obtém os identificadores de fluxo para os fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_SizeMatrizFluxosEntrada">O tamanho da matriz que vai conter os IDs dos fluxos de entrada.</param>
/// <param name="Param_MatrizFluxosEntrada">Uma matriz que vai receber todos os identificadores de fluxos de Entrada. O chamador é responsável por criar a matriz. 
/// Chame o método ICarenMFTransform::ObterQuantidadeFluxos para descobrir o tamanho que deve ser essa matriz.</param>
/// <param name="Param_SizeMatrizFluxosSaida">O tamanho da matriz que vai conter os IDs dos fluxos de Saida.</param>
/// <param name="Param_MatrizFluxosSaida">Uma matriz que vai receber todos os identificadores de fluxos de Saida. O chamador é responsável por criar a matriz. 
/// Chame o método ICarenMFTransform::ObterQuantidadeFluxos para descobrir o tamanho que deve ser essa matriz.</param>
CarenResult CarenMFTransform::ObterIDsFluxo(
				UInt32 Param_SizeMatrizFluxosEntrada, 
				cli::array<UInt32>^% Param_MatrizFluxosEntrada,  //REF
				UInt32 Param_SizeMatrizFluxosSaida, 
				cli::array<UInt32>^% Param_MatrizFluxosSaida) //REF
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DWORD* pArrayFluxosEntrada = CriarMatrizUnidimensional<DWORD>(Param_SizeMatrizFluxosEntrada);
	DWORD* pArrayFluxosSaida = CriarMatrizUnidimensional<DWORD>(Param_SizeMatrizFluxosSaida);

	//Copia os dados dos arrays gerenciados para os nativos.
	Util.CopiarItensTo_ArrayNativo(&pArrayFluxosEntrada, Param_MatrizFluxosEntrada, Param_SizeMatrizFluxosEntrada);
	Util.CopiarItensTo_ArrayNativo(&pArrayFluxosSaida, Param_MatrizFluxosSaida, Param_SizeMatrizFluxosSaida);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamIDs(Param_SizeMatrizFluxosEntrada, pArrayFluxosEntrada, Param_SizeMatrizFluxosSaida, pArrayFluxosSaida);

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

	//Copia os dados dos arrays nativos para os gerenciados retornados ao usuário.
	Util.CopiarItensTo_ArrayGerenciado(Param_MatrizFluxosEntrada, pArrayFluxosEntrada, Param_SizeMatrizFluxosEntrada);
	Util.CopiarItensTo_ArrayGerenciado(Param_MatrizFluxosSaida, pArrayFluxosSaida, Param_SizeMatrizFluxosSaida);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria dos arrays nativos.
	DeletarMatrizUnidimensional(pArrayFluxosEntrada);
	DeletarMatrizUnidimensional(pArrayFluxosSaida);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetStreamLimits) - Obtém o número mínimo e máximo de fluxos de entrada e saída para esta transformação da Media Foundation (MFT).
/// Se o MFT tiver um número fixo de fluxos, os valores mínimos e máximos são os mesmos.
/// </summary>
/// <param name="Param_Out_FluxoEntradaMinimo">Recebe o número mínimo de fluxos de entrada.</param>
/// <param name="Param_Out_FluxoEntradaMaximo">Recebe o número máximo de fluxos de entrada. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
/// <param name="Param_Out_FluxoSaidaMinimo">Recebe o número mínimo de fluxos de saída.</param>
/// <param name="Param_Out_FluxoSaidaMaximo">Recebe o número máximo de fluxos de saída. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
CarenResult CarenMFTransform::ObterLimitesFluxos(
				[Out] UInt32% Param_Out_FluxoEntradaMinimo, 
				[Out] UInt32% Param_Out_FluxoEntradaMaximo,
				[Out] UInt32% Param_Out_FluxoSaidaMinimo,
				[Out] UInt32% Param_Out_FluxoSaidaMaximo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD OutEntradaMinimum = 0;
	DWORD OutEntradaMaximum = 0;
	DWORD OutSaidaMinimum = 0;
	DWORD OutSaidaMaximum = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamLimits(&OutEntradaMinimum, &OutEntradaMaximum, &OutSaidaMinimum, &OutSaidaMaximum);

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

	//Define os valores nos parametros de saida.
	Param_Out_FluxoEntradaMinimo = OutEntradaMinimum;
	Param_Out_FluxoEntradaMaximo = OutEntradaMaximum;
	Param_Out_FluxoSaidaMinimo = OutSaidaMinimum;
	Param_Out_FluxoSaidaMaximo = OutSaidaMaximum;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ProcessEvent) - Envia um evento para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Evento">Um ponteiro para a interface de eventos(ICarenMFMediaEvent).</param>
CarenResult CarenMFTransform::ProcessarEvento(UInt32 Param_IDFluxoEntrada, ICarenMFMediaEvent^ Param_Evento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaEvent* pEvento = NULL;

	//Recupera o ponteiro para a interface nativa.
	Resultado = Param_Evento->RecuperarPonteiro((LPVOID*)&pEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ProcessEvent(Param_IDFluxoEntrada, pEvento);

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
/// (ProcessInput) - Fornece dados para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// Na maioria dos casos, se o método for bem sucedido, o MFT armazena a amostra e mantém uma contagem de referência no ponteiro ICarenMFSample. 
/// Não reutilize a amostra até que o MFT libere a amostra. Em vez de armazenar a amostra, no entanto, um MFT pode copiar os dados da amostra em um novo buffer. 
/// Nesse caso, o MFT deve definir a bandeira MFT_INPUT_STREAM_DOES_NOT_ADDREF no método ICarenMFTransform::ObterInfoFluxoEntrada.
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_Amostra">Um ponteiro para a interface de amostra de midia. A amostra deve conter pelo menos um Buffer de mídia que contém dados de entrada válidos.</param>
/// <param name="Param_Flags">Reservado. Deixe como zero.</param>
CarenResult CarenMFTransform::ProcessarEntrada(UInt32 Param_IDFluxoEntrada, ICarenMFSample^ Param_Amostra, UInt32 Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFSample* pAmostra = NULL;

	//Recupera o ponteiro para a interface nativa.
	Resultado = Param_Amostra->RecuperarPonteiro((LPVOID*)&pAmostra);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ProcessInput(Param_IDFluxoEntrada, pAmostra, Param_Flags);

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
/// (ProcessMessage) - Envia uma mensagem para a Transformação da Fundação de Mídia (MFT).
/// </summary>
/// <param name="Param_Mensagem">A mensagem a enviar, especificada como membro da enumeração CA_MFT_MESSAGE_TYPE.</param>
/// <param name="Param_ulPram">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
CarenResult CarenMFTransform::ProcessarMensagem(CA_MFT_MESSAGE_TYPE Param_Mensagem, UInt32 Param_ulPram)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MFT_MESSAGE_TYPE MftMensagem = static_cast<MFT_MESSAGE_TYPE>(Param_Mensagem);
	ULONG_PTR UlParam = Param_ulPram;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ProcessMessage(MftMensagem, UlParam);

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
/// (ProcessOutput) - Gera saída a partir dos dados de entrada atuais.
/// </summary>
/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_FLAGS.</param>
/// <param name="Param_QuantidadeElementos">Número de elementos na matriz (Param_MatrizBuffersSaida). O valor deve ser de pelo menos 1.</param>
/// <param name="Param_MatrizBuffersSaida">Uma matriz de estruturas CA_MFT_OUTPUT_DATA_BUFFER. O MFT usa este array para devolver dados de saída ao chamador.</param>
/// <param name="Param_Out_Status">Recebe zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_STATUS.</param>
CarenResult CarenMFTransform::ProcessarSaida(
				CA_MFT_PROCESS_OUTPUT_FLAGS Param_Flags, 
				UInt32 Param_QuantidadeElementos, 
				cli::array<CA_MFT_OUTPUT_DATA_BUFFER^>^% Param_MatrizBuffersSaida, //REF
				[Out] CA_MFT_PROCESS_OUTPUT_STATUS% Param_Out_Status)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DWORD Flags = static_cast<DWORD>(Param_Flags);
	_MFT_OUTPUT_DATA_BUFFER *pArrayOutputData = CriarMatrizEstruturas<_MFT_OUTPUT_DATA_BUFFER>(Param_QuantidadeElementos);
	DWORD OutStatus = 0;

	//Define os dados definido pelo usuário em cada matriz.
	//Isto é necessário devido a este método funciona de duas formas segundo sua documentação.
	for (unsigned int i = 0; i < Param_QuantidadeElementos; i++)
	{
		//Converte e define a estrutura fornecida pelo cliente.
		pArrayOutputData[i] = *Util.ConverterMFT_OUTPUT_DATA_BUFFERManagedToUnamaged(Param_MatrizBuffersSaida[i]);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ProcessOutput(Flags, Param_QuantidadeElementos, pArrayOutputData, &OutStatus);

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

	//Converte os dados nativos para o array gerenciado equivalente.
	for (DWORD i = 0; i < Param_QuantidadeElementos; i++)
	{
		//Converte e define no indice da matriz.
		Param_MatrizBuffersSaida[i] = Util.ConverterMFT_OUTPUT_DATA_BUFFERUnmanagedToManaged(&pArrayOutputData[i]);
	}

	//Define o flag de status
	Param_Out_Status = static_cast<CA_MFT_PROCESS_OUTPUT_STATUS>(OutStatus);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetInputType) - Define, testa ou limpa o tipo de mídia para um fluxo de entrada nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de Entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
CarenResult CarenMFTransform::DefinirTipoFluxoEntrada(
				UInt32 Param_IDFluxoEntrada, 
				ICarenMFMediaType^ Param_TipoMidiaFluxo, 
				CA_MFT_SET_TYPE_FLAGS Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pTipoMidia = NULL;
	DWORD Flags = static_cast<_MFT_SET_TYPE_FLAGS>(Param_Flags);

	//Obtém o ponteiro para o tipo midia se valido
	if (ObjetoGerenciadoValido(Param_TipoMidiaFluxo))
	{
		//Chama o método para recuperar o ponteiro.
		Resultado = Param_TipoMidiaFluxo->RecuperarPonteiro((LPVOID*)&pTipoMidia);
		
		//Verifica se não houve erro.
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Sai do método
			goto Done;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetInputType(Param_IDFluxoEntrada, pTipoMidia, Flags);

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
/// (SetOutputBounds) - Define a gama de carimbos de tempo que o cliente precisa para a saída.
/// </summary>
/// <param name="Param_HorarioAntigo">Especifica o carimbo de horário mais antigo. A Transformação da Media Foundation (MFT) aceitará a entrada até que possa produzir uma 
/// amostra de saída que começa neste momento; ou até que possa produzir uma amostra que termina neste momento ou mais tarde. Se não houver limite inferior, use o 
/// valor MFT_OUTPUT_BOUND_LOWER_UNBOUNDED(0).</param>
/// <param name="Param_HorarioMaior">Especifica o último carimbo de tempo. O MFT não produzirá uma amostra de saída com carimbos de tempo mais tarde do que desta vez. Se 
/// não houver limite superior, use o valor MFT_OUTPUT_BOUND_UPPER_UNBOUNDED(-1).</param>
CarenResult CarenMFTransform::DefinirLimiteSaida(Int64 Param_HorarioAntigo, Int64 Param_HorarioMaior)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputBounds(Param_HorarioAntigo, Param_HorarioMaior);

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
/// (SetOutputType) - Define, testa ou limpa o tipo de mídia para um fluxo de saída nesta transformação da Media Foundation (MFT).
/// </summary>
/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
CarenResult CarenMFTransform::DefinirTipoFluxoSaida(
				UInt32 Param_IDFluxoSaida,
				ICarenMFMediaType^ Param_TipoMidiaFluxo,
				CA_MFT_SET_TYPE_FLAGS Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* pTipoMidia = NULL;
	DWORD Flags = static_cast<_MFT_SET_TYPE_FLAGS>(Param_Flags);

	//Obtém o ponteiro para o tipo midia se valido
	if (ObjetoGerenciadoValido(Param_TipoMidiaFluxo))
	{
		//Chama o método para recuperar o ponteiro.
		Resultado = Param_TipoMidiaFluxo->RecuperarPonteiro((LPVOID*)&pTipoMidia);

		//Verifica se não houve erro.
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Sai do método
			goto Done;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputType(Param_IDFluxoSaida, pTipoMidia, Flags);

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