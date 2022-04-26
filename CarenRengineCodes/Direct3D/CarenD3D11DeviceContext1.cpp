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
#include "CarenD3D11DeviceContext1.h"

//Destruidor.
CarenD3D11DeviceContext1::~CarenD3D11DeviceContext1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD3D11DeviceContext1::CarenD3D11DeviceContext1()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
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
CarenResult CarenD3D11DeviceContext1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11DeviceContext1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID3D11DeviceContext1*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD3D11DeviceContext1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID3D11DeviceContext1*>(Param_PonteiroNativo);

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
CarenResult CarenD3D11DeviceContext1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD3D11DeviceContext1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD3D11DeviceContext1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD3D11DeviceContext1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11DeviceContext1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11DeviceContext1::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<ID3D11DeviceContext1*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11DeviceContext1::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<ID3D11DeviceContext1*>(PonteiroTrabalho))->Release();

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
void CarenD3D11DeviceContext1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD3D11DeviceContext1();
}






//Métodos da interface proprietária(ICarenD3D11DeviceContext1)

/// <summary>
/// (ClearView) - Define todos os elementos em uma visão de recurso para um valor.
/// </summary>
/// <param name="Param_View">Um ponteiro para uma interface ICarenD3D11View que representa a visão de recurso a ser limpa.</param>
/// <param name="Param_Cor">Um conjunto de 4 componentes(RGBA) que representa a cor para usar para limpar a visão de recurso.</param>
/// <param name="Param_ArrayRetangulos">Um array de estruturas (CA_RECT) para os retângulos na visão de recursos para limpar. Se NULO, o (ClearView) limpa toda a superfície.</param>
/// <param name="Param_QuantidadeItems">O número de retângulos no array (Param_ArrayRetangulos).</param>
CarenResult CarenD3D11DeviceContext1::ClearView(
				ICarenD3D11View^ Param_View,
				cli::array<float>^ Param_Cor,
				cli::array<CA_RECT^>^ Param_ArrayRetangulos,
				UInt32 Param_QuantidadeItems)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11View* pVisaoRecurso = NULL;
	float *pRGBAColor = CriarMatrizUnidimensional<float>(4); //4 Se refere aos 4 componentes de cor(VERMELHO - VERDE - AZUL - ALFA)
	PRECT pArrayRetangulos = NULL; //Pode ser NULO.

	//Obtém o ponteiro para o recurso de visão a ser limpo
	Resultado = Param_View->RecuperarPonteiro((LPVOID*)&pVisaoRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O ponteiro não é valido.

		//Sai do método
		goto Done;
	}

	//Copia os dados de cores para o array nativo.
	Util.CopiarItensTo_ArrayNativo(&pRGBAColor, Param_Cor, 4);

	//Verifica se foi fornencido um array com os retangulos de destino a serem limpos.
	if (ObjetoGerenciadoValido(Param_ArrayRetangulos))
	{
		//Cria a matriz nativa.
		pArrayRetangulos = CriarMatrizEstruturas<RECT>(Param_QuantidadeItems);

		//Abre um for para copiar todos os dados.
		for (UINT32 i = 0; i < Param_QuantidadeItems; i++)
		{
			//Converte e define os dados no indice da matriz.
			pArrayRetangulos[i] = *Util.ConverterRECTManagedToUnmanaged(Param_ArrayRetangulos[i]);
		}
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearView(pVisaoRecurso, pRGBAColor, pArrayRetangulos, static_cast<UINT>(Param_QuantidadeItems));

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa as matrizes para liberar a memoria utilizada.
	DeletarMatrizUnidimensionalSafe(&pRGBAColor);
	DeletarMatrizEstruturasSafe(&pArrayRetangulos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CopySubresourceRegion1) - Copia uma região de um recurso de origem para um recurso de destino.
/// </summary>
/// <param name="Param_DestinoRecurso">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_IndiceSubrecrusoDestino">Índice de sub-recurso de destino.</param>
/// <param name="Param_DestX">A coordenada X do canto superior esquerdo da região de destino.</param>
/// <param name="Param_DestY">A coordenada Y do canto superior esquerdo da região de destino. Para um sub-recurso 1D, isto deve ser zero.</param>
/// <param name="Param_DestZ">A coordenada Z do canto superior esquerdo da região de destino. Para um sub-recurso 1D ou 2D, isto deve ser zero.</param>
/// <param name="Param_FonteRecurso">Um ponteiro para o recurso de fonte</param>
/// <param name="Param_IndiceSubrecrusoFonte">Índice de sub-recurso da fonte.</param>
/// <param name="Param_OrigemBox">Uma estrutura(CAIXA 3D) que define o sub-recurso de fonte que pode ser copiado. Se nulo, o sub-recurso fonte inteiro é copiado. A caixa deve caber dentro da fonte 
/// de recurso.</param>
/// <param name="Param_CopyFlags">Um valor CA_D3D11_COPY_FLAGS que especifica como realizar a operação de cópia. Se você especificar zero para nenhuma opção de cópia, CopySubresourceRegion1 se comporta como ICarenD3D11DeviceContext::CopiarSubRecursoRegiao. Para os drivers de exibição existentes que não podem processar essas bandeiras, o tempo de execução não as usa.</param>
CarenResult CarenD3D11DeviceContext1::CopySubresourceRegion1(
				ICarenD3D11Resource^ Param_DestinoRecurso,
				UInt32 Param_IndiceSubrecrusoDestino,
				UInt32 Param_DestX,
				UInt32 Param_DestY,
				UInt32 Param_DestZ,
				ICarenD3D11Resource^ Param_FonteRecurso,
				UInt32 Param_IndiceSubrecrusoFonte,
				Estruturas::CA_D3D11_BOX^ Param_OrigemBox,
				CA_D3D11_COPY_FLAGS Param_CopyFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecursoDestino = NULL;
	ID3D11Resource* pRecursoOrigem = NULL;
	D3D11_BOX* pCaixa = NULL; //Pode ser NULO.
	UINT CopyFlags = static_cast<UINT>(Param_CopyFlags);

	//Obtém o ponteiro para o recurso de DESTINO
	Resultado = Param_DestinoRecurso->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para o recurso de ORIGEM
	Resultado = Param_FonteRecurso->RecuperarPonteiro((LPVOID*)&pRecursoOrigem);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Verifica se forneceu uma caixa e converte a estrutura.
	if (ObjetoGerenciadoValido(Param_OrigemBox))
	{
		//Converte a estrutura gerenciada para nativa.
		pCaixa = Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_OrigemBox);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CopySubresourceRegion1(
		pRecursoDestino, 
		Param_IndiceSubrecrusoDestino, 
		Param_DestX, 
		Param_DestY, 
		Param_DestZ, 
		pRecursoOrigem,
		Param_IndiceSubrecrusoFonte, 
		pCaixa ? pCaixa : NULL, 
		CopyFlags);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a estrutura se valida
	DeletarEstruturaSafe(&pCaixa);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetConstantBuffers1) - Obtém os buffers constantes que o estágio de sombreador de computação usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Recebe uma matriz com os ponteiros para os buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_MatrizBuffers) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_MatrizBuffers) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::CSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador de computação usa.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::CSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DiscardResource) - Descarta um recurso do contexto do dispositivo.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para a interface de recurso a ser dercartada. O recurso deve ter sido criado com uso D3D11_USAGE_DEFAULT ou D3D11_USAGE_DYNAMIC, 
/// caso contrário, o tempo de execução derruba a chamada para o (DiscardResource); se a camada de depuração estiver ativada, o tempo de execução retorna uma mensagem de erro.</param>
CarenResult CarenD3D11DeviceContext1::DiscardResource(ICarenD3D11Resource^ Param_Recurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecurso = NULL;

	//Obtém o ponteiro para o recurso
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro não é valido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DiscardResource(pRecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DiscardView) - Descarta uma visão de recurso do contexto do dispositivo.
/// </summary>
/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
/// retorna uma mensagem de erro.</param>
CarenResult CarenD3D11DeviceContext1::DiscardView(ICarenD3D11View^ Param_Visão)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11View* pView = NULL;

	//Obtém o ponteiro para o recurso
	Resultado = Param_Visão->RecuperarPonteiro((LPVOID*)&pView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro não é valido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DiscardView(pView);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DiscardView1) - Descarta os elementos especificados em uma visão de recurso do contexto do dispositivo.
/// </summary>
/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
/// retorna uma mensagem de erro.</param>
/// <param name="Param_MatrizRetangulos">Uma matriz de estruturas CA_RECT para os retângulos na visão de recurso para descartar. Se NULO, o DiscardView1 descarta toda a 
/// visualização e se comporta da mesma forma que o DiscardView.</param>
/// <param name="Param_NumeroRetangulos">A quantidade de retangulos no array (Param_MatrizRetangulos).</param>
CarenResult CarenD3D11DeviceContext1::DiscardView1(ICarenD3D11View^ Param_Visão, cli::array<CA_RECT^>^ Param_MatrizRetangulos, UInt32 Param_NumeroRetangulos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11View* pView = NULL;
	PRECT pArrayRetangulos = NULL;
	PRECT pRetangulo = NULL;

	//Obtém o ponteiro para o recurso
	Resultado = Param_Visão->RecuperarPonteiro((LPVOID*)&pView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro não é valido.

		//Sai do método
		goto Done;
	}

	//Verifica se forneceu os retagulos
	if (ObjetoGerenciadoValido(Param_MatrizRetangulos))
	{
		//Cria a matriz nativa.
		pArrayRetangulos = CriarMatrizEstruturas<RECT>(Param_NumeroRetangulos);

		//Copia os dados da matriz gerenciada para a nativa.
		for (UINT32 i = 0; i < Param_NumeroRetangulos; i++)
		{
			//Converte a estrutura gerenciada e define no array natvo.
			pRetangulo = Util.ConverterRECTManagedToUnmanaged(Param_MatrizRetangulos[i]);

			//Define os dados da estrutura convertida no array nativo.
			pArrayRetangulos[i] = *pRetangulo;

			//Libera a memória para a estrutura.
			DeletarMatrizEstruturasSafe(&pRetangulo);
		}
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DiscardView1(pView, pArrayRetangulos, Param_NumeroRetangulos);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a matriz de estruturas se valida.
	DeletarMatrizEstruturasSafe(&pArrayRetangulos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSGetConstantBuffers1) - Obtém os buffers constantes que o estágio de sombreador de domínio usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::DSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador de domínio usa.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::DSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do duto de sombreia de geometria usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::GSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSSetConstantBuffers1) - Define os buffers constantes que o estágio do duto de sombreia de geometria usa.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::GSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSGetConstantBuffers1) - Recebe os buffers constantes que o palco do sombreador do casco usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::HSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador do casco do gasoduto usa.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::HSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do gasoduto shader pixel usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::PSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSSetConstantBuffers1) - Define os buffers constantes que o estágio do duto de sombreador de pixels usa e permite que o sombreador acesse outras partes do buffer.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::PSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SwapDeviceContextState) - Ativa o objeto de estado de contexto dado e altera o comportamento atual do dispositivo para Direct3D 11, Direct3D 10.1 ou Direct3D 10.
/// </summary>
/// <param name="Param_Estado">Um ponteiro para a interface ICarenD3DDeviceContextState para o objeto de estado de contexto que foi criado anteriormente através do método 
/// ICarenD3D11Device1::CreateDeviceContextState. Se o SwapDeviceContextState for chamado com o (Param_Estado) definido como NULO,a chamada não tem efeito.</param>
/// <param name="Param_Out_EstadoAnterior">Recebe um ponteiro para a interface ICarenD3DDeviceContextState com o estado do objeto anteriormente ativado.</param>
CarenResult CarenD3D11DeviceContext1::SwapDeviceContextState(
				ICarenD3DDeviceContextState^ Param_Estado, 
				[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoAnterior)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3DDeviceContextState* pEstadoAtual = NULL;
	ID3DDeviceContextState* pOutEstadoAnterior = NULL;

	//Recupera o ponteiro para o estado atuak.
	Resultado = Param_Estado->RecuperarPonteiro((LPVOID*)&pEstadoAtual);

	//Verifica o resultado
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.
		
		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SwapDeviceContextState(pEstadoAtual, &pOutEstadoAnterior);

	//Cria a interface do estado anterior a ser retornada
	Param_Out_EstadoAnterior = gcnew CarenD3DDeviceContextState();

	//Define o ponteiro para a interface
	Param_Out_EstadoAnterior->AdicionarPonteiro(pOutEstadoAnterior);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UpdateSubresource1) - A CPU copia dados da memória para um subrecurso criado em memória não mappável.
/// </summary>
/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_SubrecursoDestino">Um índice baseado em zero, que identifica o sub-destino do destino.</param>
/// <param name="Param_Caixa">Uma caixa que define a parte do sub-destino de destino para copiar os dados do recurso. Coordenadas são em bytes para buffers e em texels para texturas. Se NULO, os dados são
/// gravados no subfonte de destino sem nenhum deslocamento. As dimensões da fonte devem caber no destino</param>
/// <param name="Param_DadosOrigemMemoria">Um ponteiro para os dados de origem na memória.</param>
/// <param name="Param_TamanhoLinhaOrigem">(SrcRowPitch) - O tamanho de uma linha dos dados de origem.</param>
/// <param name="Param_TamhoFatiaProdundidade">(SrcDepthPitch) - O tamanho de uma fatia de profundidade dos dados de origem.</param>
/// <param name="Param_CopyFlags">Um valor D3D11_COPY_FLAGS que especifica como realizar a operação de atualização. Se você especificar zero para nenhuma opção de atualização,
/// o (UpdateSubresource1) se comporta como ICarenD3D11DeviceContext::UpdateSubresource. Para os drivers de exibição existentes que não podem processar essas bandeiras, 
/// o tempo de execução não as usa.</param>
CarenResult CarenD3D11DeviceContext1::UpdateSubresource1(
				ICarenD3D11Resource^ Param_RecursoDestino,
				UInt32 Param_SubrecursoDestino,
				Estruturas::CA_D3D11_BOX^ Param_Caixa,
				ICarenBuffer^ Param_DadosOrigemMemoria,
				UInt32 Param_TamanhoLinhaOrigem,
				UInt32 Param_TamhoFatiaProdundidade,
				CA_D3D11_COPY_FLAGS Param_CopyFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecursoDestino = NULL;
	D3D11_BOX* pBOX = NULL; //Pode ser NULO.
	PVOID pDadosOrigem = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;
	UINT CopyFlags = static_cast<UINT>(Param_CopyFlags);

	//Recupera o ponteiro para a interface de recurso.
	Resultado = Param_RecursoDestino->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Converte a caixa do d3d11 se valida
	if (ObjetoGerenciadoValido(Param_Caixa))
	{
		//Converte a caixa gerenciada para a nativa.
		pBOX = Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_Caixa);
	}

	//Recupera o ponteiros para os dados de origem.
	Param_DadosOrigemMemoria->GetInternalPointer(PonteiroDados); 
	
	//Define o ponteiro dos dados.
	pDadosOrigem = PonteiroDados.ToPointer();

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UpdateSubresource1(pRecursoDestino, Param_SubrecursoDestino, pBOX ? pBOX : NULL, pDadosOrigem, Param_TamanhoLinhaOrigem, Param_TamhoFatiaProdundidade, CopyFlags);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Deleta a estrutura se ela for valida
	DeletarEstruturaSafe(&pBOX);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do gasoduto de shader de vértice usa.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
/// constantes em cada buffer.</param>
CarenResult CarenD3D11DeviceContext1::VSGetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VetorDataInterface;
	UINT32* pOutArrayMatrizInicioConstantes = NULL;
	UINT32* pOutArrayNumeroConstantes = NULL;
	UINT32 QtdItens = 0;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSGetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data(), pOutArrayMatrizInicioConstantes, pOutArrayNumeroConstantes);

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Obtém a quantidade de itens no vetor.
	QtdItens = static_cast<UINT32>(VetorDataInterface.size());

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(QtdItens);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Verifica se retornou os dados da matriz de constantes 
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizInicioConstante = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizInicioConstante, pOutArrayMatrizInicioConstantes, QtdItens);
	}

	//Verifica se retornou os dados da matriz que contém a quantidade de constante no buffer.
	if (ObjetoValido(pOutArrayMatrizInicioConstantes))
	{
		//A quantidade de itens nesse array nativo é igual a quantidade de buffers retornado pelo vetor.

		//Cria o parametro que vai retornar esses valores.
		Param_Out_MatrizNumeroConstantes = gcnew cli::array<UInt32>(QtdItens);

		//Copia os dados do array nativo para o gerenciado
		Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizNumeroConstantes, pOutArrayNumeroConstantes, QtdItens);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Limpa as matrizes (O MSDN NAO FALA SOBRE COMO A MEMÓRIA É ALOCADA PARA OS PONTEIROS)
	pOutArrayMatrizInicioConstantes = NULL;
	pOutArrayNumeroConstantes = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSSetConstantBuffers1) - Define os buffers constantes que o estágio do gasoduto de shader de vértice usa.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
CarenResult CarenD3D11DeviceContext1::VSSetConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfacesBuffers;
	UINT32* pArrayInicioConstantes = NULL;
	UINT32* pArrayNumeroConstantes = NULL;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfacesBuffers.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfacesBuffers.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Verifica se a matrize de constantes é valida e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizInicioConstante))
	{
		//Cria a matriz nativa.
		pArrayInicioConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizInicioConstante->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayInicioConstantes, Param_MatrizInicioConstante, static_cast<UINT32>(Param_MatrizInicioConstante->Length));
	}

	//Verifica se a matriz com a quantidade de constantes são validas e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizNumeroConstantes))
	{
		//Cria a matriz nativa.
		pArrayNumeroConstantes = CriarMatrizUnidimensional<UINT32>(Param_MatrizNumeroConstantes->Length);

		//Copia os dados para a matriz nativa.
		Util.CopiarItensTo_ArrayNativo(&pArrayNumeroConstantes, Param_MatrizNumeroConstantes, static_cast<UINT32>(Param_MatrizNumeroConstantes->Length));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSSetConstantBuffers1(Param_StartSlot, Param_NumeroBuffers, VectorInterfacesBuffers.data(), pArrayInicioConstantes, pArrayNumeroConstantes);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfacesBuffers.clear();
	VectorInterfacesBuffers.shrink_to_fit();


	//Libera a memoria para os arrays nativos se validos.
	DeletarMatrizUnidimensionalSafe(&pArrayInicioConstantes);
	DeletarMatrizUnidimensionalSafe(&pArrayNumeroConstantes);

	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface ICarenD3D11DeviceContext

/// <summary>
/// (Begin) - Marca o início de uma série de comandos.
/// </summary>
/// <param name="Param_Async">Um ponteiro para a interface de sincronização.</param>
CarenResult CarenD3D11DeviceContext1::Begin(ICarenD3D11Asynchronous^ Param_Async)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Asynchronous* pAsync = NULL;

	//Recupera o ponteiro para a interface
	Resultado = Param_Async->RecuperarPonteiro((LPVOID*)&pAsync);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Begin(pAsync);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ClearDepthStencilView) - Limpa o recurso de profundidade-estêncil.
/// </summary>
/// <param name="Param_DepthStencil">Ponteiro para o estêncil de profundidade a ser apurados.</param>
/// <param name="Param_ClearFlags">Identifica o tipo de dados para limpar </param>
/// <param name="Param_Depth">Limpe o buffer de profundidade com esse valor. Este valor irá ser fixada entre 0 e 1.</param>
/// <param name="Param_Stencil">Limpe o buffer de estêncil com esse valor.</param>
CarenResult CarenD3D11DeviceContext1::ClearDepthStencilView(
	ICarenD3D11DepthStencilView^ Param_DepthStencil,
	Enumeracoes::CA_D3D11_CLEAR_FLAG Param_ClearFlags,
	float Param_Depth,
	Byte Param_Stencil)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DepthStencilView* pStencil = NULL;
	UINT FlagClear = static_cast<UINT>(Param_ClearFlags);

	//Recupera o ponteiro para a interface
	Resultado = Param_DepthStencil->RecuperarPonteiro((LPVOID*)&pStencil);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearDepthStencilView(pStencil, FlagClear, Param_Depth, Param_Stencil);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ClearRenderTargetView) - Defina todos os elementos em um destino de processamento para um valor.
/// </summary>
/// <param name="Param_RenderTarget">Ponteiro para o destino de processamento.</param>
/// <param name="Param_Cor">Uma estrutura de 4 componentes que representam a cor para preencher o destino de processamento.</param>
CarenResult CarenD3D11DeviceContext1::ClearRenderTargetView(
	ICarenD3D11RenderTargetView^ Param_RenderTarget,
	Estruturas::CA_DXGI_RGBA^ Param_Cor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11RenderTargetView* pView = NULL;
	FLOAT* pRGBAColor = Util.Converter_DXGIRGBATo_FloatColor(Param_Cor);

	//Recupera o ponteiro para render target
	Resultado = Param_RenderTarget->RecuperarPonteiro((LPVOID*)&pView);

	//Verifica se não houve erro.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearRenderTargetView(pView, pRGBAColor);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a matriz.
	delete[] pRGBAColor;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ClearState) - Restaure todas as configurações padrão. 
/// </summary>
CarenResult CarenD3D11DeviceContext1::ClearState()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearState();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ClearUnorderedAccessViewFloat) - Limpa um recurso de acesso não ordenada, com um valor float.
/// Essa API funciona em FLOAT, UNORM e SNORM não ordenada acesso visualizações (UAVs), com formato de conversão de FLOAT para * norma se for caso disso. Em outros UAVs, a operação é inválida e a chamada 
/// não atingirá o driver.
/// </summary>
/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
CarenResult CarenD3D11DeviceContext1::ClearUnorderedAccessViewFloat(
	ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
	cli::array<float>^ Param_Valores)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11UnorderedAccessView* pAcessView = NULL;
	FLOAT* pValores = new FLOAT[4]; //4 é um valor fixo.

	//Recupera o ponteiro para a interface
	Resultado = Param_UnorderedAccess->RecuperarPonteiro((LPVOID*)&pAcessView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Copia os dados do array
	Util.CopiarItensTo_ArrayNativo(&pValores, Param_Valores, Param_Valores->Length);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearUnorderedAccessViewFloat(pAcessView, pValores);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ClearUnorderedAccessViewUint) - Limpa um recurso de acesso não ordenada com valores de bit de precisão.
/// Essa API copia o menor n bits de cada elemento da matriz para o correspondente canalizo, onde n é o número de bits no canal ith do formato de recurso (por exemplo, R8G8B8_FLOAT tem 8 bits para os 3 
/// primeiros canais). Isto funciona em qualquer UAV com nenhuma conversão de formato. Para uma visão de buffer CRU ou estruturados, somente o primeiro valor de elemento matriz é usado.
/// </summary>
/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
CarenResult CarenD3D11DeviceContext1::ClearUnorderedAccessViewUint(
	ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
	cli::array<UInt32>^ Param_Valores)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	Utilidades Util;
	ID3D11UnorderedAccessView* pAcessView = NULL;
	UINT* pValores = new UINT[4]; //4 É um valor fixo.

	//Recupera o ponteiro para a interface
	Resultado = Param_UnorderedAccess->RecuperarPonteiro((LPVOID*)&pAcessView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Copia os dados do array
	Util.CopiarItensTo_ArrayNativo(&pValores, Param_Valores, Param_Valores->Length);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearUnorderedAccessViewUint(pAcessView, pValores);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CopyResource) - Copie todo o conteúdo do recurso de fonte para o recurso de destino usando o GPU.
/// </summary>
/// <param name="Param_DestinoRecurso">Um ponteiro para a interface ID3D11Resource que representa o DESTINO do recurso.</param>
/// <param name="Param_OrigemRecurso">Um ponteiro para a interface ID3D11Resource que representa a FONTE de recursos.</param>
CarenResult CarenD3D11DeviceContext1::CopyResource(
	ICarenD3D11Resource^ Param_DestinoRecurso,
	ICarenD3D11Resource^ Param_OrigemRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecursoDestino = NULL;
	ID3D11Resource* pRecursoOrigem = NULL;

	//Obtém o ponteiro para o recurso de DESTINO
	Resultado = Param_DestinoRecurso->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para o recurso de ORIGEM
	Resultado = Param_OrigemRecurso->RecuperarPonteiro((LPVOID*)&pRecursoOrigem);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CopyResource(pRecursoDestino, pRecursoOrigem);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CopyStructureCount) - Copia dados de um buffer de dados de comprimento variável a segurar.
/// </summary>
/// <param name="Param_DestinoBuffer">Ponteiro para ID3D11Buffer. Isso pode ser qualquer recurso de buffer que outros comandos de cópia, tais como ICarenD3D11DeviceContext::CopiarRecurso ou 
/// ICarenD3D11DeviceContext::CopiarSubRecursoRegiao, são capazes de gravar.</param>
/// <param name="Param_DestinoAlignedOffsetByte">Offset do início do Param_DestinoBuffer para gravar contagem de estrutura(vértice) UINT 32 bits de Param_OrigemView.</param>
/// <param name="Param_OrigemView">Ponteiro para um ID3D11UnorderedAccessView de um recurso de Buffer estruturado criado com D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER especificado 
/// quando o UAV foi criado. Esses tipos de recursos tem escondido os contadores foram escritos "Quantos" registros de rastreamento.</param>
CarenResult CarenD3D11DeviceContext1::CopyStructureCount(
	ICarenD3D11Buffer^ Param_DestinoBuffer,
	UInt32 Param_DestinoAlignedOffsetByte,
	ICarenD3D11UnorderedAccessView^ Param_OrigemView)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Buffer* pBufferDestino = NULL;
	ID3D11UnorderedAccessView* pAcessView = NULL;

	//Obtém o ponteiro para a interface do buffer.
	Resultado = Param_DestinoBuffer->RecuperarPonteiro((LPVOID*)&pBufferDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para a interface do Acess View.
	Resultado = Param_OrigemView->RecuperarPonteiro((LPVOID*)&pAcessView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CopyStructureCount(pBufferDestino, Param_DestinoAlignedOffsetByte, pAcessView);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CopySubresourceRegion) - Copie uma região de uma fonte de recursos para um recurso de destino.
/// </summary>
/// <param name="Param_DestinoRecurso">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_IndiceSubrecrusoDestino">Índice de sub-recurso de destino.</param>
/// <param name="Param_DestX">A coordenada X do canto superior esquerdo da região de destino.</param>
/// <param name="Param_DestY">A coordenada Y do canto superior esquerdo da região de destino. Para um sub-recurso 1D, isto deve ser zero.</param>
/// <param name="Param_DestZ">A coordenada Z do canto superior esquerdo da região de destino. Para um sub-recurso 1D ou 2D, isto deve ser zero.</param>
/// <param name="Param_FonteRecurso">Um ponteiro para o recurso de fonte</param>
/// <param name="Param_IndiceSubrecrusoFonte">Índice de sub-recurso da fonte.</param>
/// <param name="Param_OrigemBox">Uma estrutura(CAIXA 3D) que define o sub-recurso de fonte que pode ser copiado. Se nulo, o sub-recurso fonte inteiro é copiado. A caixa deve caber dentro da fonte 
/// de recurso.</param>
CarenResult CarenD3D11DeviceContext1::CopySubresourceRegion(
	ICarenD3D11Resource^ Param_DestinoRecurso,
	UInt32 Param_IndiceSubrecrusoDestino,
	UInt32 Param_DestX,
	UInt32 Param_DestY,
	UInt32 Param_DestZ,
	ICarenD3D11Resource^ Param_FonteRecurso,
	UInt32 Param_IndiceSubrecrusoFonte,
	Estruturas::CA_D3D11_BOX^ Param_OrigemBox
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecursoDestino = NULL;
	ID3D11Resource* pRecursoOrigem = NULL;
	D3D11_BOX* pCaixa = NULL; //Pode ser NULO.

	//Obtém o ponteiro para o recurso de DESTINO
	Resultado = Param_DestinoRecurso->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para o recurso de ORIGEM
	Resultado = Param_FonteRecurso->RecuperarPonteiro((LPVOID*)&pRecursoOrigem);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Verifica se forneceu uma caixa e converte a estrutura.
	if (ObjetoGerenciadoValido(Param_OrigemBox))
	{
		//Converte a estrutura gerenciada para nativa.
		pCaixa = Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_OrigemBox);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CopySubresourceRegion(pRecursoDestino, Param_IndiceSubrecrusoDestino, Param_DestX, Param_DestY, Param_DestZ, pRecursoOrigem, Param_IndiceSubrecrusoFonte, pCaixa ? pCaixa : NULL);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a estrutura se valida
	DeletarEstruturaSafe(&pCaixa);



	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetConstantBuffers) - Obtém os buffers constantes usados pelo estágio de computação do Shader(Sombreamento).
/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar IUnknown:: Release sobre as interfaces retornadas quando eles não são mais necessários 
/// para evitar vazamentos de memória.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumerosBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_BuffersConstantes">Recebe uma matriz com os ponteiros para os buffers constantes.</param>
CarenResult CarenD3D11DeviceContext1::CSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumerosBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_BuffersConstantes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumerosBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetConstantBuffers(Param_StartSlot, Param_NumerosBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_BuffersConstantes = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumerosBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumerosBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_BuffersConstantes[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_BuffersConstantes[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetSamplers) - Obtém uma variedade de interfaces de estado do amostrador desde a fase de computação-shader. 
/// </summary>
/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroSamplers">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot).</param>
/// <param name="Param_Out_SamplersState">Recebe uma matriz com os ponteiros para os amostradores de estado(Samplers States).</param>
CarenResult CarenD3D11DeviceContext1::CSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroSamplers,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_SamplersState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroSamplers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetSamplers(Param_StartSlot, Param_NumeroSamplers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_SamplersState = gcnew cli::array<ICarenD3D11SamplerState^>(Param_NumeroSamplers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroSamplers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_SamplersState[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_SamplersState[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetShader) - Se o sombreador de computação atualmente definido no dispositivo.
/// </summary>
/// <param name="Param_Out_ComputeShader">Retorna uma ponteiro para a interface de Shader Compute.</param>
/// <param name="Param_Out_ArrayClassInstance">Retorna um Array que contém ponteiros para Instâncias de Classe.</param>
/// <param name="Param_Out_QuantidadeClass">Retorna a quantidade de itens no array do parametro (Param_Out_ArrayClassInstance).</param>
CarenResult CarenD3D11DeviceContext1::CSGetShader(
	[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_ArrayClassInstance,
	[Out] UInt32% Param_Out_QuantidadeClass)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11ComputeShader* pComputeShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetShader(&pComputeShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pComputeShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_ComputeShader = gcnew CarenD3D11ComputeShader();

		//Define o ponteiro de trabalho
		Param_Out_ComputeShader->AdicionarPonteiro(pComputeShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pComputeShader) ? CarenResult(ResultCode::SS_OK, true): CarenResult(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_ArrayClassInstance = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_ArrayClassInstance[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_ArrayClassInstance[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens na matriz.
	Param_Out_QuantidadeClass = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetShaderResources) - Obter os recursos de computação-shader.
/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
/// necessários para evitar vazamentos de memória.
/// </summary>
/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizShaderRecursoSombreador">Retorna uma Matriz com ponteiros de exibição de recurso de sombreador retornado pelo Dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::CSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroRecursos,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizShaderRecursoSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetShaderResources(Param_StartSlot, Param_NumeroRecursos, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizShaderRecursoSombreador = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_NumeroRecursos);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroRecursos; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizShaderRecursoSombreador[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizShaderRecursoSombreador[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSGetUnorderedAccessViews) - Obtém uma matriz de pontos de vista de um recurso não-ordenado.
/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
/// necessários para evitar vazamentos de memória.
/// </summary>
/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para retornar (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroUAVs">Número de pontos de vista para obter (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizInterfacesNaoOrdenadas">Retorna uma Matriz que contém ponteiros para as interfaces ID3D11UnorderedAccessView.</param>
CarenResult CarenD3D11DeviceContext1::CSGetUnorderedAccessViews(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroUAVs,
	[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizInterfacesNaoOrdenadas)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	vector<ID3D11UnorderedAccessView*> VectorUnordered;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSGetUnorderedAccessViews(Param_StartSlot, Param_NumeroUAVs, VectorUnordered.data());

	//Verifica se obteve alguma interface.
	if (!VectorUnordered.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizInterfacesNaoOrdenadas = gcnew cli::array<ICarenD3D11UnorderedAccessView^>(Param_NumeroUAVs);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroUAVs; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInterfacesNaoOrdenadas[i] = gcnew CarenD3D11UnorderedAccessView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInterfacesNaoOrdenadas[i]->AdicionarPonteiro(VectorUnordered[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetConstantBuffers) - Define os constantes buffers usados pela fase computação-shader.
/// O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
/// Se o aplicativo deseja o sombreador para acessar outras partes da reserva, ele deve chamar o método CSSetConstantBuffers1 em vez disso.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::CSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de computação-shader.
/// </summary>
/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroSamplers">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizSamplers">Uma matriz de interfaces do amostrador de estado a serem definidas no dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::CSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroSamplers,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizSamplers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroSamplers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroSamplers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizSamplers[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetSamplers(Param_StartSlot, Param_NumeroSamplers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetShader) - Defina um sombreador de computação para o dispositivo.
/// O número máximo de instâncias que pode ter um sombreador é 256.
/// </summary>
/// <param name="Param_ComputeShader">Ponteiro para um sombreador de computação. Passando NULO (DESABILITA) o sombreador para este estágio de pipeline.</param>
/// <param name="Param_MatrizClassInstance">Um ponteiro para uma matriz que contem as interfaces de instâncias de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader 
/// vai ser desativado. Definir Param_MatrizClassInstance para NULO se o sombreador não usa quaisquer interfaces.</param>
/// <param name="Param_QuantidadeClassInstances">A quantidade de itens no array do parametro (Param_MatrizClassInstance).</param>
CarenResult CarenD3D11DeviceContext1::CSSetShader(
	ICarenD3D11ComputeShader^ Param_ComputeShader,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizClassInstance,
	UInt32 Param_QuantidadeClassInstances)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11ComputeShader* pComputeShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_QuantidadeClassInstances > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_QuantidadeClassInstances));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_QuantidadeClassInstances; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizClassInstance[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador se ele tiver sido fornecido.
	if (ObjetoGerenciadoValido(Param_ComputeShader))
	{
		//Recupera o ponteiro para a interface.
		Param_ComputeShader->RecuperarPonteiro((LPVOID*)&pComputeShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetShader(pComputeShader ? pComputeShader : NULL, Param_QuantidadeClassInstances > 0 ? VectorInterfaces.data() : NULL, Param_QuantidadeClassInstances);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de computação-shader.
/// </summary>
/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot).</param>
/// <param name="Param_MatrizShaderRecursoSombreador">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::CSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroRecursos,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizShaderRecursoSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroRecursos));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroRecursos; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizShaderRecursoSombreador[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetShaderResources(Param_StartSlot, Param_NumeroRecursos, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CSSetUnorderedAccessViews) - Define uma matriz de pontos de vista para um recurso não-ordenada.
/// </summary>
/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para começar a configuração (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1). D3D11_1_UAV_SLOT_COUNT é definido como 64.</param>
/// <param name="Param_NumeroUAVs">Número de pontos de vista para definir (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizInterfacesNaoOrdenadas">Um ponteiro para uma matriz de ponteiros de ID3D11UnorderedAccessView a ser definido pelo método.</param>
/// <param name="Param_MatrizInitialUAVsCount">Uma matriz de acrescentar e consumir deslocamentos de reserva. Um valor de -1 indica que para manter o atual deslocamento. Quaisquer outros valores definir o 
/// contador oculto para aquele UAV (APPENDABLE) e consumíveis. Param_MatrizInitialUAVsCount só é relevante para UAVs que foram criados com qualquer D3D11_BUFFER_UAV_FLAG_APPEND ou 
/// D3D11_BUFFER_UAV_FLAG_COUNTER especificado quando o UAV foi criado; caso contrário, o argumento é ignorado.</param>
CarenResult CarenD3D11DeviceContext1::CSSetUnorderedAccessViews(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroUAVs,
	cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizInterfacesNaoOrdenadas,
	cli::array<UInt32>^ Param_MatrizInitialUAVsCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11UnorderedAccessView*> VectorInterfaces;
	UINT* pUAVsMatriz = NULL;
	ID3D11UnorderedAccessView* pUnorderedView = NULL;
	UINT CountMatrizInterfaces = static_cast<UINT>(Param_MatrizInterfacesNaoOrdenadas->Length);
	UINT CountMatrizUAVs = 0;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(CountMatrizInterfaces));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < CountMatrizInterfaces; i++)
	{
		//Recupera o ponteiro para a interface.
		Param_MatrizInterfacesNaoOrdenadas[i]->RecuperarPonteiro((LPVOID*)&pUnorderedView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pUnorderedView);

		//Limpa
		pUnorderedView = NULL;
	}

	//Verifica se forneceu uma matriz de uavs
	if (ObjetoGerenciadoValido(Param_MatrizInitialUAVsCount))
	{
		//Foreneceu a matriz.

		//Obtém a quantidade de itens.
		CountMatrizUAVs = static_cast<UINT>(Param_MatrizInitialUAVsCount->Length);

		//Inicializa a matriz.
		pUAVsMatriz = new UINT[CountMatrizUAVs];

		//Copia os dados do array gerenciado para o nativo.
		Util.CopiarItensTo_ArrayNativo(&pUAVsMatriz, Param_MatrizInitialUAVsCount, CountMatrizUAVs);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CSSetUnorderedAccessViews(Param_StartSlot, Param_NumeroUAVs, VectorInterfaces.data(), pUAVsMatriz ? pUAVsMatriz : NULL);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Libera a memoria do array de unsigned int se ele for valido.
	if (ObjetoValido(pUAVsMatriz))
	{
		//Libera a memoria para o array.
		delete[] pUAVsMatriz;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Dispatch) - Execute uma lista de comando de um grupo de discussão.
/// </summary>
/// <param name="Param_NumeroGrupoExpedidoX">O número de grupos expedidos na direção X. NumeroGrupoExpedidoX deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
/// <param name="Param_NumeroGrupoExpedidoY">O número de grupos expedidos na direção Y. NumeroGrupoExpedidoY deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
/// <param name="Param_NumeroGrupoExpedidoZ">O número de grupos expedidos na direção Z. NumeroGrupoExpedidoZ deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535). 
/// Em nível de recurso 10 o valor para NumeroGrupoExpedidoZ deve ser 1.</param>
CarenResult CarenD3D11DeviceContext1::Dispatch(
	UInt32 Param_NumeroGrupoExpedidoX,
	UInt32 Param_NumeroGrupoExpedidoY,
	UInt32 Param_NumeroGrupoExpedidoZ)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Dispatch(Param_NumeroGrupoExpedidoX, Param_NumeroGrupoExpedidoY, Param_NumeroGrupoExpedidoZ);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DispatchIndirect) - Execute uma lista de comando por um ou mais grupos de discussão.
/// Você chamar este método para executar comandos em um (Compute Shader).
/// </summary>
/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que deve ser carregado com os dados que corresponde à lista de argumento para ICarenD3D11DeviceContext::Dispatch.</param>
/// <param name="Param_AlinhamentoBytesOffsetForArgs">Um deslocamento de byte alinhado entre o início do buffer e os argumentos.</param>
CarenResult CarenD3D11DeviceContext1::DispatchIndirect(
	ICarenD3D11Buffer^ Param_BufferForArgs,
	UInt32 Param_AlinhamentoBytesOffsetForArgs)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Buffer* pBuffer = NULL;

	//Recupera o ponteiro para o buffer
	Resultado = Param_BufferForArgs->RecuperarPonteiro((LPVOID*)&pBuffer);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DispatchIndirect(pBuffer, Param_AlinhamentoBytesOffsetForArgs);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Draw) - Desenhe não-indexados, instância não primitivos.
/// O Draw envia trabalhos para o pipeline de renderização. Os dados de vértice para uma chamada de desenho normalmente vêm de um buffer de vértice que está vinculado ao pipeline. Mesmo sem qualquer buffer 
/// de vértices vinculado ao pipeline, você pode gerar seus próprios dados de vértice em seu sombreador de vértice usando a semântica do valor do sistema SV_VertexID para determinar o vértice atual que o 
/// tempo de execução está processando.
/// </summary>
/// <param name="Param_NumeroVertices">Número de vértices para desenhar.</param>
/// <param name="Param_LocalizacaoVertice">Índice do primeiro vértice, que é geralmente um deslocamento em um buffer de vértice.</param>
CarenResult CarenD3D11DeviceContext1::Draw(
	UInt32 Param_NumeroVertices,
	UInt32 Param_LocalizacaoVertice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Draw(Param_NumeroVertices, Param_LocalizacaoVertice);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawAuto) - Desenhe a geometria de um tamanho desconhecido.
/// Uma API de desenho envia trabalho para o pipeline de renderização. Esta API submete o trabalho de um tamanho desconhecido que foi processado pelos estágios montador de entrada, sombreador de vértice e 
/// fluxo-saída; o trabalho pode ou não ter passado pelo estágio de sombreamento de geometria.
/// </summary>
CarenResult CarenD3D11DeviceContext1::DrawAuto()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawAuto();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawIndexed) - Sorteio indexado, não-instanced primitivos.
/// Se a soma dos dois índices é negativa, o resultado da chamada de função é indefinido.
/// </summary>
/// <param name="Param_NumeroIndices">Número de índices para desenhar.</param>
/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
CarenResult CarenD3D11DeviceContext1::DrawIndexed(
	UInt32 Param_NumeroIndices,
	UInt32 Param_StartIndexLocalizacao,
	Int32 Param_BaseVerticeLocalizacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawIndexed(Param_NumeroIndices, Param_StartIndexLocalizacao, Param_BaseVerticeLocalizacao);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawIndexedInstanced) - Desenhe indexados, instanciados primitivos.
/// </summary>
/// <param name="Param_QuantidadeIndicesPorInstnacia">Número de índices de ler o buffer de índice para cada instância.</param>
/// <param name="Param_QuantidadeInstnacias">Número de instâncias para desenhar.</param>
/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>
CarenResult CarenD3D11DeviceContext1::DrawIndexedInstanced(
	UInt32 Param_QuantidadeIndicesPorInstnacia,
	UInt32 Param_QuantidadeInstnacias,
	UInt32 Param_StartIndexLocalizacao,
	Int32 Param_BaseVerticeLocalizacao,
	UInt32 Param_StartInstanciaLocalizacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawIndexedInstanced(Param_QuantidadeIndicesPorInstnacia, Param_QuantidadeInstnacias, Param_StartIndexLocalizacao, Param_BaseVerticeLocalizacao, Param_StartInstanciaLocalizacao);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawIndexedInstancedIndirect) - Desenhe primitivos indexados, instanciado, gerado pelo GPU.
/// </summary>
/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
/// <param name="Param_AlinhamentoBytesOffsetForArgs">Deslocamento em Param_BufferForArgs para o início da GPU gerado primitivos.</param>
CarenResult CarenD3D11DeviceContext1::DrawIndexedInstancedIndirect(
	ICarenD3D11Buffer^ Param_BufferForArgs,
	UInt32 Param_AlinhamentoBytesOffsetForArgs)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Buffer* pBuffer = NULL;

	//Recupera o ponteiro para o buffer
	Resultado = Param_BufferForArgs->RecuperarPonteiro((LPVOID*)&pBuffer);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawIndexedInstancedIndirect(pBuffer, Param_AlinhamentoBytesOffsetForArgs);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawInstanced) - Desenhe não-indexados, instanciado primitivos.
/// Instância pode prolongar o desempenho, reutilizando a mesma geometria para desenhar vários objetos em uma cena. Um exemplo de criação de instância pode ser desenhar o mesmo objeto com posições 
/// diferentes e cores.
/// </summary>
/// <param name="Param_QuantidadeVerticiesPorInstnacia">Número de vértices para desenhar.</param>
/// <param name="Param_QuantidadeInstnacias">Número de instâncias para desenhar.</param>
/// <param name="Param_StartVerticeLocalizacao">Índice do primeiro vértice.</param>
/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>			
CarenResult CarenD3D11DeviceContext1::DrawInstanced(
	UInt32 Param_QuantidadeVerticiesPorInstnacia,
	UInt32 Param_QuantidadeInstnacias,
	UInt32 Param_StartVerticeLocalizacao,
	UInt32 Param_StartInstanciaLocalizacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawInstanced(Param_QuantidadeVerticiesPorInstnacia, Param_QuantidadeInstnacias, Param_StartVerticeLocalizacao, Param_StartInstanciaLocalizacao);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DrawInstancedIndirect) - Desenhe primitivos instanciado, gerado pelo GPU.
/// </summary>
/// <param name="Param_BufferDadosPrimitivos">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
/// <param name="Param_DeslocamentoDados">Deslocamento em (Param_BufferDadosPrimitivos) para o início da GPU gerado primitivos.</param>
CarenResult CarenD3D11DeviceContext1::DrawInstancedIndirect(
	ICarenD3D11Buffer^% Param_BufferDadosPrimitivos,
	UInt32 Param_DeslocamentoDados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Buffer* pBuffer = NULL;

	//Recupera o ponteiro para o buffer
	Resultado = Param_BufferDadosPrimitivos->RecuperarPonteiro((LPVOID*)&pBuffer);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawIndexedInstancedIndirect(pBuffer, Param_DeslocamentoDados);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSGetConstantBuffers) - Obtém os buffers constantes usados por fase de domínio-shader.
/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
CarenResult CarenD3D11DeviceContext1::DSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSGetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSGetSamplers) - Obtém uma variedade de interfaces de estado amostrador desde a fase de domínio-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_Amostradores">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizAmostradoresEstado">Uma matriz para as interfaces com amostradores de estado.</param>
CarenResult CarenD3D11DeviceContext1::DSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_Amostradores,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_Amostradores));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSGetSamplers(Param_StartSlot, Param_Amostradores, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizAmostradoresEstado = gcnew cli::array<ICarenD3D11SamplerState^>(Param_Amostradores);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_Amostradores; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizAmostradoresEstado[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizAmostradoresEstado[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSGetShader) - Se o sombreador de domínio atualmente definido no dispositivo.
/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
/// </summary>
/// <param name="Param_Out_SombreadorDominio">Retorna a interface para o sombreador de dominio.</param>
/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz que contém interface de instâncias de classe.</param>
/// <param name="Param_Out_ElementosMatriz">Retorna a quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::DSGetShader(
	[Out] ICarenD3D11DomainShader^% Param_Out_SombreadorDominio,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
	[Out] UInt32% Param_Out_ElementosMatriz)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11DomainShader* pDomainShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSGetShader(&pDomainShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pDomainShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_SombreadorDominio = gcnew CarenD3D11DomainShader();

		//Define o ponteiro de trabalho
		Param_Out_SombreadorDominio->AdicionarPonteiro(pDomainShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pDomainShader) ? CarenResult(ResultCode::SS_OK, true): CarenResult(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_MatrizInstanciasClasse = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInstanciasClasse[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInstanciasClasse[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens no array.
	Param_Out_ElementosMatriz = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSGetShaderResources) - Obter os recursos de domínio-shader. 
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_QuantidadeRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador a ser retornado pelo dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::DSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_QuantidadeRecursos,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizRecursoShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSGetShaderResources(Param_StartSlot, Param_QuantidadeRecursos, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizRecursoShader = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_QuantidadeRecursos);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizRecursoShader[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizRecursoShader[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSSetConstantBuffers) - Define os constantes buffers usados pela fase de domínio-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::DSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de domínio-shader.
/// </summary>
/// <param name="Param_StartSlot">Indice na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_Amostradores">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces amostrador-estado a ser dado ao dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::DSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_Amostradores,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_Amostradores));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_Amostradores; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizAmostradoresEstado[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSSetSamplers(Param_StartSlot, Param_Amostradores, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSSetShader) - Defina um sombreador de domínio para o dispositivo.
/// </summary>
/// <param name="Param_SombreadorDominio">Ponteiro para um sombreador de domínio. Passando NULO desabilita o sombreador para este estágio de pipeline.</param>
/// <param name="Param_MatrizInstanciasClasse">Um ponteiro para uma matriz de instância da classe interfaces. Cada interface usada por um sombreador deve ter uma instância de 
/// classe correspondente ou o shader vai ser desativado. Definir Param_MatrizInstanciasClasse para NULO se o sombreador não usa quaisquer interfaces.</param>
/// <param name="Param_ElementosMatriz">A quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::DSSetShader(
	ICarenD3D11DomainShader^ Param_SombreadorDominio,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciasClasse,
	UInt32 Param_ElementosMatriz)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11DomainShader* pDomainShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_ElementosMatriz > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_ElementosMatriz));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_ElementosMatriz; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizInstanciasClasse[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador se ele tiver sido fornecido.
	if (ObjetoGerenciadoValido(Param_SombreadorDominio))
	{
		//Recupera o ponteiro para a interface.
		Param_SombreadorDominio->RecuperarPonteiro((LPVOID*)&pDomainShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSSetShader(pDomainShader ? pDomainShader : NULL, Param_ElementosMatriz > 0 ? VectorInterfaces.data() : NULL, Param_ElementosMatriz);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (DSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de domínio-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_QuantidadeRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::DSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_QuantidadeRecursos,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizRecursoShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_QuantidadeRecursos));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizRecursoShader[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DSSetShaderResources(Param_StartSlot, Param_QuantidadeRecursos, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (End) - Marca o fim de uma série de comandos.
/// Use ICarenD3D11DeviceContext::Begin para marcar o início de uma série de comandos.
/// </summary>
/// <param name="Param_Async">Um ponteiro para uma interface de ID3D11Asynchronous .</param>
CarenResult CarenD3D11DeviceContext1::End(ICarenD3D11Asynchronous^ Param_Async)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Asynchronous* pAsync = NULL;

	//Obtém o ponteiro
	Resultado = Param_Async->RecuperarPonteiro((LPVOID*)&pAsync);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->End(pAsync);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ExecuteCommandList) - Comandos de filas de uma lista de comandos para um dispositivo.
/// </summary>
/// <param name="Param_FilaComandos">Um ponteiro para uma interface ID3D11CommandList que encapsula uma lista de comandos graficos.</param>
/// <param name="Param_RestaurarEstadoContexto">Um sinalizador booleano que determina se o estado do contexto de destino é salvo antes e restaurado após a execução de uma lista de comandos. Use TRUE para indicar que o tempo de 
/// execução precisa salvar e restaurar o estado. Use FALSE para indicar que nenhum estado deve ser salvo ou restaurado, o que faz com que o contexto de destino retorne ao seu estado padrão após a 
/// execução da lista de comandos. Normalmente, os aplicativos devem usar FALSE, a menos que restaurem o estado para ser quase equivalente ao estado que o tempo de execução restauraria se TRUE fosse 
/// passado. Quando os aplicativos usam FALSE , eles podem evitar transições de estado desnecessárias e ineficientes.</param>
CarenResult CarenD3D11DeviceContext1::ExecuteCommandList(
	ICarenD3D11CommandList^ Param_FilaComandos,
	Boolean Param_RestaurarEstadoContexto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11CommandList* pCommandList = NULL;

	//Obtém o ponteiro
	Resultado = Param_FilaComandos->RecuperarPonteiro((LPVOID*)&pCommandList);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ExecuteCommandList(pCommandList, Param_RestaurarEstadoContexto ? TRUE : FALSE);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (FinishCommandList) - Crie um comando lista e registro gráficos comandos nele.
/// </summary>
/// <param name="Param_RestDeferidoEstadoContexto">Um sinalizador booleano que determina se o tempo de execução salva o estado de contexto adiado antes de executar FinishCommandList e restaurá-lo posteriormente. 
/// Use TRUE para indicar que o tempo de execução precisa salvar e restaurar o estado. Use FALSE para indicar que o tempo de execução não salvará nem restaurará nenhum estado. Nesse caso, o contexto deferido 
/// retornará ao seu estado padrão após a conclusão desta chamada. Para obter informações sobre o estado padrão, consulte ICarenD3D11DeviceContext::ClearState. Normalmente, use FALSE, a menos que você restaure 
/// o estado para ser quase equivalente ao estado que o tempo de execução restauraria se você passasse por TRUE . Quando você usa FALSE, você pode evitar transições de estado desnecessárias e ineficientes.</param>
/// <param name="Param_Out_FilaComandos">Retorna um ponteiro da interface ICarenD3D11CommandList que é inicializado com as informações da lista de comandos gravados. O objeto ICarenD3D11CommandList 
/// resultante é imutável e só pode ser usado com ICarenD3D11DeviceContext::ExecutarListaComandos.</param>
CarenResult CarenD3D11DeviceContext1::FinishCommandList(
	Boolean Param_RestDeferidoEstadoContexto,
	[Out] ICarenD3D11CommandList^% Param_Out_FilaComandos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11CommandList* pCommandList = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FinishCommandList(Param_RestDeferidoEstadoContexto ? TRUE : FALSE, &pCommandList);

	//Verifica se o ponteiro para o objeto é valido
	if (ObjetoValido(pCommandList))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou..

		//Define erro.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_FilaComandos = gcnew CarenD3D11CommandList();

	//Define o ponteiro de trabalho
	Param_Out_FilaComandos->AdicionarPonteiro(pCommandList);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Flush) - Envia comandos de cima enfileirado no buffer de comandos para a unidade de processamento gráfico (GPU).
/// </summary>
CarenResult CarenD3D11DeviceContext1::Flush()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Flush();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GenerateMips) - Gera mipmaps para o recurso de sombreador determinado.
/// </summary>
/// <param name="Param_RecursoSombreador">Um ponteiro para uma interface ICarenD3D11ShaderResourceView que representa o recurso de sombreador.</param>
CarenResult CarenD3D11DeviceContext1::GenerateMips(ICarenD3D11ShaderResourceView^ Param_RecursoSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas
	ID3D11ShaderResourceView* pRecursoView = NULL;

	//Obtém o ponteiro
	Resultado = Param_RecursoSombreador->RecuperarPonteiro((LPVOID*)&pRecursoView);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GenerateMips(pRecursoView);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetContextFlags) - Obtém os sinalizadores de inicialização associados com o atual contexto diferido.
/// </summary>
/// <param name="Param_Out_ContextFlags">recebe as bandeiras que foram fornecidos à ContextFlags parâmetro de ICarenD3D11Device::CreateDeferredContext; no entanto, o sinalizador de contexto é reservado para 
/// uso futuro.</param>
CarenResult CarenD3D11DeviceContext1::GetContextFlags([Out] UInt32% Param_Out_ContextFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_Out_ContextFlags = PonteiroTrabalho->GetContextFlags();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetData) - Obter dados a partir da unidade de processamento gráfico (GPU) de forma assíncrona.
/// </summary>
/// <param name="Param_Async">Um ponteiro para uma interface ICarenD3D11Asynchronous para o objeto sobre o qual (GetData) recupera dados.</param>
/// <param name="Param_Dados">Ponteiro para uma interface de buffer que receberá os dados. Se NULO, (GetData) será usado apenas para verificar o estado. O tipo de saída de dados depende do tipo de interface assíncrona.</param>
/// <param name="Param_TamanhoDados">Tamanho dos dados a serem recuperados ou 0. Deve ser 0 quando (Param_Dados) for NULO.</param>
/// <param name="Param_FlagsGetData">Bandeiras opcionais. Pode ser 0 ou qualquer combinação das bandeiras enumeradas por CA_D3D11_ASYNC_GETDATA_FLAG.</param>
CarenResult CarenD3D11DeviceContext1::GetData(
	ICarenD3D11Asynchronous^ Param_Async,
	ICarenBuffer^% Param_Dados,
	UInt32 Param_TamanhoDados,
	Enumeracoes::CA_D3D11_ASYNC_GETDATA_FLAG Param_FlagsGetData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Asynchronous* pAsync = NULL;
	UINT FlagsGetData = static_cast<UINT>(Param_FlagsGetData);
	IntPtr PonteiroDados = IntPtr::Zero;
	void* pData = NULL;

	//Obtém o ponteiro para a matriz que vai conter os dados.
	Resultado = Param_Async->RecuperarPonteiro((LPVOID*)&pAsync);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Verifica se forneceu um ponteiro que receberá os dados.
	if (ObjetoGerenciadoValido(Param_Dados))
	{
		//Forneceu.

		//Recuper ao ponteiro para a memoria que vai conter os dados.
		Param_Dados->GetInternalPointer(PonteiroDados); 
		
		//Define os dados no ponteiro.
		pData = PonteiroDados.ToPointer();
	}
	else
	{
		//Não forneceu um ponteiro.
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetData(pAsync, pData ? pData : NULL, Param_TamanhoDados, FlagsGetData);

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
/// (GetPredication) - Obtém o estado do predicado de renderização.
/// </summary>
/// <param name="Param_Out_Predicado">Recebe um ponteiro para um predicado. O valor armazenado aqui será NULO na criação do dispositivo.</param> 
/// <param name="Param_Out_ValuePredicado">Recebe um valor booleano para preencher o valor de comparação de predicado. FALSE na criação do dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::GetPredication(
	[Out] ICarenD3D11Predicate^% Param_Out_Predicado,
	[Out] Boolean% Param_Out_ValuePredicado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Predicate* pPredicate = NULL;
	BOOL ValuePredicado = FALSE;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetPredication(&pPredicate, &ValuePredicado);

	//Verifica se o ponteiro retornado é valido e define na interface.
	//Se não for valido, isso não vai representar um erro, porque ele pode retornar NULO na criação.
	if (ObjetoValido(pPredicate))
	{
		//Cria a interface que vai ser retornada.
		Param_Out_Predicado = gcnew CarenD3D11Predicate();

		//Define o ponteiro de trabalho
		Param_Out_Predicado->AdicionarPonteiro(pPredicate);
	}

	//Define o value
	Param_Out_ValuePredicado = ValuePredicado ? TRUE : FALSE;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetResourceMinLOD) - Obtém o mínimo nível-de-detalhe (LOD).
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para uma interface que representa um recurso.</param> 
/// <param name="Param_Out_LODMinimo">Retorna o LOD minímo.</param> 
CarenResult CarenD3D11DeviceContext1::GetResourceMinLOD(ICarenD3D11Resource^ Param_Recurso, [Out] float% Param_Out_LODMinimo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecurso = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Param_Out_LODMinimo = PonteiroTrabalho->GetResourceMinLOD(pRecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetType) - Obtém o tipo de contexto de dispositivo.
/// </summary>
/// <param name="Param_Out_ContextoDispositivo">Retorna as opções de contexto do dispositivo.</param> 
CarenResult CarenD3D11DeviceContext1::GetType([Out] Enumeracoes::CA_D3D11_DEVICE_CONTEXT_TYPE% Param_Out_ContextoDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_Out_ContextoDispositivo = static_cast<CA_D3D11_DEVICE_CONTEXT_TYPE>(PonteiroTrabalho->GetType());

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSGetConstantBuffers) - Se os buffers constantes usados pela fase geometria shader pipeline.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
CarenResult CarenD3D11DeviceContext1::GSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSGetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de gasoduto de sombreamento de geometria.
/// </summary>
/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
CarenResult CarenD3D11DeviceContext1::GSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSGetSamplers(Param_StartSlot, Param_NumeroAmostradores, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizEstadoAmostrado = gcnew cli::array<ICarenD3D11SamplerState^>(Param_NumeroAmostradores);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizEstadoAmostrado[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizEstadoAmostrado[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSGetShader) - Obtém o sombreador de geometria atualmente definido no dispositivo.
/// </summary>
/// <param name="Param_Out_SombreadorGeometria">Retorna uma interface para o sombreador de Geometria.</param>
/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::GSGetShader(
	[Out] ICarenD3D11GeometryShader^% Param_Out_SombreadorGeometria,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
	[Out] UInt32% Param_Out_QuantidadeInstancias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11GeometryShader* pGeometryShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSGetShader(&pGeometryShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pGeometryShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_SombreadorGeometria = gcnew CarenD3D11GeometryShader();

		//Define o ponteiro de trabalho
		Param_Out_SombreadorGeometria->AdicionarPonteiro(pGeometryShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pGeometryShader) ? CarenResult(ResultCode::SS_OK, true): CarenResult(ResultCode::ER_FAIL, true);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_MatrizInstanciasClasse = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInstanciasClasse[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInstanciasClasse[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens no array.
	Param_Out_QuantidadeInstancias = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSGetShaderResources) - Obtém os recursos de geometria obscuros.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::GSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSGetShaderResources(Param_StartSlot, Param_NumeroViews, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizVisualizadoresSombreador = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_NumeroViews);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizVisualizadoresSombreador[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizVisualizadoresSombreador[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSSetConstantBuffers) - Define os constantes buffers usados pela fase geometria shader pipeline.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
CarenResult CarenD3D11DeviceContext1::GSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline de sombreador geometria.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
CarenResult CarenD3D11DeviceContext1::GSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizAmostradoresEstado[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSSetSamplers(Param_StartSlot, Param_NumeroAmostradores, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSSetShader) - Defina um sombreador de geometria para o dispositivo.
/// </summary>
/// <param name="Param_SombreadorGeometria">Ponteiro para um sombreador de vértice. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
CarenResult CarenD3D11DeviceContext1::GSSetShader(
	ICarenD3D11GeometryShader^ Param_SombreadorGeometria,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
	UInt32 Param_NumeroInstanciasClasse)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11GeometryShader* pGeometryShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_NumeroInstanciasClasse > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroInstanciasClasse));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_NumeroInstanciasClasse; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizInstanciaClasse[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador de geometria se tiver sido fornecido
	if (ObjetoGerenciadoValido(Param_SombreadorGeometria))
	{
		//Recupera o ponteiro para a interface.
		Param_SombreadorGeometria->RecuperarPonteiro((LPVOID*)&pGeometryShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSSetShader(pGeometryShader ? pGeometryShader : NULL, Param_NumeroInstanciasClasse > 0 ? VectorInterfaces.data() : NULL, Param_NumeroInstanciasClasse);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreamento de geometria.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
CarenResult CarenD3D11DeviceContext1::GSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroViews));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Recupera o ponteiro para a interface.
		Param_MatrizVisualizadoresSombreador[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GSSetShaderResources(Param_StartSlot, Param_NumeroViews, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSGetConstantBuffers) - Se os buffers constantes usados pela fase casco-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
CarenResult CarenD3D11DeviceContext1::HSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSGetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de casco-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
CarenResult CarenD3D11DeviceContext1::HSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSGetSamplers(Param_StartSlot, Param_NumeroAmostradores, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizEstadoAmostrado = gcnew cli::array<ICarenD3D11SamplerState^>(Param_NumeroAmostradores);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizEstadoAmostrado[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizEstadoAmostrado[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSGetShader) - Obtém o Sombreador de Casco atualmente definido no dispositivo.
/// </summary>
/// <param name="Param_Out_SombreadorCasco">Retorna uma interface para o Sombreador de Casco.</param>
/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::HSGetShader(
	[Out] ICarenD3D11HullShader^% Param_Out_SombreadorCasco,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
	[Out] UInt32% Param_Out_QuantidadeInstancias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11HullShader* pHullShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSGetShader(&pHullShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pHullShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_SombreadorCasco = gcnew CarenD3D11HullShader();

		//Define o ponteiro de trabalho
		Param_Out_SombreadorCasco->AdicionarPonteiro(pHullShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pHullShader) ? CarenResult(ResultCode::SS_OK, true): CarenResult(ResultCode::ER_FAIL, true);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_MatrizInstanciasClasse = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInstanciasClasse[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInstanciasClasse[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens no array.
	Param_Out_QuantidadeInstancias = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSGetShaderResources) - Obtém os recursos do sombreador de casco(Hull).
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::HSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSGetShaderResources(Param_StartSlot, Param_NumeroViews, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizVisualizadoresSombreador = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_NumeroViews);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizVisualizadoresSombreador[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizVisualizadoresSombreador[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSSetConstantBuffers) - Defina os constantes buffers usados pelo palco casco-shader.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
CarenResult CarenD3D11DeviceContext1::HSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de sombreamento de casco(Hull).
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
CarenResult CarenD3D11DeviceContext1::HSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizAmostradoresEstado[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSSetSamplers(Param_StartSlot, Param_NumeroAmostradores, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSSetShader) - Defina um sombreador de casco para o dispositivo.
/// </summary>
/// <param name="Param_SombreadorCasco">Ponteiro para um Sombreador de Casco(Hull). Passar em NULO desativa o shader para este estágio de pipeline.</param>  
/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
CarenResult CarenD3D11DeviceContext1::HSSetShader(
	ICarenD3D11HullShader^ Param_SombreadorCasco,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
	UInt32 Param_NumeroInstanciasClasse)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11HullShader* pHullShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_NumeroInstanciasClasse > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroInstanciasClasse));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_NumeroInstanciasClasse; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizInstanciaClasse[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador de geometria se tiver sido fornecido
	if (ObjetoGerenciadoValido(Param_SombreadorCasco))
	{
		//Recupera o ponteiro para a interface.
		Param_SombreadorCasco->RecuperarPonteiro((LPVOID*)&pHullShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSSetShader(pHullShader ? pHullShader : NULL, Param_NumeroInstanciasClasse > 0 ? VectorInterfaces.data() : NULL, Param_NumeroInstanciasClasse);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (HSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de casco-shader.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
CarenResult CarenD3D11DeviceContext1::HSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroViews));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Recupera o ponteiro para a interface.
		Param_MatrizVisualizadoresSombreador[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->HSSetShaderResources(Param_StartSlot, Param_NumeroViews, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IAGetIndexBuffer) - Obtém um ponteiro para o buffer de índice que é vinculado à fase de entrada-montador.
/// </summary>
/// <param name="Param_Out_Buffer">Retorna um ponteiro para o buffer.</param>
/// <param name="Param_Out_Formato">Retorna uma especificação do formato dos dados no buffer de índice. Esses formatos oferecem o tamanho e o tipo de dados no buffer. Os formatos só permitidos para dados 
/// de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
/// <param name="Param_Out_Deslocamento">Retorna o Deslocamento(Offset) (em bytes) desde o início do buffer de índice, o primeiro índice para usar.</param>
CarenResult CarenD3D11DeviceContext1::IAGetIndexBuffer(
	[Out] ICarenD3D11Buffer^% Param_Out_Buffer,
	[Out] Enumeracoes::CA_DXGI_FORMAT% Param_Out_Formato,
	[Out] UInt32% Param_Out_Deslocamento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Buffer* pBuffer = NULL;
	DXGI_FORMAT FormatoDadosBuffer;
	UINT DeslocamentoBuffer = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IAGetIndexBuffer(&pBuffer, &FormatoDadosBuffer, &DeslocamentoBuffer);

	//Verifica se o buffer é valido
	if (ObjetoValido(pBuffer))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.

		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o buffer.
	Param_Out_Buffer = gcnew CarenD3D11Buffer();

	//Define o ponteiro de trabalho
	Param_Out_Buffer->AdicionarPonteiro(pBuffer);

	//Define o parametro de formato
	Param_Out_Formato = static_cast<CA_DXGI_FORMAT>(FormatoDadosBuffer);

	//Define o deslocamento do buffer.
	Param_Out_Deslocamento = DeslocamentoBuffer;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IAGetInputLayout) - Obter um ponteiro para o objeto de entrada-layout que está vinculado para o estágio de entrada-montador.
/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
/// necessários para vitar vazamentos de memória.
/// </summary>
/// <param name="Param_Out_InputLayout">Reretorna um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
CarenResult CarenD3D11DeviceContext1::IAGetInputLayout([Out] ICarenD3D11InputLayout^% Param_Out_InputLayout)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11InputLayout* pInputLayout = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IAGetInputLayout(&pInputLayout);

	//Verifica se a interface é valida.
	if (ObjetoValido(pInputLayout))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.

		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o buffer.
	Param_Out_InputLayout = gcnew CarenD3D11InputLayout();

	//Define o ponteiro de trabalho
	Param_Out_InputLayout->AdicionarPonteiro(pInputLayout);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IAGetPrimitiveTopology) - Obter informações sobre o tipo primitivo e a ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
/// </summary>
/// <param name="Param_Out_TipoPrimitivo"></param>
CarenResult CarenD3D11DeviceContext1::IAGetPrimitiveTopology([Out] Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY% Param_Out_TipoPrimitivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	D3D11_PRIMITIVE_TOPOLOGY PrimiteTopology;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IAGetPrimitiveTopology(&PrimiteTopology);

	//Define no parametro de saida.
	Param_Out_TipoPrimitivo = static_cast<CA_D3D11_PRIMITIVE_TOPOLOGY>(PrimiteTopology);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IAGetVertexBuffers) - Se os buffers de vértice ligados para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_StartSlot">O slot de entrada do primeiro buffer vértice para chegar. O primeiro buffer de vértice é explicitamente vinculado ao slot de início; Isso faz com que cada buffer de 
/// vértice adicional na matriz para ser implicitamente ligado a cada slot de entrada subsequente. O máximo de 16 ou 32 slots de entrada (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) 
/// estão disponíveis; o número máximo de slots de entrada depende do nível de recurso.</param>
/// <param name="Param_NumeroBuffers">O número de buffers de vértice para obter começando em deslocamento. O número de buffers (mais o slot de partida) não pode exceder o número total de slots de entrada IA-estágio.</param>
/// <param name="Param_Out_MatrizVertexBuffers">Retorna uma matriz de buffers de vertex.</param>
/// <param name="Param_Out_MatrizStrides">Retorna uma matriz de valores de (Stride) retornado pelo método; um (Stride) valor para cada buffer na matriz de buffer de vértice. Cada valor de stride é o tamanho (em bytes) 
/// dos elementos que devem ser usados desse buffer de vértice.</param>
/// <param name="Param_Out_MatrizDeslocamentos">uma matriz de valores de deslocamento retornado pelo método; um valor para cada buffer na matriz de buffer de vértice de deslocamento. Cada deslocamento é o 
/// número de bytes entre o primeiro elemento de um buffer de vértice e o primeiro elemento que será usado.</param>
CarenResult CarenD3D11DeviceContext1::IAGetVertexBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizVertexBuffers,
	[Out] cli::array<UInt32>^% Param_Out_MatrizStrides,
	[Out] cli::array<UInt32>^% Param_Out_MatrizDeslocamentos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaceBuffer;
	UINT* pMatrizStrides = new UINT[Param_NumeroBuffers];
	UINT* pMatrizDeslocamentos = new UINT[Param_NumeroBuffers];

	//Reserva a quantidade de ponteiros no vetor.
	VectorInterfaceBuffer.reserve(Param_NumeroBuffers);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IAGetVertexBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaceBuffer.data(), pMatrizStrides, pMatrizDeslocamentos);

	//Verifica se o vetor com os ponteiros é valido.
	if (!VectorInterfaceBuffer.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou..

		//Define falha na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai retornar as interfaces ponteiros.
	Param_Out_MatrizVertexBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Cria e define os ponteiros do buffer em cada id no array.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface do buffer no id especificado.
		Param_Out_MatrizVertexBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro para o buffer no id.
		Param_Out_MatrizVertexBuffers[i]->AdicionarPonteiro(VectorInterfaceBuffer[i]);
	}

	//Cria as matrizes de tipo simples.
	Param_Out_MatrizStrides = gcnew cli::array<UInt32>(Param_NumeroBuffers);
	Param_Out_MatrizDeslocamentos = gcnew cli::array<UInt32>(Param_NumeroBuffers);

	//Copia os dados das matrizes simples.
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizStrides, pMatrizStrides, Param_NumeroBuffers);
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizDeslocamentos, pMatrizDeslocamentos, Param_NumeroBuffers);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para as matrizes
	delete[] pMatrizStrides;
	delete[] pMatrizDeslocamentos;

	//Limpa o vetor.
	VectorInterfaceBuffer.clear();
	VectorInterfaceBuffer.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IASetIndexBuffer) - Vincule um buffer do índice para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_Buffer">Um ponteiro para um objeto ICarenD3D11Buffer, que contém os índices. O buffer do índice deve ter sido criado com o sinalizador D3D11_BIND_INDEX_BUFFER .</param>
/// <param name="Param_Formato">Um CA_D3D11_DXGI_FORMAT que especifica o formato dos dados no buffer de índice. Os formatos só permitidos para dados de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
/// <param name="Param_Deslocamento">Offset (em bytes) do início do buffer de índice para o primeiro índice para usar.</param>
CarenResult CarenD3D11DeviceContext1::IASetIndexBuffer(
	ICarenD3D11Buffer^ Param_Buffer,
	Enumeracoes::CA_DXGI_FORMAT Param_Formato,
	UInt32 Param_Deslocamento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Buffer* pBuffer = NULL;
	DXGI_FORMAT FormatoBuffer = static_cast<DXGI_FORMAT>(Param_Formato);

	//Obtém o ponteiro para a interface.
	Resultado = Param_Buffer->RecuperarPonteiro((LPVOID*)&pBuffer);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IASetIndexBuffer(pBuffer, FormatoBuffer, Param_Deslocamento);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IASetInputLayout) - Vincule um objeto de layout de entrada para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_InputLayout">Um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
CarenResult CarenD3D11DeviceContext1::IASetInputLayout(ICarenD3D11InputLayout^ Param_InputLayout)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11InputLayout* pInputLayout = NULL;

	//Obtém o ponteiro para a interface.
	Resultado = Param_InputLayout->RecuperarPonteiro((LPVOID*)&pInputLayout);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IASetInputLayout(pInputLayout);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IASetPrimitiveTopology) - Vincule informações sobre o tipo primitivo e ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
/// </summary>
/// <param name="Param_TipoPrimitivo">O tipo de primitivo e ordenação dos dados primitivos.</param>
CarenResult CarenD3D11DeviceContext1::IASetPrimitiveTopology(Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY Param_TipoPrimitivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopo = static_cast<D3D11_PRIMITIVE_TOPOLOGY>(Param_TipoPrimitivo);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IASetPrimitiveTopology(PrimitiveTopo);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IASetVertexBuffers) - Liga a uma matriz de buffers de vértice para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_StartSlot">O primeiro slot de entrada para ligação. O primeiro buffer de vértice é explicitamente vinculado ao slot de início; Isso faz com que cada buffer de vértice adicional na 
/// matriz para ser implicitamente ligado a cada slot de entrada subsequente. O máximo de 16 ou 32 slots de entrada (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) estão disponíveis; o número
/// máximo de slots de entrada depende do nível de recurso.</param>
/// <param name="Param_NumeroBuffers">O número de buffers de vértice na matriz. O número de buffers (mais o slot de partida) não pode exceder o número total de slots de entrada IA-estágio 
/// (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizVertexBuffers">Uma matriz de buffers de vértice. Os buffers de vértice devem ter sido criados com o sinalizador D3D11_BIND_VERTEX_BUFFER .</param>
/// <param name="Param_MatrizStrides">Uma matriz de valores de stride; um passo valor para cada buffer na matriz de buffer de vértice. Cada passo é o tamanho (em bytes) dos elementos que devem ser 
/// usados desse buffer de vértice.</param>
/// <param name="Param_MatrizDeslocamentos">uma matriz de valores de deslocamento; um valor para cada buffer na matriz de buffer de vértice de deslocamento. Cada deslocamento é o número de bytes entre o 
/// primeiro elemento de um buffer de vértice e o primeiro elemento que será usado.</param>
CarenResult CarenD3D11DeviceContext1::IASetVertexBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizVertexBuffers,
	cli::array<UInt32>^ Param_MatrizStrides,
	cli::array<UInt32>^ Param_MatrizDeslocamentos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11Buffer*> VectorInterfaceBuffer;
	UINT* pMatrizStrides = new UINT[Param_NumeroBuffers];
	UINT* pMatrizDeslocamentos = new UINT[Param_NumeroBuffers];
	ID3D11Buffer* pBuffer = NULL;

	//Reserva a quantidade de ponteiros no vetor.
	VectorInterfaceBuffer.reserve(Param_NumeroBuffers);

	//Copia os dados do array gerenciado para o vetor nativo.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizVertexBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuffer);

		//Define o ponteiro no vetor.
		VectorInterfaceBuffer.push_back(pBuffer);

		//Limpa
		pBuffer = NULL;
	}

	//Copia os dados para as matrizes simples.
	Util.CopiarItensTo_ArrayNativo(&pMatrizStrides, Param_MatrizStrides, Param_NumeroBuffers);
	Util.CopiarItensTo_ArrayNativo(&pMatrizDeslocamentos, Param_MatrizDeslocamentos, Param_NumeroBuffers);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IASetVertexBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaceBuffer.data(), pMatrizStrides, pMatrizDeslocamentos);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Libera a memoria para as matrizes
	delete[] pMatrizStrides;
	delete[] pMatrizDeslocamentos;

	//Limpa o vetor.
	VectorInterfaceBuffer.clear();
	VectorInterfaceBuffer.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Map) - Obtém um ponteiro para os dados contidos em um sub-recurso e nega o acesso GPU para aquele sub-recurso.
/// Esse método também retorna DXGI_ERROR_WAS_STILL_DRAWING se MapFlags especifica D3D11_MAP_FLAG_DO_NOT_WAIT e a GPU ainda não está terminado com o recurso.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para uma interface de ID3D11Resource .</param>
/// <param name="Param_IndiceSubRecurso">O Indice para o sub-recruso.</param>
/// <param name="Param_PermissõesAcessoRecurso">Um D3D11_MAP valor digitado que especifica a CPU ler e escrever permissões para um recurso.</param>
/// <param name="Param_MapFlags">Sinalizador que especifica que a CPU faz quando a GPU está ocupado. Este sinalizador é opcional. Define como (CA_D3D11_MAP_FLAG::Zero) para deixar como opcional.</param>
/// <param name="Param_Out_RecrusoMapeado">Uma estrutura de CA_D3D11_MAPPED_SUBRESOURCE para o sub-recurso mapeado. Essa estrutura pode ser NULA as vezes. Consulte a documentação.</param>
CarenResult CarenD3D11DeviceContext1::Map(
	ICarenD3D11Resource^ Param_Recurso,
	UInt32 Param_IndiceSubRecurso,
	Enumeracoes::CA_D3D11_MAP Param_PermissõesAcessoRecurso,
	Enumeracoes::CA_D3D11_MAP_FLAG Param_MapFlags,
	[Out] Estruturas::CA_D3D11_MAPPED_SUBRESOURCE^% Param_Out_RecrusoMapeado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_MAP PermissaoAcesso = static_cast<D3D11_MAP>(Param_PermissõesAcessoRecurso);
	UINT Flags = static_cast<UINT>(Param_PermissõesAcessoRecurso);
	D3D11_MAPPED_SUBRESOURCE* pEstruturaData = NULL;

	//Obtém o ponteiro para a interface.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Map(pRecurso, Param_IndiceSubRecurso, PermissaoAcesso, Flags, pEstruturaData);

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

	//Verifica se a estrutura é valida.
	//De acordo com a documentação, ela pode retornar NULL se tiver sido criada com D3D11_USAGE_DEFAULT e ter sido chamado de um contexto imediato.
	if (ObjetoValido(pEstruturaData))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Não vai ser setado como erro.
		//Só vai vai criar uma estrutura valida para retornar ao usuario.

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Sai do método
		Sair;
	}

	//Converte a interface nativa para a gerenciada e define no parametro.
	//Parametro 'gcnew CarenBuffer()' é utilizado para armazenar o ponteiro de dados que a estrutura nativa pede.
	Param_Out_RecrusoMapeado = Util.ConverterD3D11_MAPPED_SUBRESOURCEUnManaged_ToManaged(pEstruturaData, gcnew CarenBuffer());

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMGetBlendState) - Obtém o estado de mistura da fase de saída-fusão.
/// </summary>
/// <param name="Param_Out_EstadoMitura">Retorna um ponteiro para a interface de estado de mistura.</param>
/// <param name="Param_Out_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA.</param>
/// <param name="Param_Out_SampleMask">Retorna um valor para uma máscara de amostra.</param>
CarenResult CarenD3D11DeviceContext1::OMGetBlendState(
	[Out] ICarenD3D11BlendState^% Param_Out_EstadoMitura,
	[Out] cli::array<float>^% Param_Out_MatrizFatoresMistura,
	[Out] UInt32% Param_Out_SampleMask)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11BlendState* pBlendState = NULL;
	FLOAT* pMatrizMisturaRGBA = new FLOAT[4]; //4 é um valor fixo.
	UINT SampleMask = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMGetBlendState(&pBlendState, pMatrizMisturaRGBA, &SampleMask);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pBlendState))
	{
		//Cria a interface que vai conter o ponteiro da interface a ser retornada.
		Param_Out_EstadoMitura = gcnew CarenD3D11BlendState();

		//Define o ponteiro de trabalho
		Param_Out_EstadoMitura->AdicionarPonteiro(pBlendState);
	}

	//Cria a matriz de mistura de fatores
	Param_Out_MatrizFatoresMistura = gcnew cli::array<float>(4); //4 é um valor fixo (RGBA)

	//Copia os dados dos componentes RGBA na matriz nativa para a gerenciada.
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_MatrizFatoresMistura, pMatrizMisturaRGBA, 4);

	//Define a Sample Mask
	Param_Out_SampleMask = SampleMask;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, false);

	//Libera a memoria para a matriz de float.
	delete[] pMatrizMisturaRGBA;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMGetDepthStencilState) - Obtém o estado de profundidade-estêncil da fase de saída-fusão.
/// </summary>
/// <param name="Param_Out_DepthStencilState">Retorna um ponteiro para interface de estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
/// <param name="Param_Out_StencilRef">Retorna um valor para um estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::OMGetDepthStencilState(
	[Out] ICarenD3D11DepthStencilState^% Param_Out_DepthStencilState,
	[Out] UInt32% Param_Out_StencilRef)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DepthStencilState* pStencilState = NULL;
	UINT StencilRef = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMGetDepthStencilState(&pStencilState, &StencilRef);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pStencilState))
	{
		//Cria a interface que vai conter o ponteiro da interface a ser retornada.
		Param_Out_DepthStencilState = gcnew CarenD3D11DepthStencilState();

		//Define o ponteiro de trabalho
		Param_Out_DepthStencilState->AdicionarPonteiro(pStencilState);
	}

	//Define o Ref do Stencil
	Param_Out_StencilRef = StencilRef;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMGetRenderTargets) - Obter ponteiros para os recursos vinculados para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_NumeroViews">Número de destinos de processamento para recuperar.</param>
/// <param name="Param_IgnorarRecuperaçãoDestino">Defina (TRUE) para esse parâmetro quando a recuperação de um destino de processamento não é necessária.
/// O parametro (Param_Out_MatrizRenderTargetViews) retorna NULO se esse valor for verdadeiro.</param>
/// <param name="Param_Out_MatrizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam processar exibições de alvo.</param>
/// <param name="Param_IgnorarRecuperaçãoModoExibição">Defina (TRUE) para esse parâmetro quando a recuperação do modo de exibição de profundidade-estêncil não é necessária.
/// O parametro (Param_Out_DepthStencilView) retorna NULO se esse valor for verdadeiro.</param>
/// <param name="Param_Out_DepthStencilView">Ponteiro para um ID3D11DepthStencilView, que representa uma visão de profundidade-estêncil.</param>
CarenResult CarenD3D11DeviceContext1::OMGetRenderTargets(
	UInt32 Param_NumeroViews,
	Boolean Param_IgnorarRecuperaçãoDestino,
	[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTargetViews,
	Boolean Param_IgnorarRecuperaçãoModoExibição,
	[Out] ICarenD3D11DepthStencilView^% Param_Out_DepthStencilView)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11RenderTargetView*> VectorInterfacesTargetView; //Pode ser vazio.
	ID3D11DepthStencilView* pStencilView = NULL; //Pode ser NULO.

	//Reserva o vetor se os destinos de processamento forem necessários
	if (!Param_IgnorarRecuperaçãoDestino)
	{
		//Reserva a quantidade de ponteiro que vai conter no vetor.
		VectorInterfacesTargetView.reserve(Param_NumeroViews);
	}
	else
	{
		//Deve ignorar a recuperação de destino.

	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMGetRenderTargets(Param_NumeroViews, Param_IgnorarRecuperaçãoDestino ? NULL : VectorInterfacesTargetView.data(), Param_IgnorarRecuperaçãoModoExibição ? NULL : &pStencilView);

	//Verifica quais os dados seram retornados
	if (!Param_IgnorarRecuperaçãoDestino)
	{
		//O usuário deseja obter a matriz com as interfaces de destino.
		Param_Out_MatrizRenderTargetViews = gcnew cli::array<ICarenD3D11RenderTargetView^>(Param_NumeroViews);

		//Faz um for para criar e adicionar o ponteiro de trabalho
		for (UINT i = 0; i < Param_NumeroViews; i++)
		{
			//Cria a interface no id especificado.
			Param_Out_MatrizRenderTargetViews[i] = gcnew CarenD3D11RenderTargetView();

			//Define o ponteiro de trabalho na interface.
			Param_Out_MatrizRenderTargetViews[i]->AdicionarPonteiro(VectorInterfacesTargetView[i]);
		}
	}
	if (!Param_IgnorarRecuperaçãoModoExibição)
	{
		//Cria a interface a ser retornada
		Param_Out_DepthStencilView = gcnew CarenD3D11DepthStencilView();

		//Define o ponteiro de trabalho
		Param_Out_DepthStencilView->AdicionarPonteiro(pStencilView);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Libera o vetor.
	VectorInterfacesTargetView.clear();
	VectorInterfacesTargetView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMGetRenderTargetsAndUnorderedAccessViews) - Obter ponteiros para os recursos vinculados para o estágio de saída-fusão.
/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
/// necessários para vitar vazamentos de memória.
/// </summary>
/// <param name="Param_NumeroRTVs">O número de pontos de vista de renderização-destino para recuperar.</param>
/// <param name="Param_IgnorarRenderTargetView">Defina (TRUE) para esse parâmetro quando a recuperação de pontos de vista de destino de processamento não é necessária.
/// O parametro (Param_Out_MatrizRenderTarget) retorna NULO se esse valor for verdadeiro.</param>
/// <param name="Param_Out_MatrizRenderTarget">Retorna uma matriz de ID3D11RenderTargetViews, que representam vistas de destino de processamento.</param>
/// <param name="Param_Out_DepthStencilView">Defina (TRUE) para esse parâmetro quando a recuperação do modo de exibição de profundidade-estêncil não é necessária.
/// O parametro (Param_DepthStencilView) retorna NULO se esse valor for verdadeiro.</param>
/// <param name="Param_Out_DepthStencilView">Retorna um ponteiro para um ICarenD3D11DepthStencilView, que representa uma visão de profundidade-estêncil.</param>
/// <param name="Param_UAVStartSlot">Indice em uma matriz baseada em zero para começar a recuperar acesso não ordenada visualizações (varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - 1). 
/// Para sombreamentos de pixel (Param_UAVStartSlot) deve ser igual ao número de pontos de vista de destino de processamento que estão vinculados.</param>
/// <param name="Param_NumeroUAVs">Número de pontos de vista de acesso não-ordenados para retornar no ppUnorderedAccessViews. Este número varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - Param_UAVStartSlot.</param>
/// <param name="Param_IgnorarUnorderedAccessView">Defina (TRUE) para esse parâmetro quando a recuperação de pontos de vista de acesso não-ordenados não é necessária.
///  O parametro (Param_Out_MatrizUnorderedAccessViews) retorna NULO se esse valor for verdadeiro.</param>
/// <param name="Param_Out_MatrizUnorderedAccessViews">Retorna uma matriz de ICarenD3D11UnorderedAccessViews, que representam vistas de acesso não ordenada que são recuperadas.</param>
CarenResult CarenD3D11DeviceContext1::OMGetRenderTargetsAndUnorderedAccessViews(
	UInt32 Param_NumeroRTVs,
	Boolean Param_IgnorarRenderTargetView,
	[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTarget,
	Boolean Param_IgnorarDepthStencilView,
	[Out] ICarenD3D11DepthStencilView^ Param_Out_DepthStencilView,
	UInt32  Param_UAVStartSlot,
	UInt32  Param_NumeroUAVs,
	Boolean Param_IgnorarUnorderedAccessView,
	[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizUnorderedAccessViews)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);


	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11RenderTargetView*> VectorInterfacesTargetView; //Pode ser vazio.
	ID3D11DepthStencilView* pStencilView = NULL; //Pode ser NULO.
	std::vector <ID3D11UnorderedAccessView*> VectorInterfacesUnorderedView; //Pode ser vazio.

	//Reserva a quantidade de ponteiro para cada vetor se ele não for ignorado.
	if (!Param_IgnorarRenderTargetView)
	{
		//Reserva a quantidade de ponteiro que vai conter no vetor.
		VectorInterfacesTargetView.reserve(Param_NumeroRTVs);
	}
	else
	{
		//Deve ignorar a recuperação de destino.

	}
	if (!Param_IgnorarUnorderedAccessView)
	{
		//Reserva a quantidade de ponteiro que vai conter no vetor.
		VectorInterfacesUnorderedView.reserve(Param_NumeroUAVs);
	}
	else
	{
		//Deve ignorar a recuperação de destino.

	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMGetRenderTargetsAndUnorderedAccessViews(
		Param_NumeroRTVs,
		Param_IgnorarRenderTargetView ? NULL : VectorInterfacesTargetView.data(),
		Param_IgnorarDepthStencilView ? NULL : &pStencilView,
		Param_UAVStartSlot,
		Param_NumeroUAVs,
		Param_IgnorarUnorderedAccessView ? NULL : VectorInterfacesUnorderedView.data()
	);

	//Verifica quais os dados seram retornados
	if (!Param_IgnorarRenderTargetView)
	{
		//O usuário deseja obter a matriz com as interfaces de destino.
		Param_Out_MatrizRenderTarget = gcnew cli::array<ICarenD3D11RenderTargetView^>(Param_NumeroRTVs);

		//Faz um for para criar e adicionar o ponteiro de trabalho
		for (UINT i = 0; i < Param_NumeroRTVs; i++)
		{
			//Cria a interface no id especificado.
			Param_Out_MatrizRenderTarget[i] = gcnew CarenD3D11RenderTargetView();

			//Define o ponteiro de trabalho na interface.
			Param_Out_MatrizRenderTarget[i]->AdicionarPonteiro(VectorInterfacesTargetView[i]);
		}
	}
	if (!Param_IgnorarDepthStencilView)
	{
		//Cria a interface a ser retornada
		Param_Out_DepthStencilView = gcnew CarenD3D11DepthStencilView();

		//Define o ponteiro de trabalho
		Param_Out_DepthStencilView->AdicionarPonteiro(pStencilView);
	}
	if (!Param_IgnorarUnorderedAccessView)
	{
		//O usuário deseja obter a matriz com as interfaces de destino.
		Param_Out_MatrizUnorderedAccessViews = gcnew  cli::array<ICarenD3D11UnorderedAccessView^>(Param_NumeroUAVs);

		//Faz um for para criar e adicionar o ponteiro de trabalho
		for (UINT i = 0; i < Param_NumeroUAVs; i++)
		{
			//Cria a interface no id especificado.
			Param_Out_MatrizUnorderedAccessViews[i] = gcnew CarenD3D11UnorderedAccessView();

			//Define o ponteiro de trabalho na interface.
			Param_Out_MatrizUnorderedAccessViews[i]->AdicionarPonteiro(VectorInterfacesUnorderedView[i]);
		}
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Libera os vetores.
	VectorInterfacesTargetView.clear();
	VectorInterfacesTargetView.shrink_to_fit();
	VectorInterfacesUnorderedView.clear();
	VectorInterfacesUnorderedView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMSetBlendState) - Defina o estado de mistura da fase de saída-fusão.
/// Para criar uma interface de mistura-estado, chamade o método ICarenD3D11Device::CreateBlendState.
/// </summary>
/// <param name="Param_EstadoMitura">Ponteiro para um estado de mistura interface. Passe nulo para um estado de mistura padrão.</param>
/// <param name="Param_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA. Os fatores de mistura modulate valores para o shader de pixel, processar o alvo, ou ambos. Se você 
/// tiver criado o objeto de mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, a fase de mistura usa a matriz não-nulos de mistura fatores. Se você não criar o objeto de 
/// mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, fase de mesclagem não usa a matriz não-nulos de misturam fatores; o tempo de execução armazena os mistura de fatores, 
/// e mais tarde pode chamar ICarenD3D11DeviceContext::OMGetBlendState para recuperar os fatores de mistura. Se você transmitir NULO, o tempo de execução usa ou armazena um fator de mistura igual 
/// a {1, 1, 1, 1}.</param>
/// <param name="Param_SampleMask">cobertura de amostra de 32 bits. O valor padrão é 0xffffffff. Uma máscara de amostra determina quais amostras atualizadas em todos os destinos de processamento ativo. 
/// O mapeamento de bits em uma máscara de amostra para amostras em um destino processar multisample é da responsabilidade de um aplicativo individual. Sempre é aplicada uma máscara de amostra; 
/// é independente de se multisampling é habilitado e não depende de se um aplicativo usa multisample render destinos.</param>
CarenResult CarenD3D11DeviceContext1::OMSetBlendState(
	ICarenD3D11BlendState^ Param_EstadoMitura,
	cli::array<float>^ Param_MatrizFatoresMistura,
	UInt32 Param_SampleMask)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11BlendState* pBlendState = NULL; //Pode ser NULO.
	FLOAT* pFatoresMistura = NULL;

	//Verifica se forneceu o blend
	if (ObjetoGerenciadoValido(Param_EstadoMitura))
	{
		//Recupera o ponteiro para a interface.
		Resultado = Param_EstadoMitura->RecuperarPonteiro((LPVOID*)&pBlendState);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou..

			//Sai do método
			Sair;
		}
	}
	//Verifica se forneceu uma matriz de fatores de mistura
	if (ObjetoGerenciadoValido(Param_MatrizFatoresMistura))
	{
		//Inicializa a matriz.
		pFatoresMistura = new FLOAT[4];	 //4 é um valor Fixo(RGBA).

		//Copia os dados.
		Util.CopiarItensTo_ArrayNativo(&pFatoresMistura, Param_MatrizFatoresMistura, 4);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMSetBlendState(pBlendState ? NULL : pBlendState, pFatoresMistura ? pFatoresMistura : NULL, Param_SampleMask);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a matriz se ela for valida
	if (ObjetoValido(pFatoresMistura))
	{
		//Libera a memoria para a matriz.
		delete[] pFatoresMistura;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMSetDepthStencilState) - Define o estado de profundidade-estêncil da fase de saída-fusão.
/// [Atenção] -> O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
/// </summary>
/// <param name="Param_DepthStencilState">Ponteiro para um estado de profundidade-estêncil interface para ligar o dispositivo. Defina NULO para usar o estado padrão listado em D3D11_DEPTH_STENCIL_DESC.</param>
/// <param name="Param_StencilRef">Valor de referência para executar contra ao fazer um teste de profundidade-estêncil.</param>
CarenResult CarenD3D11DeviceContext1::OMSetDepthStencilState(
	ICarenD3D11DepthStencilState^ Param_DepthStencilState,
	UInt32 Param_StencilRef)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11DepthStencilState* pDepthStencil = NULL; //Pode ser NULO.

	//Verifica se forneceu um ponteiro para o stencil e recupera
	if (ObjetoGerenciadoValido(Param_DepthStencilState))
	{
		//Recupera o ponteiro para a interface.
		Resultado = Param_DepthStencilState->RecuperarPonteiro((LPVOID*)&pDepthStencil);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou..

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMSetDepthStencilState(pDepthStencil ? pDepthStencil : NULL, Param_StencilRef);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMSetRenderTargets) - Ligar um ou mais destinos de processamento atomicamente e a profundidade-estêncil buffer para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_NumeroViews">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas 
/// na matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro.</param>
/// <param name="Param_MatizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumViews é 0, não render destinos são vinculados.</param>
/// <param name="Param_DepthStencilView">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
CarenResult CarenD3D11DeviceContext1::OMSetRenderTargets(
	UInt32 Param_NumeroViews,
	cli::array<ICarenD3D11RenderTargetView^>^ Param_MatizRenderTargetViews,
	ICarenD3D11DepthStencilView^ Param_DepthStencilView)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11DepthStencilView* pDepthStencilView = NULL;
	std::vector<ID3D11RenderTargetView*> ppMatrizRendersDestino;
	LPVOID pPointer = NULL;

	//Define o tamanho do vetor.
	ppMatrizRendersDestino.reserve(Param_NumeroViews);

	//Verifica se forneceu uma matriz de renders de destino
	if (ObjetoGerenciadoValido(Param_MatizRenderTargetViews))
	{
		//Define os dados
		for (UINT i = 0; i < Param_NumeroViews; i++)
		{
			//Recupera o ponteiro.
			Param_MatizRenderTargetViews[i]->RecuperarPonteiro((LPVOID*)&pPointer);

			//Adiciona no vetor.
			ppMatrizRendersDestino.push_back((ID3D11RenderTargetView*)pPointer);

			//Limpa
			pPointer = NULL;
		}
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMSetRenderTargets(Param_NumeroViews, ObjetoGerenciadoValido(Param_MatizRenderTargetViews) ? ppMatrizRendersDestino.data() : NULL, pDepthStencilView ? pDepthStencilView : NULL);

	//Limpa o vetor.
	ppMatrizRendersDestino.clear();
	ppMatrizRendersDestino.shrink_to_fit();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OMSetRenderTargetsAndUnorderedAccessViews) - Vincula recursos para a fase de saída-fusão.
/// Para sombreamentos de pixel, os destinos de processamento e acesso não-ordenados vistas compartilhar os slots de recurso mesmo quando sendo escritos para fora. Isto significa que UAVs devem ser dado 
/// um deslocamento, para que eles são colocados nos slots após as vistas de destino de render que estão sendo vinculadas.
/// Nota:  CSC, DSV e UAVs não podem ser definidos de forma independente; todos eles precisam ser definidas ao mesmo tempo.
/// </summary>
/// <param name="Param_NumeroRTVs">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas na 
/// matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro. Se você definir NumRTVs para D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL (0xffffffff), esse método não modifica as 
/// vistas atualmente ligados render-alvo (CSC) e também não modifica vista profundidade-estêncil (DSV).</param>
/// <param name="Param_MatrizRenderTargetViews">Uma matriz de s de ID3D11RenderTargetViewque representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumRTVs 
/// é 0, não render destinos são vinculados.</param>
/// <param name="Param_DepthStencil">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. 
/// Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
/// <param name="Param_UAVStartSlot">Índice em uma matriz baseada em zero para começar a definir vistas não ordenada-acesso (varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - 1).Para o runtime Direct3D 11.1, 
/// que está disponível iniciando com o Windows 8, esse valor pode variar de 0 a D3D11_1_UAV_SLOT_COUNT - 1. D3D11_1_UAV_SLOT_COUNT é definido como 64. Para sombreamentos de pixel, Param_UAVStartSlot deve ser 
/// igual ao número de pontos de vista de renderização - destino sendo ligado.</param>
/// <param name="Param_NumeroUAVs">Número de pontos de vista de acesso não ordenada (UAVs) em Param_MatrizUnorderedAccessViews. Se você definir NumUAVs para D3D11_KEEP_UNORDERED_ACCESS_VIEWS (0xffffffff), 
/// esse método não modifica os pontos de vista não ordenada-acesso atualmente ligados.Para o runtime Direct3D 11.1, que está disponível iniciando com o Windows 8, esse valor pode variar de 0 a 
/// D3D11_1_UAV_SLOT_COUNT - Param_UAVStartSlot.</param>
/// <param name="Param_MatrizUnorderedAccessViews">Uma matriz de s de ICarenD3D11UnorderedAccessViewque representam os pontos de vista de acesso não-ordenados para ligar o dispositivo. Se este parâmetro for 
/// NULO, e Param_NumeroUAVs é 0, não ordenada-acesso opiniões é vinculado.</param>
/// <param name="Param_MatrizUAVInitialCounts">Uma matriz de acrescentar e consumir deslocamentos de reserva. Um valor de -1 indica que para manter o atual deslocamento. Quaisquer outros valores definir o 
/// contador oculto para aquele UAV appendable e consumíveis. Param_MatrizUAVInitialCounts é relevante apenas para UAVs que foram criados com qualquer D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER 
/// especificado quando o UAV foi criado; caso contrário, o argumento é ignorado.</param>
CarenResult CarenD3D11DeviceContext1::OMSetRenderTargetsAndUnorderedAccessViews(
	UInt32 Param_NumeroRTVs,
	cli::array <ICarenD3D11RenderTargetView^>^ Param_MatrizRenderTargetViews,
	ICarenD3D11DepthStencilView^ Param_DepthStencil,
	UInt32 Param_UAVStartSlot,
	UInt32 Param_NumeroUAVs,
	cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizUnorderedAccessViews,
	cli::array<UInt32>^ Param_MatrizUAVInitialCounts)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<ID3D11RenderTargetView*> VectorInterfacesTargetView; //Pode ser vazio.
	ID3D11RenderTargetView* pRenderTarget = NULL;
	ID3D11DepthStencilView* pStencilView = NULL; //Pode ser NULO.
	std::vector <ID3D11UnorderedAccessView*> VectorInterfacesUnorderedView; //Pode ser vazio.
	ID3D11UnorderedAccessView* pUnorderedView = NULL;
	UINT* pMatrizUAV = NULL; //Pode ser NULO.
	UINT LarguraArrayUVAInitialCount = 0;

	//Verifica se forneceu as interfaces e copia os dados.
	if (ObjetoGerenciadoValido(Param_MatrizRenderTargetViews))
	{
		//Reserva a quantidade de itens para o vetor.
		VectorInterfacesTargetView.reserve(Param_NumeroRTVs);

		//Copia os dados para o vetor.
		for (UINT i = 0; i < Param_NumeroRTVs; i++)
		{
			//Recupera o ponteiro.
			Param_MatrizRenderTargetViews[i]->RecuperarPonteiro((LPVOID*)&pRenderTarget);

			//Define no vetor.
			VectorInterfacesTargetView.push_back(pRenderTarget);

			//Limpa.
			pRenderTarget = NULL;
		}
	}
	if (ObjetoGerenciadoValido(Param_DepthStencil))
	{
		//Recupera o ponteiro para a interface.
		Resultado = Param_DepthStencil->RecuperarPonteiro((LPVOID*)&pStencilView);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou...

			//Sai do método
			Sair;
		}
	}
	if (ObjetoGerenciadoValido(Param_MatrizUnorderedAccessViews))
	{
		//Reserva a quantidade de itens para o vetor.
		VectorInterfacesUnorderedView.reserve(Param_NumeroUAVs);

		//Copia os dados para o vetor.
		for (UINT i = 0; i < Param_NumeroUAVs; i++)
		{
			//Recupera o ponteiro.
			Param_MatrizUnorderedAccessViews[i]->RecuperarPonteiro((LPVOID*)&pUnorderedView);

			//Define no vetor.
			VectorInterfacesUnorderedView.push_back(pUnorderedView);

			//Limpa.
			pUnorderedView = NULL;
		}
	}
	if (ObjetoGerenciadoValido(Param_MatrizUAVInitialCounts))
	{
		//Obtém a largura do array.
		LarguraArrayUVAInitialCount = Param_MatrizUAVInitialCounts->Length;

		//Cria a matriz.
		pMatrizUAV = new UINT[LarguraArrayUVAInitialCount];

		//Copia os dados.
		Util.CopiarItensTo_ArrayNativo(&pMatrizUAV, Param_MatrizUAVInitialCounts, LarguraArrayUVAInitialCount);
	}


	//Chama o método para realizar a operação.
	PonteiroTrabalho->OMSetRenderTargetsAndUnorderedAccessViews(
		Param_NumeroRTVs,
		VectorInterfacesTargetView.empty() ? NULL : VectorInterfacesTargetView.data(),
		pStencilView ? pStencilView : NULL,
		Param_UAVStartSlot,
		Param_NumeroUAVs,
		VectorInterfacesUnorderedView.empty() ? NULL : VectorInterfacesUnorderedView.data(),
		pMatrizUAV ? pMatrizUAV : NULL);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera os vetores.
	VectorInterfacesTargetView.clear();
	VectorInterfacesTargetView.shrink_to_fit();
	VectorInterfacesUnorderedView.clear();
	VectorInterfacesUnorderedView.shrink_to_fit();

	//Libera a memória da matriz se ela for valida.
	if (ObjetoValido(pMatrizUAV))
	{
		//Libera a memoria para a matriz.
		delete[] pMatrizUAV;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSGetConstantBuffers) - Se os buffers constantes usados por fase de gasoduto do sombreador de pixel. 
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
CarenResult CarenD3D11DeviceContext1::PSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSGetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSGetSamplers) - Obtém uma matriz de Estados amostrador desde a fase de gasoduto de sombreador de pixel.
/// </summary>
/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
CarenResult CarenD3D11DeviceContext1::PSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSGetSamplers(Param_StartSlot, Param_NumeroAmostradores, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizEstadoAmostrado = gcnew cli::array<ICarenD3D11SamplerState^>(Param_NumeroAmostradores);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizEstadoAmostrado[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizEstadoAmostrado[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSGetShader) -  Obtém o sombreador de pixel atualmente definido no dispositivo.
/// </summary>
/// <param name="Param_Out_SombreadorPixel">Retorna uma interface para o Sombreador de Pixel.</param>
/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::PSGetShader(
	[Out] ICarenD3D11PixelShader^% Param_Out_SombreadorPixel,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
	[Out] UInt32% Param_Out_QuantidadeInstancias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11PixelShader* pPixelShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSGetShader(&pPixelShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pPixelShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_SombreadorPixel = gcnew CarenD3D11PixelShader();

		//Define o ponteiro de trabalho
		Param_Out_SombreadorPixel->AdicionarPonteiro(pPixelShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pPixelShader) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_MatrizInstanciasClasse = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInstanciasClasse[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInstanciasClasse[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens no array.
	Param_Out_QuantidadeInstancias = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSGetShaderResources) - Obter o pixel sombreador recursos.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::PSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSGetShaderResources(Param_StartSlot, Param_NumeroViews, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizVisualizadoresSombreador = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_NumeroViews);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizVisualizadoresSombreador[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizVisualizadoresSombreador[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSSetConstantBuffers) - Define os constantes buffers usados pela fase de gasoduto do sombreador de pixel.
/// </summary>
/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::PSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSSetSamplers) - Defina uma matriz de Estados amostrador à fase de gasoduto de sombreador de pixel.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
CarenResult CarenD3D11DeviceContext1::PSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizAmostradoresEstado[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSSetSamplers(Param_StartSlot, Param_NumeroAmostradores, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSSetShader) - Define um sombreador de pixel para o dispositivo.
/// </summary>
/// <param name="Param_ShaderPixel">Ponteiro para um Sombreador de Pixel. Passar NULO desativa o shader para este estágio de pipeline.</param>  
/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
CarenResult CarenD3D11DeviceContext1::PSSetShader(
	ICarenD3D11PixelShader^ Param_ShaderPixel,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
	UInt32 Param_NumeroInstanciasClasse)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11PixelShader* pPixelShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_NumeroInstanciasClasse > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroInstanciasClasse));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_NumeroInstanciasClasse; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizInstanciaClasse[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador de Pixel se tiver sido fornecido
	if (ObjetoGerenciadoValido(Param_ShaderPixel))
	{
		//Recupera o ponteiro para a interface.
		Param_ShaderPixel->RecuperarPonteiro((LPVOID*)&pPixelShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSSetShader(pPixelShader ? pPixelShader : NULL, Param_NumeroInstanciasClasse > 0 ? VectorInterfaces.data() : NULL, Param_NumeroInstanciasClasse);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (PSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de pixel.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
CarenResult CarenD3D11DeviceContext1::PSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroViews));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Recupera o ponteiro para a interface.
		Param_MatrizVisualizadoresSombreador[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PSSetShaderResources(Param_StartSlot, Param_NumeroViews, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ResolveSubresource) - Copie um recurso multisampled para um recurso não-multisampled.
/// </summary>
/// <param name="Param_RecursoDestino">Recurso de destino. Deve ser um criado com o sinalizador D3D11_USAGE_DEFAULT e single-amostrados.</param>
/// <param name="Param_IndiceSubRecursoDestino">Um índice baseado em zero, que identifica o sub-recurso de destino. Use D3D11CalcSubresource para calcular o índice.</param>
/// <param name="Param_RecursoOrigem">Fonte de recursos. Deve ser multisampled.</param>
/// <param name="Param_IndiceSubRecursoOrigem">O sub-recurso fonte de fonte de recursos.</param>
/// <param name="Param_DXGIFormato">Um CA_DXGI_FORMAT que indica como o recurso multisampled será resolvido para um recurso único-amostrados.</param>
CarenResult CarenD3D11DeviceContext1::ResolveSubresource(
	ICarenD3D11Resource^ Param_RecursoDestino,
	UInt32 Param_IndiceSubRecursoDestino,
	ICarenD3D11Resource^ Param_RecursoOrigem,
	UInt32 Param_IndiceSubRecursoOrigem,
	Enumeracoes::CA_DXGI_FORMAT Param_DXGIFormato)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecursoDestino = NULL;
	ID3D11Resource* pRecursoOrigem = NULL;
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_DXGIFormato);

	//Obtém os ponteiros para os recursos.
	//Não vai ser verificado se valido ou se obteve com sucesso.
	//Os ponteiros são obrigatorios.
	Param_RecursoDestino->RecuperarPonteiro((LPVOID*)&pRecursoDestino);
	Param_RecursoOrigem->RecuperarPonteiro((LPVOID*)&pRecursoOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ResolveSubresource(pRecursoDestino, Param_IndiceSubRecursoDestino, pRecursoOrigem, Param_IndiceSubRecursoOrigem, FormatoDXGI);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSGetScissorRects) - Obtém a matriz de scissor retângulos vinculado à fase rasterizer.
/// </summary>
/// <param name="Param_Out_NumeroRects">O número de retângulos de tesoura (intervalos entre 0 e D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) ligados; defina Param_ChecarQuantidade para TRUE para usar 
/// Param_Out_NumeroRects para ver quantos retângulos seriam retornados.</param>
/// <param name="Param_ChecarQuantidade">Define como (TRUE) para obter a quantidade de retangulos que seriam retornados. Se esse valor for TRUE, o parametro (Param_Out_Rects) não retorna nada.</param>
/// <param name="Param_Out_Rects">Uma matriz de retângulos scissor. Se Param_NumeroRects for maior que o número de (Scissor Rects) atualmente vinculada, membros não utilizados da matriz conterá 0.</param>
CarenResult CarenD3D11DeviceContext1::RSGetScissorRects(
	[Out] UInt32% Param_Out_NumeroRects,
	Boolean Param_ChecarQuantidade,
	[Out] cli::array<Estruturas::CA_RECT^>^% Param_Out_Rects)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT NumeroRects = Param_Out_NumeroRects; //[IN, OUT]
	std::vector<RECT> VectorRects;

	//Reserva a quantidade de retangulos que vai conter.
	VectorRects.reserve(Param_Out_NumeroRects);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSGetScissorRects(&NumeroRects, Param_ChecarQuantidade ? NULL : VectorRects.data());

	//Verifica se só estava verificando a quantidade.
	//Se sim, só vai retornar a quantidade de rects.
	if (Param_ChecarQuantidade)
	{
		//Define a quantidade de rects.
		Param_Out_NumeroRects = NumeroRects;

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Sai do método
		Sair;
	}
	else
	{
		//Verifica se o vetor não está vazio
		if (!VectorRects.empty())
		{
			//Deixa o método continuar.
		}
		else
		{
			//O vetor está vazio.

			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do metodo
			Sair;
		}
	}

	//Cria o array que vai conter os RECTS a serem retornados.
	Param_Out_Rects = gcnew cli::array<Estruturas::CA_RECT^>(NumeroRects);

	//Faz um for para converter os rects nativos para o gerenciado.
	for (UINT i = 0; i < NumeroRects; i++)
	{
		//Converte o Rect e define no array gerenciado.
		Param_Out_Rects[i] = Util.ConverterRECTUnmanagedToManaged(&VectorRects[i]);
	}

	//Define a quantidade de rects.
	Param_Out_NumeroRects = NumeroRects;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor e os dados.
	VectorRects.clear();
	VectorRects.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSGetState) - Obtém o estado do rasterizador do rasterizador estágio do pipeline.
/// </summary>
/// <param name="Param_Out_EstadoRasterizador">Um ponteiro para um estado de rasterizador interface para preencher com as informações do dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::RSGetState([Out] ICarenD3D11RasterizerState^% Param_Out_EstadoRasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11RasterizerState* pRasterizador = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSGetState(&pRasterizador);

	//Verifica se o objeto é valido
	if (ObjetoValido(pRasterizador))
	{
		//Deixa  o método continuar.
	}
	else
	{
		//O objeto não era valido.

		//Define erro.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que vai retornar a interface.
	Param_Out_EstadoRasterizador = gcnew CarenD3D11RasterizerState();

	//Define o ponteiro de trabalho
	Param_Out_EstadoRasterizador->AdicionarPonteiro(pRasterizador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSGetViewports) - Obtém a matriz de viewports vinculadas à fase rasterizer.
/// </summary>
/// <param name="Param_ObterQuantidadeViewports">Define para (TRUE) para obter o número de viewports atualmente definidas. Se (TRUE), Param_Out_MatrizViewports retorna NULO.</param>
/// <param name="Param_Ref_NumeroViewports">.Na entrada deve definir a quantidade de viewports que seram obtidas. Na saida, ela retorna a quantidade real de viewports retornadas pelo
/// parametro (Param_Out_MatrizViewports).</param>
/// <param name="Param_Out_MatrizViewports">Uma matriz de estruturas CA_D3D11_VIEWPORT para as viewports que estão vinculadas à fase do rasterizador.</param>
CarenResult CarenD3D11DeviceContext1::RSGetViewports(
	Boolean Param_ObterQuantidadeViewports,
	UInt32% Param_Ref_NumeroViewports,
	[Out] cli::array<Estruturas::CA_D3D11_VIEWPORT^>^% Param_Out_MatrizViewports)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT NumeroViewPorts = Param_Ref_NumeroViewports; //[IN, OUT]
	std::vector<D3D11_VIEWPORT> VectorViewPort;

	//Reserva a quantidade de estruturas que o vetor vai conter
	if (!Param_ObterQuantidadeViewports)
	{
		//Reserva a quantidade informada pelo usuário.
		VectorViewPort.reserve(NumeroViewPorts);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSGetViewports(&NumeroViewPorts, Param_ObterQuantidadeViewports ? NULL : VectorViewPort.data());

	//Verifica se o usuário só chamaou para obter a quantidade de viewports
	if (!Param_ObterQuantidadeViewports)
	{
		//Deixa continuar.
	}
	else
	{
		//Estava só obtendo a quantidade de viewports.

		//Define a quantidade no parametro de saida e entrada.
		Param_Ref_NumeroViewports = NumeroViewPorts;

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Sai do método
		Sair;
	}

	//Verifica se o ponteiro não está vazio.
	if (!VectorViewPort.empty())
	{
		//Deixa continuar.
	}
	else
	{
		//O vetor está vazio.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a matriz que vai retornar as viewports.
	Param_Out_MatrizViewports = gcnew cli::array<Estruturas::CA_D3D11_VIEWPORT^>(NumeroViewPorts);

	//Faz um for para converter e definir na matriz.
	for (UINT i = 0; i < NumeroViewPorts; i++)
	{
		//Converter a viewport no id especificado e define na matriz de saida.
		Param_Out_MatrizViewports[i] = Util.ConverterD3D11_VIEWPORTUnManaged_ToManaged(&VectorViewPort[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorViewPort.clear();
	VectorViewPort.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSSetScissorRects) - Vincule uma matriz de retângulos de tesoura para o rasterizador de palco.
/// </summary>
/// <param name="Param_NumeroRects">Número de retângulos de tesoura para ligar.</param>
/// <param name="Param_MatrizRects">Uma matriz de retângulos scissor.</param>
CarenResult CarenD3D11DeviceContext1::RSSetScissorRects(
	UInt32 Param_NumeroRects,
	cli::array<Estruturas::CA_RECT^>^ Param_MatrizRects)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	RECT* pRECTS = CriarMatrizEstruturas<RECT>(Param_NumeroRects);

	//Faz um for para converter a estrutura gerenciada para a nativa.
	for (UINT i = 0; i < Param_NumeroRects; i++)
	{
		//Converte e define na matriz nativa.
		pRECTS[i] = *Util.ConverterRECTManagedToUnmanaged(Param_MatrizRects[i]);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSSetScissorRects(Param_NumeroRects, pRECTS);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Chama o método para liberar a memoria para a matriz de rects
	DeletarMatrizEstruturasSafe(&pRECTS);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSSetState) - Defina o estado do rasterizador para o rasterizador de estágio do pipeline.
/// </summary>
/// <param name="Param_EstadoRasterizador">Ponteiro para uma interface de estado rasterizador para vincular ao pipeline.</param>
CarenResult CarenD3D11DeviceContext1::RSSetState(ICarenD3D11RasterizerState^ Param_EstadoRasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11RasterizerState* pRasterizador = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = Param_EstadoRasterizador->RecuperarPonteiro((LPVOID*)&pRasterizador);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSSetState(pRasterizador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RSSetViewports) - Ligar a uma matriz de viewports para o rasterizador de estágio do pipeline.
/// </summary>
/// <param name="Param_NumeroViewports">Número de viewports para vincular.</param>
/// <param name="Param_MatrizViewports">Uma matriz de estruturas D3D11_VIEWPORT para vincular ao dispositivo. Consulte a página de estrutura para obter detalhes sobre como o tamanho da viewport depende do nível de recurso do dispositivo que foi alterado 
/// entre o Direct3D 11 e o Direct3D 10.</param>
CarenResult CarenD3D11DeviceContext1::RSSetViewports(
	UInt32 Param_NumeroViewports,
	cli::array<Estruturas::CA_D3D11_VIEWPORT^>^ Param_MatrizViewports)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_VIEWPORT* pArrayViewPorts = CriarMatrizEstruturas<D3D11_VIEWPORT>(Param_NumeroViewports);

	//Covnerte as ViewPorts gerenciadas
	for (UINT i = 0; i < Param_NumeroViewports; i++)
	{
		//Converte e define no array.
		pArrayViewPorts[i] = *Util.ConverterD3D11_VIEWPORTManaged_ToUnManaged(Param_MatrizViewports[i]);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RSSetViewports(Param_NumeroViewports, pArrayViewPorts);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Libera a memoria para a estrutura
	DeletarMatrizEstruturasSafe(&pArrayViewPorts);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPredication) - Defina um predicado de renderização.
/// </summary>
/// <param name="Param_Predicate">Um ponteiro para a interface ICarenD3D11Predicate que representa o predicado de renderização. Um valor NULO indica predicação "não"; Nesse caso, o valor de 
/// (Param_ValorPredicado) é irrelevante, mas será preservado para ICarenD3D11DeviceContext::GetPredication.</param>
/// <param name="Param_ValorPredicado">Se TRUE, a renderização será afetada quando as condições do predicado forem cumpridas. Se FALSE, a renderização será afetada quando as condições não forem atendidas.</param>
CarenResult CarenD3D11DeviceContext1::SetPredication(
	ICarenD3D11Predicate^ Param_Predicate,
	Boolean Param_ValorPredicado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Predicate* pPredicado = NULL; //Pode ser nulo.

	//Verifica se forneceu um ponteiro para o predicado
	if (ObjetoGerenciadoValido(Param_Predicate))
	{
		//Recupera o ponteiro para o predicado
		Resultado = Param_Predicate->RecuperarPonteiro((LPVOID*)&pPredicado);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou...

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetPredication(pPredicado ? pPredicado : NULL, Param_ValorPredicado ? TRUE : FALSE);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetResourceMinLOD) - Define o mínimo nível-de-detalhe (LOD) para um recurso.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para um ID3D11Resource que representa o recurso.</param>
/// <param name="Param_MinLOD">O nível de detalhamento, que varia entre 0 e o número máximo de níveis de mipmap do recurso. Por exemplo, o número máximo de níveis mipmap de uma textura 1D é especificado na 
/// MipLevels membro do D3D11_TEXTURE1D_DESC estrutura.</param>
CarenResult CarenD3D11DeviceContext1::SetResourceMinLOD(
	ICarenD3D11Resource^ Param_Recurso,
	float Param_MinLOD)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecurso = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetResourceMinLOD(pRecurso, Param_MinLOD);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SOGetTargets) - Se os buffers de saída de destino para o fluxo de saída estágio do pipeline.
/// </summary>
/// <param name="Param_NumeroBuffers">O número de Buffers a serem obtidos.</param>
/// <param name="Param_Out_MatrizBuffers">Recebe a matriz com os buffers de saida retornado do dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::SOGetTargets(
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VectorBuffers;

	//Reserva a quantidad de interfaces que vai conter no vetor
	VectorBuffers.reserve(Param_NumeroBuffers);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SOGetTargets(Param_NumeroBuffers, VectorBuffers.data());

	//Verifica se o vetor contém dados
	if (!VectorBuffers.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou..

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método 
		Sair;
	}

	//Cria a matriz que vai conter as interfaces.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os ponteiros
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro(VectorBuffers[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VectorBuffers.clear();
	VectorBuffers.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SOSetTargets) - Defina os buffers de saída de destino para o fluxo de saída estágio do pipeline.
/// </summary>
/// <param name="Param_NumeroBuffers">O número de buffer para ligar ao dispositivo. Um máximo de quatro buffers de saída pode ser definido. Se menos de quatro forem definidos pela chamada, 
/// os slots de buffer restantes serão definidos como NULO.</param>
/// <param name="Param_MatrizBuffers">A matriz de buffers de saída para ligar ao dispositivo. Os buffers devem ter sido criados com o sinalizador D3D11_BIND_STREAM_OUTPUT.</param>  
/// <param name="Param_DeslocamentosBuffers">Matriz de deslocamentos para os buffers de saída de (Param_MatrizBuffers), um deslocamento para cada buffer. Os valores de deslocamento devem estar 
/// em bytes.</param>
CarenResult CarenD3D11DeviceContext1::SOSetTargets(
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
	cli::array<UInt32>^ Param_DeslocamentosBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VectorMatrizBuffer;
	UINT* pDeslocamentos = new UINT[Param_NumeroBuffers];
	ID3D11Buffer* pBuff = NULL;

	//Faz um for para obter as interfaces e os deslocamentos.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Preenche o vetor.

		//Recupera o ponteiro para a interface.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define no vetor
		VectorMatrizBuffer.push_back(pBuff);

		//Limpa
		pBuff = NULL;


		//Preenche a matriz de deslocamentos.

		//Define o deslocamento no id
		pDeslocamentos[i] = Param_DeslocamentosBuffers[i];
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SOSetTargets(Param_NumeroBuffers, VectorMatrizBuffer.data(), pDeslocamentos);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorMatrizBuffer.clear();
	VectorMatrizBuffer.shrink_to_fit();

	//Libera a memoria da matriz.
	delete[] pDeslocamentos;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (unmap) - Invalida o ponteiro para um recurso e reabilita o acesso da GPU para esse recurso.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para o recurso a ser invalido.</param>
/// <param name="Param_SubrecursoInvalidado">O Id do subrecurso a ser (Desmapeado).</param>
CarenResult CarenD3D11DeviceContext1::Unmap(
	ICarenD3D11Resource^ Param_Recurso,
	UInt32 Param_SubrecursoInvalidado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecurso = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Unmap(pRecurso, Param_SubrecursoInvalidado);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UpdateSubresource) -  A CPU copia dados da memória para um sub-recurso criado na memória não-mapeável.
/// </summary>
/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_SubrecursoDestino">Um índice baseado em zero, que identifica o sub-destino do destino.</param>
/// <param name="Param_Caixa">Uma caixa que define a parte do sub-destino de destino para copiar os dados do recurso. Coordenadas são em bytes para buffers e em texels para texturas. Se NULO, os dados são
/// gravados no subfonte de destino sem nenhum deslocamento. As dimensões da fonte devem caber no destino</param>
/// <param name="Param_DadosOrigemMemoria">Um ponteiro para os dados de origem na memória.</param>
/// <param name="Param_TamanhoLinhaOrigem">(SrcRowPitch) - O tamanho de uma linha dos dados de origem.</param>
/// <param name="Param_TamhoFatiaProdundidade">(SrcDepthPitch) - O tamanho de uma fatia de profundidade dos dados de origem.</param>
CarenResult CarenD3D11DeviceContext1::UpdateSubresource(
	ICarenD3D11Resource^ Param_RecursoDestino,
	UInt32 Param_SubrecursoDestino,
	Estruturas::CA_D3D11_BOX^ Param_Caixa,
	ICarenBuffer^ Param_DadosOrigemMemoria,
	UInt32 Param_TamanhoLinhaOrigem,
	UInt32 Param_TamhoFatiaProdundidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecursoDestino = NULL;
	D3D11_BOX* pBOX = NULL; //Pode ser NULO.
	PVOID pDadosOrigem = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;

	//Recupera o ponteiro para a interface de recurso.
	Resultado = Param_RecursoDestino->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Converte a caixa do d3d11 se valida
	if (ObjetoGerenciadoValido(Param_Caixa))
	{
		//Converte a caixa gerenciada para a nativa.
		pBOX = Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_Caixa);
	}

	//Recupera o ponteiros para os dados de origem.
	Param_DadosOrigemMemoria->GetInternalPointer(PonteiroDados); 
	
	//Define o ponteiro dos dados.
	pDadosOrigem = PonteiroDados.ToPointer();

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UpdateSubresource(pRecursoDestino, Param_SubrecursoDestino, pBOX ? pBOX : NULL, pDadosOrigem, Param_TamanhoLinhaOrigem, Param_TamhoFatiaProdundidade);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Deleta a estrutura se ela for valida
	DeletarEstruturaSafe(&pBOX);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSGetConstantBuffers) - Se os buffers constantes usados pela fase vértice shader pipeline.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
CarenResult CarenD3D11DeviceContext1::VSGetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroBuffers));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSGetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizBuffers = gcnew cli::array<ICarenD3D11Buffer^>(Param_NumeroBuffers);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizBuffers[i] = gcnew CarenD3D11Buffer();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizBuffers[i]->AdicionarPonteiro((LPVOID*)&VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSGetSamplers) - Obter uma matriz de Estados amostrador desde a fase de gasoduto de shader de vértice.
/// </summary>
/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
CarenResult CarenD3D11DeviceContext1::VSGetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VetorDataInterface;
	bool VetorVazio = FALSE;

	//Define a quantidade de itens que o vetor vai conter.
	VetorDataInterface.reserve(static_cast<size_t>(Param_NumeroAmostradores));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSGetSamplers(Param_StartSlot, Param_NumeroAmostradores, VetorDataInterface.data());

	//Verifica se o Vetor está vazio
	VetorVazio = VetorDataInterface.empty();

	//Verifica o resultado
	if (!VetorVazio)
	{
		//Deixa o método continuar.
	}
	else
	{
		//O vetor está vazio.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai conter o ponteiros.
	Param_Out_MatrizEstadoAmostrado = gcnew cli::array<ICarenD3D11SamplerState^>(Param_NumeroAmostradores);

	//Faz um for para criar e definir os dados.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizEstadoAmostrado[i] = gcnew CarenD3D11SamplerState();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizEstadoAmostrado[i]->AdicionarPonteiro(VetorDataInterface[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorDataInterface.clear();
	VetorDataInterface.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSGetShader) - Obtém o vértice shader atualmente definido no dispositivo.
/// </summary>
/// <param name="Param_Out_SombreadorVertice">Retorna uma interface para o sombreador de vertice.</param>
/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
CarenResult CarenD3D11DeviceContext1::VSGetShader(
	[Out] ICarenD3D11VertexShader^% Param_Out_SombreadorVertice,
	[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
	[Out] UInt32% Param_Out_QuantidadeInstancias)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);


	//Variaveis a serem utilizadas.
	ID3D11VertexShader* pVertexShader = NULL;
	vector<ID3D11ClassInstance*> VetorInterfaces;
	UINT CountInterfacesInArray = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSGetShader(&pVertexShader, VetorInterfaces.data(), &CountInterfacesInArray);

	//Verifica se interface do Shader Computer é valida
	if (ObjetoValido(pVertexShader))
	{
		//Cria a interface que será retornada no parametro.
		Param_Out_SombreadorVertice = gcnew CarenD3D11VertexShader();

		//Define o ponteiro de trabalho
		Param_Out_SombreadorVertice->AdicionarPonteiro(pVertexShader);
	}

	//Verifica se o foi retornado algum item para o vetor.
	if (CountInterfacesInArray > 0)
	{
		//Deixa  continuar.
	}
	else
	{
		//Nenhuma interface foi retornada para o vetor.

		//Define o resultado com base na interface de computação do shader.
		Resultado = ObjetoValido(pVertexShader) ? CarenResult(ResultCode::SS_OK , true): CarenResult(ResultCode::ER_FAIL , false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai ser retornado.
	Param_Out_MatrizInstanciasClasse = gcnew cli::array<ICarenD3D11ClassInstance^>(CountInterfacesInArray);

	//Copia os dados para o array
	for (UINT i = 0; i < CountInterfacesInArray; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizInstanciasClasse[i] = gcnew CarenD3D11ClassInstance();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizInstanciasClasse[i]->AdicionarPonteiro(VetorInterfaces[i]);
	}

	//Define a quantidade de itens no array.
	Param_Out_QuantidadeInstancias = CountInterfacesInArray;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa o vetor
	VetorInterfaces.clear();
	VetorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSGetShaderResources) - Obter o vértice shader recursos.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::VSGetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<ID3D11ShaderResourceView*> VectorResourceView;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSGetShaderResources(Param_StartSlot, Param_NumeroViews, VectorResourceView.data());

	//Verifica se obteve alguma interface.
	if (!VectorResourceView.empty())
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Nenhuma interface foi retornada.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai
		Sair;
	}

	//Cria a matriz a ser retornada ao usuário.
	Param_Out_MatrizVisualizadoresSombreador = gcnew cli::array<ICarenD3D11ShaderResourceView^>(Param_NumeroViews);

	//faz um for para criar cada interface e definir o ponteiro de trabalho.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Cria a interface no id especificado.
		Param_Out_MatrizVisualizadoresSombreador[i] = gcnew CarenD3D11ShaderResourceView();

		//Define o ponteiro de trabalho.
		Param_Out_MatrizVisualizadoresSombreador[i]->AdicionarPonteiro(VectorResourceView[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera o vetor.
	VectorResourceView.clear();
	VectorResourceView.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSSetConstantBuffers) - Define os constantes buffers usados pela fase vértice shader pipeline.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
CarenResult CarenD3D11DeviceContext1::VSSetConstantBuffers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroBuffers,
	cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11Buffer*> VectorInterfaces;
	ID3D11Buffer* pBuff = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(Param_NumeroBuffers);

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroBuffers; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizBuffers[i]->RecuperarPonteiro((LPVOID*)&pBuff);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pBuff);

		//Limpa
		pBuff = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSSetConstantBuffers(Param_StartSlot, Param_NumeroBuffers, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline vértice shader.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
CarenResult CarenD3D11DeviceContext1::VSSetSamplers(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroAmostradores,
	cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11SamplerState*> VectorInterfaces;
	ID3D11SamplerState* pSample = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(Param_NumeroAmostradores);

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroAmostradores; i++)
	{
		//Recupera o ponteiro para o buffer.
		Param_MatrizAmostradoresEstado[i]->RecuperarPonteiro((LPVOID*)&pSample);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pSample);

		//Limpa
		pSample = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSSetSamplers(Param_StartSlot, Param_NumeroAmostradores, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSSetShader) - Defina um sombreador de vértices para o dispositivo.
/// </summary>
/// <param name="Param_ShaderVertice">Ponteiro para um sombreador de vértice. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
CarenResult CarenD3D11DeviceContext1::VSSetShader(
	ICarenD3D11VertexShader^ Param_ShaderVertice,
	cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
	UInt32 Param_NumeroInstanciasClasse)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11VertexShader* pVertexShader = NULL; //Pode ser nulo.
	std::vector<ID3D11ClassInstance*> VectorInterfaces; //Pode ser nulo.
	ID3D11ClassInstance* pInstance = NULL;

	//Reserva o vetor para a quantidade especificada pelo usuário se for maior que zero.
	//Se for, vai copiar as interfaces aqui mesmo.
	if (Param_NumeroInstanciasClasse > 0)
	{
		//Reverva uma quantidade para o vetor.
		VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroInstanciasClasse));

		//Obtem e define as interfaces no vetor.
		for (UINT i = 0; i < Param_NumeroInstanciasClasse; i++)
		{
			//Recupera o ponteiro para a interface.
			Param_MatrizInstanciaClasse[i]->RecuperarPonteiro((LPVOID*)&pInstance);

			//Define o ponteiro no vetor.
			VectorInterfaces.push_back(pInstance);

			//Limpa
			pInstance = NULL;
		}
	}

	//Recupera o ponteiro para o Sombreador de Pixel se tiver sido fornecido
	if (ObjetoGerenciadoValido(Param_ShaderVertice))
	{
		//Recupera o ponteiro para a interface.
		Param_ShaderVertice->RecuperarPonteiro((LPVOID*)&pVertexShader);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSSetShader(pVertexShader ? pVertexShader : NULL, Param_NumeroInstanciasClasse > 0 ? VectorInterfaces.data() : NULL, Param_NumeroInstanciasClasse);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (VSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de vértices.
/// </summary>
/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
CarenResult CarenD3D11DeviceContext1::VSSetShaderResources(
	UInt32 Param_StartSlot,
	UInt32 Param_NumeroViews,
	cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	std::vector<ID3D11ShaderResourceView*> VectorInterfaces;
	ID3D11ShaderResourceView* pShaderView = NULL;

	//Define a quantidade de dados que vai conter no vetor.
	VectorInterfaces.reserve(static_cast<size_t>(Param_NumeroViews));

	//Faz um for para obter os buffers e definir no vetor.
	for (UINT i = 0; i < Param_NumeroViews; i++)
	{
		//Recupera o ponteiro para a interface.
		Param_MatrizVisualizadoresSombreador[i]->RecuperarPonteiro((LPVOID*)&pShaderView);

		//Define o ponteiro no vetor.
		VectorInterfaces.push_back(pShaderView);

		//Limpa
		pShaderView = NULL;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->VSSetShaderResources(Param_StartSlot, Param_NumeroViews, VectorInterfaces.data());

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Limpa o vetor.
	VectorInterfaces.clear();
	VectorInterfaces.shrink_to_fit();

	//Retorna o resultado.
	return Resultado;
}




//Métodos da interface (ICarenD3D11DeviceChild)

/// <summary>
/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
/// </summary>
/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
/// para transforma em sua interface original.</param>
CarenResult CarenD3D11DeviceContext1::GetDevice(ICaren^ Param_Out_DispositivoD3D11)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Device* pDevice = NULL;

	//Chama o método
	PonteiroTrabalho->GetDevice(&pDevice);

	//Verifica se a operação obteve sucesso.
	if (ObjetoValido(pDevice))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o código HRESULT.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método.
		goto Done;
	}

	//Define o ponteiro do dispositivo.
	Param_Out_DispositivoD3D11->AdicionarPonteiro(pDevice);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (GetPrivateData) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
CarenResult CarenD3D11DeviceContext1::GetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_BufferDados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	LPVOID pDados = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Chama o método
	Hr = PonteiroTrabalho->GetPrivateData(GuidDados, &OutLarguraDados, &pDados);

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

	//Cria a interface que vai conter o ponteiro de dados.
	Param_Out_BufferDados = gcnew CarenBuffer();

	//Define o ponteiro de dados na interface de buffer.
	Param_Out_BufferDados->CreateBuffer(IntPtr(pDados), false, OutLarguraDados, OutLarguraDados);

	//Define o tamanho real dos dados retornados.
	Param_Out_TamanhoBufferSaida = OutLarguraDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
CarenResult CarenD3D11DeviceContext1::SetPrivateData(
	String^ Param_Guid,

	UInt32 Param_TamanhoBuffer, ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	PBYTE pDados = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Obtém o ponteiro para os dados.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se é valido
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pDados = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método que vai definir os dados.
	Hr = PonteiroTrabalho->SetPrivateData(GuidDados, Param_TamanhoBuffer, pDados);

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
/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
CarenResult CarenD3D11DeviceContext1::SetPrivateDataInterface(
	String^ Param_Guid, ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidAssociado = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidAssociado = Util.CreateGuidFromString(Param_Guid);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)pInterface);

	//Verifica se a interface não é invalida
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface é invalida

		//Sai do método
		goto Done;
	}

	//Chama o método para definir a interface.
	Hr = PonteiroTrabalho->SetPrivateDataInterface(GuidAssociado, pInterface);

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