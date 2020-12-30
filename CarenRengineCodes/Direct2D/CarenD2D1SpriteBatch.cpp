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
#include "CarenD2D1SpriteBatch.h"

//Destruidor.
CarenD2D1SpriteBatch::~CarenD2D1SpriteBatch()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1SpriteBatch::CarenD2D1SpriteBatch()
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
CarenResult CarenD2D1SpriteBatch::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenD2D1SpriteBatch::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SpriteBatch*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1SpriteBatch::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SpriteBatch*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1SpriteBatch::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SpriteBatch::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SpriteBatch::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1SpriteBatch::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SpriteBatch::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SpriteBatch::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SpriteBatch::LiberarReferencia()
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
void CarenD2D1SpriteBatch::LimparDados()
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
void CarenD2D1SpriteBatch::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1SpriteBatch();
}



// Métodos da interface proprietária(ICarenD2D1SpriteBatch)


/// <summary>
/// Adiciona os sprites dado ao final deste lote sprite.
/// No Direct2D, um sprite é definido por quatro propriedades: um retângulo de destino, um retângulo de origem, uma cor e uma transformação. Os retângulos de destino são obrigatórios, mas as demais 
/// propriedades são opcionais.
/// Sempre omitir ou passar um valor nulo para propriedades que você não deseja usar. Isso permite que o Direct2D evite armazenar valores para essas propriedades e pule totalmente seu manuseio, o 
/// que melhora a velocidade de desenho.
/// </summary>
/// <param name="Param_QuantidadeSprites">O número de sprites a serem adicionados. Isso determina quantos passos em cada matriz direct2D será lido.</param>
/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos 
/// os sprites adicionados.</param>
/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não mudará
/// a cor de nenhum dos sprites adicionados.</param>
/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que sejam
/// atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites adicionados.</param>
/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
/// será usado para cada sprite adicionado.</param>
/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
/// de origem será usado para cada sprite adicionado.</param>
/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
/// adicionado.</param>
/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
/// será usada para cada sprite adicionado.</param>
CarenResult CarenD2D1SpriteBatch::AddSprites(
UInt32 Param_QuantidadeSprites,
cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
UInt32 Param_DestinationRectanglesStride,
UInt32 Param_SourceRectanglesStride,
UInt32 Param_ColorsStride,
UInt32 Param_TransformStride)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pMatrizRectsDestino = CriarMatrizEstruturas<D2D1_RECT_F>(Param_QuantidadeSprites);
	D2D1_RECT_U* pMatrizRectsOrigem = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_COLOR_F* pMatrizCores = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_MATRIX_3X2_F* pMatrizMatrixTransforms = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_MATRIX_3X2_F* pMatrixAuxiliar = NULL; //Variavel auxiliar para copiar os dados para a matriz nativa (pMatrizMatrixTransforms).

	//Copia os dados da matriz de retangulos de destino.
	for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
	{
		//Verifica se o Id sera iniciado ou omitido.
		if (ObjetoGerenciadoValido(Param_RetangulosDestino[i]))
		{
			//Inicializa a estrutura.
			pMatrizRectsDestino[i] = { 0 };

			//Define os dados.
			pMatrizRectsDestino[i].top = Param_RetangulosDestino[i]->top;
			pMatrizRectsDestino[i].bottom = Param_RetangulosDestino[i]->bottom;
			pMatrizRectsDestino[i].right = Param_RetangulosDestino[i]->right;
			pMatrizRectsDestino[i].left = Param_RetangulosDestino[i]->left;
		}
		else
		{
			//Omite
		}
	}

	//Verifica se forneceu os retangulos de origem
	if (ObjetoGerenciadoValido(Param_RetangulosOrigem))
	{
		//Cria a matriz nativa.
		pMatrizRectsOrigem = CriarMatrizEstruturas<D2D1_RECT_U>(Param_QuantidadeSprites);

		//Copia os dados da matriz de retangulos de origem.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_RetangulosOrigem[i]))
			{
				//Inicializa a estrutura.
				pMatrizRectsOrigem[i] = { 0 };

				//Define os dados.
				pMatrizRectsOrigem[i].top = Param_RetangulosOrigem[i]->top;
				pMatrizRectsOrigem[i].bottom = Param_RetangulosOrigem[i]->bottom;
				pMatrizRectsOrigem[i].right = Param_RetangulosOrigem[i]->right;
				pMatrizRectsOrigem[i].left = Param_RetangulosOrigem[i]->left;
			}
			else
			{
				//Omite
			}
		}
	}

	//Verifica se forneceu a matriz de cores.
	if (ObjetoGerenciadoValido(Param_Cores))
	{ 
		//Cria a matriz nativa.
		pMatrizCores = CriarMatrizEstruturas<D2D1_COLOR_F>(Param_QuantidadeSprites);

		//Copia os dados da matriz de cores.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_Cores[i]))
			{
				//Inicializa a estrutura.
				pMatrizCores[i] = { 0 };

				//Define os dados.
				pMatrizCores[i].a = Param_Cores[i]->a;
				pMatrizCores[i].r = Param_Cores[i]->r;
				pMatrizCores[i].g = Param_Cores[i]->g;
				pMatrizCores[i].b = Param_Cores[i]->b;
			}
			else
			{
				//Omite
			}
		}
	}

	//Verifica se forneceu a matriz de transformações.
	if (ObjetoGerenciadoValido(Param_Transform))
	{
		//Cria a matriz nativa.
		pMatrizMatrixTransforms = CriarMatrizEstruturas<D2D1_MATRIX_3X2_F>(Param_QuantidadeSprites);

		//Copia os dados da matriz de transformações.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_Transform[i]))
			{
				//Converte a estrutura.
				pMatrixAuxiliar = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform[i]);
				
				//Define os dados.
				pMatrizMatrixTransforms[i] = *pMatrixAuxiliar;

				//Libera a memória para a matrix.
				DeletarEstruturaSafe(&pMatrixAuxiliar);
			}
			else
			{
				//Omite
			}
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddSprites(
		Param_QuantidadeSprites, 
		pMatrizRectsDestino, 
		pMatrizRectsOrigem,
		pMatrizCores, 
		pMatrizMatrixTransforms, 
		Param_DestinationRectanglesStride, 
		Param_SourceRectanglesStride, 
		Param_ColorsStride, 
		Param_TransformStride);

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
	//Libera a memória para as matrizes de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizRectsDestino);
	DeletarMatrizEstruturasSafe(&pMatrizRectsOrigem);
	DeletarMatrizEstruturasSafe(&pMatrizCores);
	DeletarMatrizEstruturasSafe(&pMatrizMatrixTransforms);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os sprites deste lote de sprite. 
/// </summary>
void CarenD2D1SpriteBatch::Clear()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->Clear();
}

/// <summary>
/// Recupera o número de sprites neste lote sprite. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de sprites neste lote de sprites.</param>
void CarenD2D1SpriteBatch::GetSpriteCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetSpriteCount();
}

/// <summary>
/// Recupera o subconjunto especificado de sprites deste lote sprite. Para obter o melhor desempenho, use NULL para propriedades que você não precisa recuperar. 
/// </summary>
/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para recuperar.</param>
/// <param name="Param_QuantidadeSprites">O número de sprites para recuperar.</param>
/// <param name="Param_Ref_RetangulosDestino">Retorna uma matriz contendo os retângulos de destino para os sprites recuperados.</param>
/// <param name="Param_Ref_RetangulosOrigem">Retorna uma matriz contendo os retângulos de origem para os sprites recuperados. O InfiniteRectU é devolvido para quaisquer sprites que não foram atribuídos 
/// a um retângulo de origem.</param>
/// <param name="Param_Ref_Cores">Retorna uma matriz contendo as cores a serem aplicadas aos sprites recuperados. A cor {1.0f, 1.0f, 1.0f, 1.0f} é devolvida para quaisquer sprites que não foram 
/// atribuídos uma cor.</param>
/// <param name="Param_Ref_Transform">Retorna uma matriz contendo as transformações a serem aplicadas aos sprites recuperados. A matriz de identidade é devolvida para quaisquer sprites que não 
/// foram atribuídos uma transformação.</param>
CarenResult CarenD2D1SpriteBatch::GetSprites(
UInt32 Param_StartIndex,
UInt32 Param_QuantidadeSprites,
cli::array<CA_D2D1_RECT_F^>^% Param_Ref_RetangulosDestino,
cli::array<CA_D2D1_RECT_U^>^% Param_Ref_RetangulosOrigem,
cli::array<CA_D2D1_COLOR_F^>^% Param_Ref_Cores,
cli::array<CA_D2D1_MATRIX_3X2_F^>^% Param_Ref_Transform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pMatrizRectsDestino = NULL; //Pode ser NULO.
	D2D1_RECT_U* pMatrizRectsOrigem = NULL; //Pode ser NULO.
	D2D1_COLOR_F* pMatrizCores = NULL; //Pode ser NULO.
	D2D1_MATRIX_3X2_F* pMatrizMatrixTransforms = NULL; //Pode ser NULO.

	//Verifica se vai requisitar os retangulos de destino
	if (ObjetoGerenciadoValido(Param_Ref_RetangulosDestino))
	{
		//Cria a matriz que vai receber os dados.
		pMatrizRectsDestino = CriarMatrizEstruturas<D2D1_RECT_F>(Param_QuantidadeSprites);
	}

	//Verifica se vai requisitar os retangulos de origem
	if (ObjetoGerenciadoValido(Param_Ref_RetangulosOrigem))
	{
		//Cria a matriz que vai receber os dados.
		pMatrizRectsOrigem = CriarMatrizEstruturas<D2D1_RECT_U>(Param_QuantidadeSprites);
	}

	//Verifica se vai requisitar a matriz de cores.
	if (ObjetoGerenciadoValido(Param_Ref_Cores))
	{
		//Cria a matriz que vai receber os dados.
		pMatrizCores = CriarMatrizEstruturas<D2D1_COLOR_F>(Param_QuantidadeSprites);
	}

	//Verifica se vai requisitar a matriz de transformações.
	if (ObjetoGerenciadoValido(Param_Ref_Transform))
	{
		//Cria a matriz que vai receber os dados.
		pMatrizMatrixTransforms = CriarMatrizEstruturas<D2D1_MATRIX_3X2_F>(Param_QuantidadeSprites);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSprites(
		Param_StartIndex,
		Param_QuantidadeSprites,
		pMatrizRectsDestino,
		pMatrizRectsOrigem,
		pMatrizCores,
		pMatrizMatrixTransforms);

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

	//Copia os dados para as matrizes que foram forneceidas.
	if (ObjetoGerenciadoValido(Param_Ref_RetangulosDestino))
	{
		//Abre um for para copiar os dados da matriz nativa.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no index especificado.
			Param_Ref_RetangulosDestino[i] = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&pMatrizRectsDestino[i]);
		}
	}
	if (ObjetoGerenciadoValido(Param_Ref_RetangulosOrigem))
	{
		//Abre um for para copiar os dados da matriz nativa.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no index especificado.
			Param_Ref_RetangulosOrigem[i] = Util.ConverterD2D1_RECT_UUnmanagedToManaged(&pMatrizRectsOrigem[i]);
		}
	}
	if (ObjetoGerenciadoValido(Param_Ref_Cores))
	{
		//Abre um for para copiar os dados da matriz nativa.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no index especificado.
			Param_Ref_Cores[i] = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&pMatrizCores[i]);
		}
	}
	if (ObjetoGerenciadoValido(Param_Ref_Transform))
	{
		//Abre um for para copiar os dados da matriz nativa.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no index especificado.
			Param_Ref_Transform[i] = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&pMatrizMatrixTransforms[i]);
		}
	}

Done:;
	//Libera a memória para as matrizes de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizRectsDestino);
	DeletarMatrizEstruturasSafe(&pMatrizRectsOrigem);
	DeletarMatrizEstruturasSafe(&pMatrizCores);
	DeletarMatrizEstruturasSafe(&pMatrizMatrixTransforms);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza as propriedades dos sprites especificados neste lote sprite. Fornecer um valor nulo para qualquer propriedade deixará essa propriedade não modificada para esse valor.
/// </summary>
/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para atualização.</param>
/// <param name="Param_QuantidadeSprites">O número de sprites para atualizar com novas propriedades. Isso determina quantos passos em cada matriz direct2D será lido.</param>
/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos os 
/// sprites atualizados.</param>
/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não 
/// alterará a cor de nenhum dos sprites atualizados.</param>
/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que 
/// sejam atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites atualizados.</param>
/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
/// será usado para cada sprite atualizado.</param>
/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
/// de origem será usado para cada sprite atualizado.</param>
/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
/// atualizado.</param>
/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
/// será usada para cada sprite atualizado.</param>
CarenResult CarenD2D1SpriteBatch::SetSprites(
UInt32 Param_StartIndex,
UInt32 Param_QuantidadeSprites,
cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
UInt32 Param_DestinationRectanglesStride,
UInt32 Param_SourceRectanglesStride,
UInt32 Param_ColorsStride,
UInt32 Param_TransformStride)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pMatrizRectsDestino = CriarMatrizEstruturas<D2D1_RECT_F>(Param_QuantidadeSprites);
	D2D1_RECT_U* pMatrizRectsOrigem = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_COLOR_F* pMatrizCores = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_MATRIX_3X2_F* pMatrizMatrixTransforms = NULL; //Pode ser NULO inteiramente ou alguns seram omitidos.
	D2D1_MATRIX_3X2_F* pMatrixAuxiliar = NULL; //Variavel auxiliar para copiar os dados para a matriz nativa (pMatrizMatrixTransforms).

	//Copia os dados da matriz de retangulos de destino.
	for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
	{
		//Verifica se o Id sera iniciado ou omitido.
		if (ObjetoGerenciadoValido(Param_RetangulosDestino[i]))
		{
			//Inicializa a estrutura.
			pMatrizRectsDestino[i] = { 0 };

			//Define os dados.
			pMatrizRectsDestino[i].top = Param_RetangulosDestino[i]->top;
			pMatrizRectsDestino[i].bottom = Param_RetangulosDestino[i]->bottom;
			pMatrizRectsDestino[i].right = Param_RetangulosDestino[i]->right;
			pMatrizRectsDestino[i].left = Param_RetangulosDestino[i]->left;
		}
		else
		{
			//Omite
		}
	}

	//Verifica se forneceu os retangulos de origem
	if (ObjetoGerenciadoValido(Param_RetangulosOrigem))
	{
		//Cria a matriz nativa.
		pMatrizRectsOrigem = CriarMatrizEstruturas<D2D1_RECT_U>(Param_QuantidadeSprites);

		//Copia os dados da matriz de retangulos de origem.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_RetangulosOrigem[i]))
			{
				//Inicializa a estrutura.
				pMatrizRectsOrigem[i] = { 0 };

				//Define os dados.
				pMatrizRectsOrigem[i].top = Param_RetangulosOrigem[i]->top;
				pMatrizRectsOrigem[i].bottom = Param_RetangulosOrigem[i]->bottom;
				pMatrizRectsOrigem[i].right = Param_RetangulosOrigem[i]->right;
				pMatrizRectsOrigem[i].left = Param_RetangulosOrigem[i]->left;
			}
			else
			{
				//Omite
			}
		}
	}

	//Verifica se forneceu a matriz de cores.
	if (ObjetoGerenciadoValido(Param_Cores))
	{
		//Cria a matriz nativa.
		pMatrizCores = CriarMatrizEstruturas<D2D1_COLOR_F>(Param_QuantidadeSprites);

		//Copia os dados da matriz de cores.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_Cores[i]))
			{
				//Inicializa a estrutura.
				pMatrizCores[i] = { 0 };

				//Define os dados.
				pMatrizCores[i].a = Param_Cores[i]->a;
				pMatrizCores[i].r = Param_Cores[i]->r;
				pMatrizCores[i].g = Param_Cores[i]->g;
				pMatrizCores[i].b = Param_Cores[i]->b;
			}
			else
			{
				//Omite
			}
		}
	}

	//Verifica se forneceu a matriz de transformações.
	if (ObjetoGerenciadoValido(Param_Transform))
	{
		//Cria a matriz nativa.
		pMatrizMatrixTransforms = CriarMatrizEstruturas<D2D1_MATRIX_3X2_F>(Param_QuantidadeSprites);

		//Copia os dados da matriz de transformações.
		for (UINT32 i = 0; i < Param_QuantidadeSprites; i++)
		{
			//Verifica se o Id sera iniciado ou omitido.
			if (ObjetoGerenciadoValido(Param_Transform[i]))
			{
				//Converte a estrutura.
				pMatrixAuxiliar = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform[i]);

				//Define os dados.
				pMatrizMatrixTransforms[i] = *pMatrixAuxiliar;

				//Libera a memória para a matrix.
				DeletarEstruturaSafe(&pMatrixAuxiliar);
			}
			else
			{
				//Omite
			}
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSprites(
		Param_StartIndex,
		Param_QuantidadeSprites,
		pMatrizRectsDestino,
		pMatrizRectsOrigem,
		pMatrizCores,
		pMatrizMatrixTransforms,
		Param_DestinationRectanglesStride,
		Param_SourceRectanglesStride,
		Param_ColorsStride,
		Param_TransformStride);

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
	//Libera a memória para as matrizes de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizRectsDestino);
	DeletarMatrizEstruturasSafe(&pMatrizRectsOrigem);
	DeletarMatrizEstruturasSafe(&pMatrizCores);
	DeletarMatrizEstruturasSafe(&pMatrizMatrixTransforms);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SpriteBatch::GetFactory(ICaren^ Param_Out_Factory)
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