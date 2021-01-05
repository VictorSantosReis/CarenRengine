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
#include "CarenD2D1ComputeTransform.h"

//Destruidor.
CarenD2D1ComputeTransform::~CarenD2D1ComputeTransform()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1ComputeTransform::CarenD2D1ComputeTransform()
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
CarenResult CarenD2D1ComputeTransform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenD2D1ComputeTransform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1ComputeTransform*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1ComputeTransform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1ComputeTransform*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1ComputeTransform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1ComputeTransform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1ComputeTransform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1ComputeTransform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1ComputeTransform::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1ComputeTransform::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1ComputeTransform::LiberarReferencia()
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
void CarenD2D1ComputeTransform::LimparDados()
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
void CarenD2D1ComputeTransform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1ComputeTransform();
}



// Métodos da interface proprietária(ICarenD2D1ComputeTransform)


/// <summary>
/// Este método permite que uma transformação baseada em sombreamento de computação selecione o número de grupos de segmentos para executar com base no número de pixels
/// de saída que ele precisa preencher. Se essa chamada falhar, a instância ICarenD2D1Effect correspondente é colocada em um estado de erro e falha ao desenhar.
/// </summary>
/// <param name="Param_OutputRect">O retângulo de saída que será preenchido pela transformação computacional.</param>
/// <param name="Param_Out_DimensaoX">O número de threads na dimensão X.</param>
/// <param name="Param_Out_DimensaoY">O número de threads na dimensão Y.</param>
/// <param name="Param_Out_DimensaoZ">O número de threads na dimensão Z.</param>
CarenResult CarenD2D1ComputeTransform::CalculateThreadgroups(
CA_D2D1_RECT_L^ Param_OutputRect,
[Out] UInt32% Param_Out_DimensaoX,
[Out] UInt32% Param_Out_DimensaoY,
[Out] UInt32% Param_Out_DimensaoZ)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_L* pOutputRect = NULL;
	UINT32 OutDimensionX = 0;
	UINT32 OutDimensionY = 0;
	UINT32 OutDimensionZ = 0;

	//Converte a estrutura
	pOutputRect = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_OutputRect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CalculateThreadgroups(pOutputRect, &OutDimensionX, &OutDimensionY, &OutDimensionZ);

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
	Param_Out_DimensaoX = OutDimensionX;
	Param_Out_DimensaoY = OutDimensionY;
	Param_Out_DimensaoZ = OutDimensionZ;

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pOutputRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define as informações de renderização usadas para especificar o pass de sombreador de computação.
// Se esse método falhar, o ICarenD2D1TransformGraph::AddNode falhará.
/// </summary>
/// <param name="Param_ComputeInfo">O objeto de informação de renderização a ser definido.</param>
CarenResult CarenD2D1ComputeTransform::SetComputeInfo(ICarenD2D1ComputeInfo^ Param_ComputeInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1ComputeInfo* pComputeInfo = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ComputeInfo, &pComputeInfo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetComputeInfo(pComputeInfo);

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




// Métodos da interface (ICarenD2D1Transform)


/// <summary>
/// Realiza o mapeamento inverso para MapOutputRectToInputRects.
/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
/// Ao contrário das funções MapOutputRectToInputRects e MapInvalidRect, este método é explicitamente chamado pelo renderizador em um determinado lugar em seu algoritmo de renderização. A implementação 
/// da transformação pode alterar seu estado com base nos retângulos de entrada e usar essas informações para controlar suas informações de renderização. Este método é sempre chamado antes dos métodos 
/// MapInvalidRect e MapOutputRectToInputRects da transformação.
/// </summary>
/// <param name="Param_InputRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída. O parâmetro (Param_InputRects) é sempre igual aos limites de entrada.</param>
/// <param name="Param_InputOpaqueSubRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída opaco.</param>
/// <param name="Param_QuantidadeRetangulos">O número de entradas especificadas. A implementação garante que isso seja igual ao número de entradas especificadas na transformação.</param>
/// <param name="Param_Out_OutputRect">Retorna o retângulo de saída que mapeia o retângulo de entrada correspondente.</param>
/// <param name="Param_Out_OutputOpaqueSubRect">Retorna o retângulo de saída que mapeia o retângulo de entrada opaco correspondente.</param>
CarenResult CarenD2D1ComputeTransform::MapInputRectsToOutputRect(
	cli::array<CA_D2D1_RECT_L^>^ Param_InputRects,
	cli::array<CA_D2D1_RECT_L^>^ Param_InputOpaqueSubRects,
	UInt32 Param_QuantidadeRetangulos,
	[Out] CA_D2D1_RECT_L^% Param_Out_OutputRect,
	[Out] CA_D2D1_RECT_L^% Param_Out_OutputOpaqueSubRect)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_L* pInRects = CriarMatrizEstruturas<D2D1_RECT_L>(Param_QuantidadeRetangulos);
	D2D1_RECT_L* pInOpaqueSubRects = CriarMatrizEstruturas<D2D1_RECT_L>(Param_QuantidadeRetangulos);
	D2D1_RECT_L* pRectAuxiliar = NULL;
	D2D1_RECT_L OutRect = {};
	D2D1_RECT_L OutOpaqueSubRect = {};

	//Realiza a copia dos dados da matriz (Param_InputRects).
	for (UINT32 i = 0; i < Param_QuantidadeRetangulos; i++)
	{
		//Converte a estrutura.
		pRectAuxiliar = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_InputRects[i]);

		//Define os dados.
		pInRects[i] = *pRectAuxiliar;

		//Libera a memória
		DeletarEstruturaSafe(&pRectAuxiliar);
	}

	//Realiza a copia dos dados da matriz (Param_InputOpaqueSubRects).
	for (UINT32 i = 0; i < Param_QuantidadeRetangulos; i++)
	{
		//Converte a estrutura.
		pRectAuxiliar = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_InputOpaqueSubRects[i]);

		//Define os dados.
		pInOpaqueSubRects[i] = *pRectAuxiliar;

		//Libera a memória
		DeletarEstruturaSafe(&pRectAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MapInputRectsToOutputRect(pInRects, pInOpaqueSubRects, Param_QuantidadeRetangulos, &OutRect, &OutOpaqueSubRect);

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

	//Converte as estruturas retornadas e define nos parametros de saida.
	Param_Out_OutputRect = Util.ConverterD2D1_RECT_LUnmanagedToManaged(&OutRect);
	Param_Out_OutputOpaqueSubRect = Util.ConverterD2D1_RECT_LUnmanagedToManaged(&OutOpaqueSubRect);

Done:;
	//Libera a memória para as matrizes de estruturas.
	DeletarMatrizEstruturasSafe(&pInRects);
	DeletarMatrizEstruturasSafe(&pInOpaqueSubRects);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define os retângulos de entrada para este passe de renderização na transformação.
/// A implementação da transformação deve considerar o MapInvalidRect como puramente funcional. A implementação da transformação pode basear o retângulo de entrada mapeado no estado atual da implementação 
/// da transformação, conforme especificado pelas propriedades de efeito encapsulamento. Mas a implementação da transformação não pode mudar seu próprio estado em resposta a uma chamada ao MapInvalidRect. 
/// O Direct2D pode chamar esse método a qualquer momento e em qualquer sequência após uma chamada para o método MapInputRectsToOutputRect.
/// </summary>
/// <param name="Param_InputIndex">O índice do retângulo de entrada.</param>
/// <param name="Param_InvalidInputRect">O retângulo de entrada inválido.</param>
/// <param name="Param_Out_InvalidOutputRect">Retorna o retângulo de saída para o qual o retângulo de entrada deve ser mapeado.</param>
CarenResult CarenD2D1ComputeTransform::MapInvalidRect(
	UInt32 Param_InputIndex,
	CA_D2D1_RECT_L^ Param_InvalidInputRect,
	[Out] CA_D2D1_RECT_L^% Param_Out_InvalidOutputRect)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_L* pInputInvalidRect = NULL;
	D2D1_RECT_L OutInvalidRect = {};

	//Converte a estrutura
	pInputInvalidRect = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_InvalidInputRect);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MapInvalidRect(Param_InputIndex, *pInputInvalidRect, &OutInvalidRect);

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

	//Converte a estrutura e defina no parametro de saida.
	Param_Out_InvalidOutputRect = Util.ConverterD2D1_RECT_LUnmanagedToManaged(&OutInvalidRect);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pInputInvalidRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Permite uma transformação para afirmar como mapearia um retângulo solicitado em sua saída para um conjunto de retângulos de amostra em sua entrada. 
/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
/// A implementação da transformação deve considerar esse método como puramente funcional. Ele pode basear os retângulos de entrada e saída mapeados em seu estado atual, conforme especificado pelas 
/// propriedades de efeito encapsulamento. No entanto, não deve mudar seu próprio estado em resposta a este método que está sendo invocado. A implementação do renderizador Direct2D reserva-se o direito 
/// de chamar este método a qualquer momento e em qualquer sequência.
/// </summary>
/// <param name="Param_OutputRect">O retângulo de saída do qual as entradas devem ser mapeadas.</param>
/// <param name="Param_Out_InputRects">O conjunto correspondente de entradas. As entradas corresponderão diretamente aos insumos de transformação.</param>
/// <param name="Param_InputRectsCount">O número de entradas especificadas. O Direct2D garante que isso seja igual ao número de entradas especificadas na transformação.</param>
CarenResult CarenD2D1ComputeTransform::MapOutputRectToInputRects(
	CA_D2D1_RECT_L^ Param_OutputRect,
	[Out] cli::array<CA_D2D1_RECT_L^>^% Param_Out_InputRects,
	UInt32 Param_InputRectsCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_L* pOutputRect = NULL;
	D2D1_RECT_L* pInputRects = CriarMatrizEstruturas<D2D1_RECT_L>(Param_InputRectsCount); //Retornado pelo método.

	//Converte a estrutura
	pOutputRect = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_OutputRect);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MapOutputRectToInputRects(pOutputRect, pInputRects, Param_InputRectsCount);

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
	Param_Out_InputRects = gcnew cli::array<CA_D2D1_RECT_L^>(Param_InputRectsCount);

	//Preenche os dados da matriz.
	for (UINT32 i = 0; i < Param_InputRectsCount; i++)
	{
		//Converte e define os dados no index.
		Param_Out_InputRects[i] = Util.ConverterD2D1_RECT_LUnmanagedToManaged(&pInputRects[i]);
	}

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pOutputRect);
	DeletarMatrizEstruturasSafe(&pInputRects);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1TransformNode)


/// <summary>
/// Obtém o número de entradas para o nó de transformação. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este nó de transformação.</param>
void CarenD2D1ComputeTransform::GetInputCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetInputCount();
}