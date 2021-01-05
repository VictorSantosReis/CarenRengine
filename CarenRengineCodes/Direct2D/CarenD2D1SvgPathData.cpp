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
#include "CarenD2D1SvgPathData.h"

//Destruidor.
CarenD2D1SvgPathData::~CarenD2D1SvgPathData()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgPathData::CarenD2D1SvgPathData()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD2D1SvgPathData::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgPathData::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgPathData*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1SvgPathData::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgPathData*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1SvgPathData::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenD2D1SvgPathData::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenD2D1SvgPathData::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1SvgPathData::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SvgPathData::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgPathData::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgPathData::LiberarReferencia()
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
void CarenD2D1SvgPathData::LimparDados()
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
void CarenD2D1SvgPathData::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1SvgPathData();
}



// Métodos da interface proprietária(ICarenD2D1SvgPathData)


/// <summary>
/// Cria um objeto de Path Geometry representando os Path Data. 
/// </summary>
/// <param name="Param_FillMode">Modo de preenchimento para o Path Geometry.</param>
/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry1) contendo um ponteiro para para o objeto criado. </param>
CarenResult CarenD2D1SvgPathData::CreatePathGeometry(
CA_D2D1_FILL_MODE Param_FillMode,
[Out] ICarenD2D1PathGeometry1^% Param_Out_PathGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_FILL_MODE FillMode = static_cast<D2D1_FILL_MODE>(Param_FillMode);
	ID2D1PathGeometry1* pOutPathGeometry1 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePathGeometry(FillMode, &pOutPathGeometry1);

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

	//Cria a interface que será retornada.
	Param_Out_PathGeometry = gcnew CarenD2D1PathGeometry1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutPathGeometry1, Param_Out_PathGeometry);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe comandos da matriz de comandos. 
/// </summary>
/// <param name="Param_Out_Comandos">Buffer para conter os comandos.</param>
/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
/// <param name="Param_StartIndex">O índice dos primeiros comandos para recuperar.</param>
CarenResult CarenD2D1SvgPathData::GetCommands(
[Out] cli::array<CA_D2D1_SVG_PATH_COMMAND>^% Param_Out_Comandos,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_PATH_COMMAND* pOutMatrizSvgCommands = CriarMatrizUnidimensional<D2D1_SVG_PATH_COMMAND>(Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCommands(pOutMatrizSvgCommands, Param_Quantidade, Param_StartIndex);

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

	//Cria a matriz a ser retornada.
	Param_Out_Comandos = gcnew cli::array<CA_D2D1_SVG_PATH_COMMAND>(Param_Quantidade);

	//Copia os dados para a matriz gerenciada.
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_Comandos, pOutMatrizSvgCommands, Param_Quantidade);

Done:;
	//Libera a memória para matriz.
	DeletarMatrizUnidimensionalSafe(&pOutMatrizSvgCommands);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tamanho da matriz de comandos. 
/// </summary>
/// <param name="Param_Out_QuantidadeComandos">Retorna o tamanho da matriz de comandos.</param>
void CarenD2D1SvgPathData::GetCommandsCount([Out] UInt32% Param_Out_QuantidadeComandos)
{
	//Chama o método para realizar a operação.
	Param_Out_QuantidadeComandos = PonteiroTrabalho->GetCommandsCount();
}

/// <summary>
/// Obtém dados do conjunto de dados do segmento. 
/// </summary>
/// <param name="Param_Out_Dados">Buffer para conter o conjunto de dados do segmento.</param>
/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
/// <param name="Param_StartIndex">O índice dos dados do primeiro segmento para recuperar.</param>
CarenResult CarenD2D1SvgPathData::GetSegmentData(
[Out] cli::array<float>^% Param_Out_Dados,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	FLOAT* pOutMatrizDados = CriarMatrizUnidimensional<FLOAT>(static_cast<DWORD>(Param_Quantidade));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSegmentData(pOutMatrizDados, Param_Quantidade, Param_StartIndex);

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

	//Cria a matriz a ser retornada.
	Param_Out_Dados = gcnew cli::array<float>(Param_Quantidade);

	//Copia os dados para a matriz gerenciada.
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_Dados, pOutMatrizDados, Param_Quantidade);

Done:;
	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pOutMatrizDados);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tamanho do conjunto de dados do segmento. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o tamanho do conjunto de dados do segmento.</param>
void CarenD2D1SvgPathData::GetSegmentDataCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetSegmentDataCount();
}

/// <summary>
/// Remove comandos do final da matriz de comandos. 
/// </summary>
/// <param name="Param_QuantidadeComandos">Especifica quantos comandos deve remover.</param>
CarenResult CarenD2D1SvgPathData::RemoveCommandsAtEnd(UInt32 Param_QuantidadeComandos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveCommandsAtEnd(Param_QuantidadeComandos);

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
/// Remove dados do conjunto de dados do segmento. 
/// </summary>
/// <param name="Param_DataCount">Especifica quantos dados deve remover.</param>
CarenResult CarenD2D1SvgPathData::RemoveSegmentDataAtEnd(UInt32 Param_DataCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveSegmentDataAtEnd(Param_DataCount);

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
/// Atualiza o conjunto de comandos. Os comandos existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos comandos. 
/// </summary>
/// <param name="Param_Comandos">A matriz de comandos.</param>
/// <param name="Param_Quantidade">O número de comandos para atualizar.</param>
/// <param name="Param_StartIndex">O índice para começar a atualizar comandos. Deve ser menor ou igual ao tamanho da matriz de comandos.</param>
CarenResult CarenD2D1SvgPathData::UpdateCommands(
cli::array<CA_D2D1_SVG_PATH_COMMAND>^ Param_Comandos,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_PATH_COMMAND* pMatrizCommandos = CriarMatrizUnidimensional<D2D1_SVG_PATH_COMMAND>(static_cast<DWORD>(Param_Quantidade));

	//Copia os dados para a matriz nativa.
	Util.CopiarItensTo_ArrayNativo(&pMatrizCommandos, Param_Comandos, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateCommands(pMatrizCommandos, Param_Quantidade, Param_StartIndex);

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
	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pMatrizCommandos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza o conjunto de dados do segmento. Os dados do segmento existentes não atualizados por este método são preservados. O array é redimensionado maior, 
/// se necessário, para acomodar os dados do novo segmento. 
/// </summary>
/// <param name="Param_Dados">O conjunto de dados.</param>
/// <param name="Param_Quantidade">O número de dados para atualizar.</param>
/// <param name="Param_StartIndex">O índice para começar a atualizar os dados do segmento. Deve ser menor ou igual ao tamanho do conjunto de dados do segmento.</param>
CarenResult CarenD2D1SvgPathData::UpdateSegmentData(
cli::array<float>^ Param_Dados,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	float* pMatrizDados = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_Quantidade));

	//Copia os dados para a matriz nativa.
	Util.CopiarItensTo_ArrayNativo(&pMatrizDados, Param_Dados, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateSegmentData(pMatrizDados, Param_Quantidade, Param_StartIndex);

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
	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pMatrizDados);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1SvgAttribute)


/// <summary>
/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
/// </summary>
/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
CarenResult CarenD2D1SvgPathData::Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgAttribute* pOutClone = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Clone(&pOutClone);
	;
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

	//Cria a interface a ser retornada.
	Param_Out_CloneInterface = gcnew CarenD2D1SvgAttribute();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutClone, Param_Out_CloneInterface, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna o elemento no qual este atributo é definido. Retorna nulo se o atributo não estiver definido em nenhum elemento. 
/// </summary>
/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém um ponteiro parao elemtno no qual este atributo é definido. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgPathData::GetElement(ICaren^ Param_Out_SvgElement)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetElement(&pOutSvgElement);

	//Define o ponteiro na interface inicializada pelo usuário.
	Param_Out_SvgElement->AdicionarPonteiro(pOutSvgElement);
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgPathData::GetFactory(ICaren^ Param_Out_Factory)
{
	//Variaveis a serem utilizadas.
	ID2D1Factory* pFactory = NULL;

	//Variavel de resultados.
	CarenResult Resultado;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFactory(&pFactory);

	//Verifica se o ponteiro é válido
	if (!ObjetoValido(pFactory))
		Sair;

	//Adiciona o ponteiro na interface informada.
	Resultado = Param_Out_Factory->AdicionarPonteiro(pFactory);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera o ponteiro recuperado anteriormente.
		pFactory->Release();
		pFactory = NULL;

		//Chama uma execeção para indicar o erro.
		throw gcnew Exception(String::Format("Ocorreu uma falha ao definir o ponteiro nativo na interface gerenciada. Código de erro > {0}", Resultado.StatusCode));
	}

Done:;
}