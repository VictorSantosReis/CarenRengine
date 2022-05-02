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
#include "CarenD2D1Transform.h"

//Destruidor.
CarenD2D1Transform::~CarenD2D1Transform()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1Transform::CarenD2D1Transform()
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
CarenResult CarenD2D1Transform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Transform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Transform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Transform**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Transform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Transform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Transform**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Transform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Transform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1Transform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1Transform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Transform::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Transform::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1Transform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Transform();
}



// Métodos da interface proprietária(ICarenD2D1Transform)


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
CarenResult CarenD2D1Transform::MapInputRectsToOutputRect(
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
CarenResult CarenD2D1Transform::MapInvalidRect(
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
CarenResult CarenD2D1Transform::MapOutputRectToInputRects(
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
void CarenD2D1Transform::GetInputCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetInputCount();
}