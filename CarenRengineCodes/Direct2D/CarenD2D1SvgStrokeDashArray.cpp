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
#include "CarenD2D1SvgStrokeDashArray.h"

//Destruidor.
CarenD2D1SvgStrokeDashArray::~CarenD2D1SvgStrokeDashArray()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgStrokeDashArray::CarenD2D1SvgStrokeDashArray()
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
CarenResult CarenD2D1SvgStrokeDashArray::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgStrokeDashArray::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgStrokeDashArray*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgStrokeDashArray**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgStrokeDashArray::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgStrokeDashArray*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgStrokeDashArray**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgStrokeDashArray::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgStrokeDashArray::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1SvgStrokeDashArray::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1SvgStrokeDashArray::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SvgStrokeDashArray::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgStrokeDashArray::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgStrokeDashArray::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1SvgStrokeDashArray::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1SvgStrokeDashArray();
}



// Métodos da interface proprietária(ICarenD2D1SvgStrokeDashArray)


/// <summary>
/// Recebe traços(dashes) da matriz. 
/// </summary>
/// <param name="Param_Out_Dashes">O array que vai conter o dashes.</param>
/// <param name="Param_Quantidade">A contagem de elementos da matriz no argumento dashes.</param>
/// <param name="Param_StartIndex">O índice do primeiro traço a ser recuperado.</param>
CarenResult CarenD2D1SvgStrokeDashArray::GetDashes(
[Out] cli::array<float>^% Param_Out_Dashes,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	float* pOutMatrizDashes = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_Quantidade));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDashes(pOutMatrizDashes, Param_Quantidade, Param_StartIndex);

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
	Param_Out_Dashes = gcnew cli::array<float>(Param_Quantidade);

	//Copia os dados para a matriz gerenciada
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_Dashes, pOutMatrizDashes, Param_Quantidade);

Done:;
	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pOutMatrizDashes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe traços(dashes) da matriz.  
/// </summary>
/// <param name="Param_Out_Dashes">O array que vai conter o dashes.</param>
/// <param name="Param_Quantidade">A contagem de elementos da matriz no argumento dashes.</param>
/// <param name="Param_StartIndex">O índice do primeiro traço a ser recuperado.</param>
CarenResult CarenD2D1SvgStrokeDashArray::GetDashes(
[Out] cli::array<CA_D2D1_SVG_LENGTH^>^% Param_Out_Dashes,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_LENGTH* pOutDashes = CriarMatrizEstruturas<D2D1_SVG_LENGTH>(Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDashes(pOutDashes, Param_Quantidade, Param_StartIndex);

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

	//Cria ao array que será retornado.
	Param_Out_Dashes = gcnew cli::array<CA_D2D1_SVG_LENGTH^>(Param_Quantidade);

	//Faz um for para copiar os dados.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte do nativo para o gerenciado e define no array.
		Param_Out_Dashes[i] = Util.ConverterD2D1_SVG_LENGTHUnmanagedToManaged(&pOutDashes[i]);
	}

Done:;
	//Libera a memória para a matriz nativa.
	DeletarMatrizEstruturasSafe(&pOutDashes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número dos traços(dashes) na matriz. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de traços(dashes) na matriz.</param>
void CarenD2D1SvgStrokeDashArray::GetDashesCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetDashesCount();
}

/// <summary>
/// Remove traços(dashes) da extremidade da matriz. 
/// </summary>
/// <param name="Param_DashesCount">Especifica quantos traços(dashes) para remover.</param>
CarenResult CarenD2D1SvgStrokeDashArray::RemoveDashesAtEnd(UInt32 Param_DashesCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveDashesAtEnd(Param_DashesCount);

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
/// Atualiza o array. Os traços(dashes) existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos traços. 
/// </summary>
/// <param name="Param_Dashes">A matriz de traços.</param>
/// <param name="Param_Quantidade">O número de traços para atualizar.</param>
/// <param name="Param_StartIndex">O índice para começar a atualizar traços. Deve ser menor ou igual ao tamanho da matriz.</param>
CarenResult CarenD2D1SvgStrokeDashArray::UpdateDashes(
cli::array<float>^ Param_Dashes,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	float* pMatrizDashes = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_Quantidade));

	//Copia os dados para a matriz nativa.
	Util.CopiarItensTo_ArrayNativo(&pMatrizDashes, Param_Dashes, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateDashes(pMatrizDashes, Param_Quantidade, Param_StartIndex);

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
	DeletarMatrizUnidimensionalSafe(&pMatrizDashes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza o array. Os traços(dashes) existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos traços. 
/// </summary>
/// <param name="Param_Dashes">A matriz de traços.</param>
/// <param name="Param_Quantidade">O número de traços para atualizar.</param>
/// <param name="Param_StartIndex">O índice para começar a atualizar traços. Deve ser menor ou igual ao tamanho da matriz.</param>
CarenResult CarenD2D1SvgStrokeDashArray::UpdateDashes(
cli::array<CA_D2D1_SVG_LENGTH^>^ Param_Dashes,
UInt32 Param_Quantidade,
UInt32 Param_StartIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_LENGTH* pMatrizDashes = CriarMatrizEstruturas<D2D1_SVG_LENGTH>(Param_Quantidade);
	D2D1_SVG_LENGTH* pSvgAuxiliar = NULL;

	//Faz um for para converte e definir.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte a estrutura para a nativa.
		pSvgAuxiliar = Util.ConverterD2D1_SVG_LENGTHManagedToUnmanaged(Param_Dashes[i]);

		//Define na matriz.
		pMatrizDashes[i] = *pSvgAuxiliar;
		
		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pSvgAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateDashes(pMatrizDashes, Param_Quantidade, Param_StartIndex);

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
	DeletarMatrizEstruturasSafe(&pMatrizDashes);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1SvgAttribute)


/// <summary>
/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
/// </summary>
/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
CarenResult CarenD2D1SvgStrokeDashArray::Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface)
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
void CarenD2D1SvgStrokeDashArray::GetElement(ICaren^ Param_Out_SvgElement)
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
void CarenD2D1SvgStrokeDashArray::GetFactory(ICaren^ Param_Out_Factory)
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