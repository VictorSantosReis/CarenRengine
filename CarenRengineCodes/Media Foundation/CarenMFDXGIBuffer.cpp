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
#include "CarenMFDXGIBuffer.h"


//Destruidor.
CarenMFDXGIBuffer::~CarenMFDXGIBuffer()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFDXGIBuffer::CarenMFDXGIBuffer()
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
CarenResult CarenMFDXGIBuffer::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFDXGIBuffer::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFDXGIBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFDXGIBuffer**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFDXGIBuffer::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFDXGIBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFDXGIBuffer**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFDXGIBuffer::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFDXGIBuffer::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFDXGIBuffer::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFDXGIBuffer::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFDXGIBuffer::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFDXGIBuffer::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFDXGIBuffer::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFDXGIBuffer::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFDXGIBuffer();
}





// Métodos da interface proprietária (ICarenMFDXGIBuffer)


/// <summary>
/// Consulta a superfície do Microsoft DirectX Graphics infra-estrutura (DXGI) para uma interface.
/// Você pode usar esse método para obter um ponteiro para a interface de ID3D11Texture2D da superfície. Se o buffer estiver bloqueado, o método retorna ER_MF_REQUISICAO_INVALIDA.
/// </summary>
/// <param name="Param_Guid">O identificador de interface (IID) da interface requisitada.</param>
/// <param name="Param_Out_InterfaceRecurso">Recebe um ponteiro para a interface. O chamador deve liberar a interface. O Usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenMFDXGIBuffer::GetResource(String^ Param_Guid, ICaren^ Param_Out_InterfaceRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas no método.
	GUID vi_GuidRecurso = GUID_NULL;
	LPUNKNOWN vi_pOutResource = NULL;

	//Cria o guid da interface de recurso.
	CarenCreateGuidFromStringSafe(Param_Guid, vi_GuidRecurso);

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->GetResource(vi_GuidRecurso, reinterpret_cast<void**>(&vi_pOutResource));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface no parametro de siada.
	CarenSetPointerToICarenSafe(vi_pOutResource, Param_Out_InterfaceRecurso, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém o índice do sub-recurso que está associado com esse buffer de mídia.
/// </summary>
/// <param name="Param_Out_SubResourceId">Recebe o índice baseado em zero do sub-recurso.</param>
CarenResult CarenMFDXGIBuffer::GetSubresourceIndex([Out] UInt32% Param_Out_SubResourceId) 
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas no método.
	UINT vi_OutSubRecursoId = 0;

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->GetSubresourceIndex(&vi_OutSubRecursoId);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o id do sub-recurso.
	Param_Out_SubResourceId = vi_OutSubRecursoId;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um ponteiro IUnknown que anteriormente foi armazenado no objeto de reserva de meios de comunicação.
/// </summary>
/// <param name="Param_GuidInterface">O identificador do ponteiro IUnknown.</param>
/// <param name="Param_IID">O identificador de interface (IID) da interface requisitada.</param>
/// <param name="Param_Out_InterfaceRequisitada">Recebe um ponteiro para o objeto anteriormente definido. O chamador é responsável por inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFDXGIBuffer::GetUnknown(String^ Param_GuidInterface, String^ Param_IID, ICaren^ Param_Out_InterfaceRequisitada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas no método.
	GUID vi_GuidInterface = GUID_NULL;
	GUID vi_RIIDInterface = GUID_NULL;
	LPVOID vi_pOutInterface = NULL;

	//Converte os parametros de Strings para GUIDs nativos.
	CarenCreateGuidFromStringSafe(Param_GuidInterface, vi_GuidInterface);
	CarenCreateGuidFromStringSafe(Param_IID, vi_RIIDInterface);

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->GetUnknown(vi_GuidInterface, vi_RIIDInterface, &vi_pOutInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface no parametro de saida.
	CarenSetPointerToICarenSafe(reinterpret_cast<IUnknown*>(vi_pOutInterface), Param_Out_InterfaceRequisitada, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Armazena um ponteiro IUnknown arbitrário em objeto de reserva de meios de comunicação.  
/// </summary>
/// <param name="Param_GuidInterface">O identificador para o ponteiro IUnknown. Esse identificador é usado como uma chave para recuperar o valor. Pode ser qualquer valor GUID.</param>
/// <param name="Param_Interface">Um ponteiro para a interface IUnknown. Defina este parâmetro como NULL para limpar um ponteiro que foi previamente definido.</param>
CarenResult CarenMFDXGIBuffer::SetUnknown(String^ Param_GuidInterface, ICaren^ Param_Interface) 
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM  Hr = E_FAIL;

	//Variaveis utilizadas no método.
	GUID vi_GuidInterface = GUID_NULL;
	IUnknown* vi_pOutInterface = NULL;

	//Obtém o Guid da interface a ser definida.
	CarenCreateGuidFromStringSafe(Param_GuidInterface, vi_GuidInterface);

	//Obtém o ponteiro para a interface nativa a ser definida.
	CarenGetPointerFromICarenSafe(Param_Interface, vi_pOutInterface);

	//Chama o método para realizar a função
	Hr = PonteiroTrabalho->SetUnknown(vi_GuidInterface, vi_pOutInterface);

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
	//Retorna o resultado
	return Resultado;
}
