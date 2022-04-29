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
#include "CarenD2D1ResourceTexture.h"

//Destruidor.
CarenD2D1ResourceTexture::~CarenD2D1ResourceTexture()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1ResourceTexture::CarenD2D1ResourceTexture()
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
CarenResult CarenD2D1ResourceTexture::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ResourceTexture::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ResourceTexture*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ResourceTexture**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ResourceTexture::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ResourceTexture*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ResourceTexture**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ResourceTexture::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ResourceTexture::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1ResourceTexture::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1ResourceTexture::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1ResourceTexture::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1ResourceTexture::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1ResourceTexture::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1ResourceTexture::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1ResourceTexture();
}



// Métodos da interface proprietária(ICarenD2D1ResourceTexture)


/// <summary>
/// Atualiza a textura específica do recurso dentro da faixa ou caixa específica usando os dados fornecidos. 
/// </summary>
/// <param name="Param_MinimumExtents">A extensão "esquerda" das atualizações se especificada; se NULO, toda a textura é atualizada.</param>
/// <param name="Param_MaximumExtents">A extensão "direita" das atualizações, se especificada; se NULO, toda a textura é atualizada.</param>
/// <param name="Param_Strides">O stride para avançar através dos dados de entrada, de acordo com a dimensão.</param>
/// <param name="Param_Dimensoes">O número de dimensões na textura do recurso. Isso deve corresponder ao número usado para carregar a textura.</param>
/// <param name="Param_Buffer">Os dados a serem colocados na textura do recurso.</param>
/// <param name="Param_DataCount">O tamanho do buffer de dados a ser usado para atualizar a textura do recurso.</param>
CarenResult CarenD2D1ResourceTexture::Update(
cli::array<UInt32>^ Param_MinimumExtents,
cli::array<UInt32>^ Param_MaximumExtents,
cli::array<UInt32>^ Param_Strides,
UInt32 Param_Dimensoes,
ICarenBuffer^ Param_Buffer,
UInt32 Param_DataCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32* pArrayMinimumExtents = NULL; //Pode ser NULO
	UINT32* pArrayMaximumExtents = NULL; //Pode ser NULO.
	UINT32* pArrayStrides = NULL;
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Verifica se forneceu os arrays e cria.
	if (ObjetoGerenciadoValido(Param_MinimumExtents))
	{
		//Cria a matriz nativa.
		pArrayMinimumExtents = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_MinimumExtents->Length));

		//Copia os dados para a matriz.
		Util.CopiarItensTo_ArrayNativo(&pArrayMinimumExtents, Param_MinimumExtents, static_cast<UINT32>(Param_MinimumExtents->Length));
	}
	if (ObjetoGerenciadoValido(Param_MaximumExtents))
	{
		//Cria a matriz nativa.
		pArrayMaximumExtents = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_MaximumExtents->Length));

		//Copia os dados para a matriz.
		Util.CopiarItensTo_ArrayNativo(&pArrayMaximumExtents, Param_MaximumExtents, static_cast<UINT32>(Param_MaximumExtents->Length));
	}

	//Cria a matriz de strides
	pArrayStrides = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Strides->Length));

	//Copia os dados para a matriz.
	Util.CopiarItensTo_ArrayNativo(&pArrayStrides, Param_Strides, static_cast<UINT32>(Param_Strides->Length));

	//Recupera o ponteiro para o buffer.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroToBuffer);

	//Verifica se não falhou
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Update(pArrayMinimumExtents, pArrayMaximumExtents, pArrayStrides, Param_Dimensoes, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer), Param_DataCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para as matrizes.
	DeletarMatrizUnidimensionalSafe(&pArrayMinimumExtents);
	DeletarMatrizUnidimensionalSafe(&pArrayMaximumExtents);
	DeletarMatrizUnidimensionalSafe(&pArrayStrides);

	//Retorna o resultado.
	return Resultado;
}