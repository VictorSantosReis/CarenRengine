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
#include "CarenDXGIResource1.h"

//Destruidor.
CarenDXGIResource1::~CarenDXGIResource1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGIResource1::CarenDXGIResource1()
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
CarenResult CarenDXGIResource1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIResource1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIResource1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIResource1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIResource1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIResource1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIResource1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIResource1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIResource1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIResource1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIResource1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIResource1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIResource1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIResource1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIResource1();
}



// Métodos da interface proprietária(ICarenDXGIResource1)

/// <summary>
/// (CreateSharedHandle) - Cria uma Handle para um recurso compartilhado. Em seguida, você pode usar a Handle devolvida com vários dispositivos Direct3D.
/// </summary>
/// <param name="Param_Atributos">Uma estrutura CA_SECURITY_ATTRIBUTES que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e 
/// um valor booleano que determina se os processos crianças podem herdar a Handle devolvida.
/// Defina esse parâmetro para NULO se desejar que os processos filhos que o aplicativo possa criar não herdem a Handle retornado por CreateSharedHandle e se 
/// desejar que o recurso associado ao identificador retornado obtenha um descritor de segurança padrão.</param>
/// <param name="Param_Acesso">Os direitos de acesso solicitados ao recurso. Você pode realizar um bitwise entre as enumerações CA_ACCESS_RIGHTS e CA_DXGI_SHARED_RESOURCE_RW 
/// para definir esse parametro.</param>
/// <param name="Param_Nome">O nome do recurso para compartilhar. O nome se limita a constante MAX_PATH. A comparação de nomes é sensível ao caso(CaseSensitive).
/// Você precisará do nome de recurso se ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhadoPorNome para acessar o recurso compartilhado pelo nome. Se você, 
/// em vez disso, ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhado1 para acessar o recurso compartilhado por cabo, defina este parâmetro para NULO.</param>
/// <param name="Param_Out_Handle">Recebe o ponteiro para uma variável que recebe o valor NT HANDLE para o recurso para compartilhar. Você pode usar esta Handle em 
/// chamadas para acessar o recurso.</param>
CarenResult CarenDXGIResource1::CreateSharedHandle(
	CA_SECURITY_ATTRIBUTES^ Param_Atributos,
	UInt64 Param_Acesso,
	String^ Param_Nome,
	[Out] IntPtr% Param_Out_Handle)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::CreateSharedHandle(PonteiroTrabalho,
		Param_Atributos,
		Param_Acesso,
		Param_Nome,
		Param_Out_Handle
	);
}

/// <summary>
/// (CreateSubresourceSurface) - Cria um objeto de superfície subrecurso.
/// </summary>
/// <param name="Param_Index">O índice do objeto de superfície do subrecurso a ser enumerado.</param>
/// <param name="Param_Out_DXGISurface2">Recebe um ponteiro para uma interface ICarenDXGISurface2 que representa o objeto de superfície do subrecurso criado na posição 
/// especificada pelo parâmetro (Param_Index). O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIResource1::CreateSubresourceSurface(
	UInt32 Param_Index, 
	ICaren^ Param_Out_DXGISurface2)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::CreateSubresourceSurface(PonteiroTrabalho,
		Param_Index,
	    Param_Out_DXGISurface2
	);
}




// Métodos da interface ICarenDXGIResource

/// <summary>
/// (GetEvictionPriority) - Obtenha a prioridade de despejo.
/// </summary>
/// <param name="Param_Out_PrioridadeDespejo">Recebe valores da enumeração CA_DXGI_RESOURCE_PRIORITY, que determinam quando o recurso pode ser despejado.</param>
CarenResult CarenDXGIResource1::GetEvictionPriority([Out] CA_DXGI_RESOURCE_PRIORITY% Param_Out_PrioridadeDespejo)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::GetEvictionPriority(PonteiroTrabalho,
		Param_Out_PrioridadeDespejo
	);
}

/// <summary>
/// (GetSharedHandle) - Obtém a Handle para um recurso compartilhado.
/// [A partir do Direct3D 11.1, recomendamos não usar o (GetSharedHandle) mais para recuperar a alça a um recurso compartilhado. Em vez disso, use o 
/// ICarenDXGIResource1::CreateSharedHandle para obter uma Handle para compartilhar. Para usar o ICarenDXGIResource1::CreateSharedHandle deve especificar 
/// que ele usa Handle NT (ou seja, você define a bandeira CA_D3D11_RESOURCE_MISC_SHARED_NTHANDLE). Também recomendamos que você crie recursos compartilhados que 
/// usam Handles NT para que você possa usar CloseHandle, DuplicateHandle, e assim por diante esses recursos compartilhados.]
/// </summary>
/// <param name="Param_Out_SharedHandle">Retorna um ponteiro para a Handle compartilhada.</param>
CarenResult CarenDXGIResource1::GetSharedHandle([Out] IntPtr% Param_Out_SharedHandle)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::GetSharedHandle(PonteiroTrabalho,
		Param_Out_SharedHandle
	);
}

/// <summary>
/// (GetUsage) - Obtenha o uso esperado de recursos.
/// </summary>
/// <param name="Param_Out_Usage">Recebe uma bandeira de uso(DXGI_USAGE). Para direct3D 10, uma superfície pode ser usada como entrada sombreadora ou uma saída de 
/// destino renderizado.</param>
CarenResult CarenDXGIResource1::GetUsage([Out] CA_DXGI_USAGE% Param_Out_Usage)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::GetUsage(PonteiroTrabalho,
		Param_Out_Usage
	);
}

/// <summary>
/// (SetEvictionPriority) - Defina a prioridade para despejar o recurso da memória.
/// </summary>
/// <param name="Param_PrioridadeDespejo">Um valor da enumeração CA_DXGI_RESOURCE_PRIORITY que define a prioridade do despejo.</param>
CarenResult CarenDXGIResource1::SetEvictionPriority(CA_DXGI_RESOURCE_PRIORITY Param_PrioridadeDespejo)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIResource::SetEvictionPriority(PonteiroTrabalho,
		Param_PrioridadeDespejo
	);
}




// Métodos da interface ICarenDXGIDeviceSubObject

/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIResource1::GetDevice(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_Objeto)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIDeviceSubObject::GetDevice(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_Objeto
	);
}




// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIResource1::GetParent(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_ObjetoPai)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetParent(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_ObjetoPai
	);
}

/// <summary>
/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGIResource1::SetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32 Param_TamanhoDados, 
	ICaren^ Param_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_TamanhoDados,
		Param_Dados
	);
}

/// <summary>
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIResource1::GetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32% Param_Ref_TamanhoDados, 
	ICaren^ Param_Out_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_Ref_TamanhoDados,
		Param_Out_Dados
	);
}

/// <summary>
/// Define uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGIResource1::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}
