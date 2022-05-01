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
#include "CarenD3D11Fence.h"

//Destruidor.
CarenD3D11Fence::~CarenD3D11Fence()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD3D11Fence::CarenD3D11Fence()
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
CarenResult CarenD3D11Fence::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Fence::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Fence*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Fence**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Fence::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Fence*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Fence**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Fence::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Fence::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD3D11Fence::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD3D11Fence::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11Fence::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11Fence::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11Fence::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD3D11Fence::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD3D11Fence();
}


//
// Métodos da interface proprietária(ICarenD3D11Fence)
//

/// <summary>
/// (CreateSharedHandle) - Cria uma Handle compartilhada em um objeto de Fence.
/// </summary>
/// <param name="Param_AtributosSec">Uma estrutura CA_SECURITY_ATTRIBUTES que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e um valor booleanoque determina se os
/// processos filho podem herdar a Handle retornada. Defina esse parâmetro como NULO se quiser processos filho que o aplicativo pode criar para não herdar a Handle devolvida pelo (CreateSharedHandle) se você 
/// quiser que o recurso associado à Handle retornada obtenha um descritor de segurança padrão. O membro do lpSecurityDescriptor da estrutura especifica um CA_SECURITY_DESCRIPTOR para o recurso. Defina esse membro como 
/// NULO se quiser que o tempo de execução atribua um descritor de segurança padrão ao recurso associado à Handle retornada. As ACLs no descritor de segurança padrão para o recurso vêm do token principal ou de 
/// personificação do criador.</param>
/// <param name="Param_TipoAcesso">Atualmente, o único valor que este parâmetro aceita é GENERIC_ALL(CA_ACCESS_RIGHTS::CA_ACR_GENERIC_ALL)</param>
/// <param name="Param_Nome">Uma sequência UNICODE com término NULO que contém o nome para associar com o heap compartilhado. O nome é limitado a MAX_PATH caracteres. A comparação de nomes é sensível a maiúsculas 
/// e minúsculas.</param>
/// <param name="Param_Out_SharedHandle">Recebe o valor NT HANDLE para o recurso a compartilhar. Você pode usar está Handle em chamadas para acessar o recurso.</param>
CarenResult CarenD3D11Fence::CreateSharedHandle(
				CA_SECURITY_ATTRIBUTES^ Param_AtributosSec, 
				UInt32 Param_TipoAcesso, 
				String^ Param_Nome, 
				[Out] IntPtr% Param_Out_SharedHandle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	SECURITY_ATTRIBUTES* pAtributos = NULL;
	HANDLE OutSharedHandle = NULL;
	LPWSTR pNome = NULL;

	//Verifica se forneceu uma estrutura de segurança
	if (ObjetoGerenciadoValido(Param_AtributosSec))
	{
		//Converte a estrutura gerenciada para a nativa.
		pAtributos = Util.ConverterSECURITY_ATTRIBUTESManagedToUnamaged(Param_AtributosSec);
	}

	//Verifica se o nome é valido e converte
	if (ObjetoGerenciadoValido(Param_Nome))
	{
		//Converte a string em uma representação nativa.
		pNome = Util.ConverterStringToWCHAR(Param_Nome);
	}
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSharedHandle(pAtributos, Param_TipoAcesso, pNome, &OutSharedHandle);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a handle no parametro de saida
	Param_Out_SharedHandle = Util.ConverterHandleToIntPtr(OutSharedHandle);

Done:;
	//Libera a memória utilizada pelo nome
	delete pNome;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCompletedValue) - Obtém o valor atual do Fence.
/// </summary>
/// <param name="Param_Out_Valor">Obtém o valor atual do Fence.</param>
CarenResult CarenD3D11Fence::GetCompletedValue([Out] UInt64% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 OutValor = 0;

	//Chama o método para realizar a operação.
	OutValor = PonteiroTrabalho->GetCompletedValue();

	//Define o valor no parametro de saida.
	Param_Out_Valor = OutValor;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetEventOnCompletion) - Especifica um evento que deve ser disparado quando a vedação atinge um determinado valor.
/// </summary>
/// <param name="Param_ValorDisparo">O valor do Fence quando o evento deve ser sinalizado.</param>
/// <param name="Param_HandleEvento">Uma handle para o objeto do evento.</param>
CarenResult CarenD3D11Fence::SetEventOnCompletion(
				UInt64 Param_ValorDisparo,
				ICarenEvent^ Param_HandleEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE HandEvento = NULL;

	//Recupera o ponteiro para a handle do evento
	Resultado = Param_HandleEvento->RecuperarEvento(&HandEvento);

	//Verifica o resultado
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O ponteiro provavelmente é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetEventOnCompletion(Param_ValorDisparo, HandEvento);

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
	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface ICarenD3D11DeviceChild

/// <summary>
/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
/// </summary>
/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
/// para transforma em sua interface original.</param>
CarenResult CarenD3D11Fence::GetDevice(ICaren^ Param_Out_DispositivoD3D11)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11DeviceChild::GetDevice(PonteiroTrabalho,
		Param_Out_DispositivoD3D11
	);
}

/// <summary>
/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (GetPrivateData) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
CarenResult CarenD3D11Fence::GetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_BufferDados)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11DeviceChild::GetPrivateData(PonteiroTrabalho,
		Param_Guid,
		Param_TamanhoBuffer,
		Param_Out_TamanhoBufferSaida,
		Param_Out_BufferDados
	);
}

/// <summary>
/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
CarenResult CarenD3D11Fence::SetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer, 
	ICarenBuffer^ Param_Buffer)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11DeviceChild::SetPrivateData(PonteiroTrabalho,
		Param_Guid,
		Param_TamanhoBuffer,
		Param_Buffer
	);
}

/// <summary>
/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
CarenResult CarenD3D11Fence::SetPrivateDataInterface(
	String^ Param_Guid, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11DeviceChild::SetPrivateDataInterface(PonteiroTrabalho,
		Param_Guid,
		Param_Interface
	);
}
