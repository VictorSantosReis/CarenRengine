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
#include "CarenD3D11Texture1D.h"

//Destruidor.
CarenD3D11Texture1D::~CarenD3D11Texture1D()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD3D11Texture1D::CarenD3D11Texture1D()
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
CarenResult CarenD3D11Texture1D::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Texture1D::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Texture1D*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Texture1D**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Texture1D::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Texture1D*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Texture1D**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Texture1D::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Texture1D::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD3D11Texture1D::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD3D11Texture1D::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11Texture1D::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11Texture1D::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11Texture1D::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD3D11Texture1D::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD3D11Texture1D();
}





//Métodos da interface proprietaria

/// <summary>
/// (GetDesc) - Obtem as propriedades do recurso de textura.
/// </summary>
/// <param name="Param_Out_PropsTextura1D">Retorna uma estrutura com as descrições do recuso.</param>
CarenResult CarenD3D11Texture1D::GetDesc([Out] Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_Out_PropsTextura1D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	Utilidades Util;
	D3D11_TEXTURE1D_DESC DescTextura1D;

	//Chama o método para realizar a operação
	PonteiroTrabalho->GetDesc(&DescTextura1D);

	//Converte a estrutura e define no parametro de saida.
	Param_Out_PropsTextura1D = Util.ConverterD3D11_TEXTURE1D_DESCUnManaged_ToManaged(&DescTextura1D);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}




//Métodos da interface proprietaria(ICarenD3D11Resource)

/// <summary>
/// (GetEvictionPriority) - Obtém a prioridade de despejo de um recurso.
/// </summary>
/// <param name="Param_Out_Prioridade">Retorna a prioridade do recurso que está sendo usado.</param>
CarenResult CarenD3D11Texture1D::GetEvictionPriority([Out] Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO% Param_Out_Prioridade)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Resource::GetEvictionPriority(PonteiroTrabalho,
		Param_Out_Prioridade
	);
}

/// <summary>
/// (GetType) - Obtém o tipo de recurso.
/// </summary>
/// <param name="Param_Out_TipoRecurso">Retorna o tipo do recurso usado.</param>
CarenResult CarenD3D11Texture1D::GetType([Out] Enumeracoes::CA_D3D11_TIPO_RECURSO% Param_Out_TipoRecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Resource::GetType(PonteiroTrabalho,
		Param_Out_TipoRecurso
	);
}

/// <summary>
/// (SetEvictionPriority) - Define a prioridade de despejo de um recurso.
/// Prioridades de recursos determinam qual recurso despejo de memória de vídeo quando o sistema ficou sem memória de vídeo. O recurso não será perdido; será removido da memória de vídeo e colocado na 
/// memória do sistema ou possivelmente colocado no disco rígido. O recurso será carregado volta na memória de vídeo quando for necessário.
/// </summary>
/// <param name="Param_PrioridadeRecurso">Define o tipo do recurso sendo usado.</param>
CarenResult CarenD3D11Texture1D::SetEvictionPriority(Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO Param_PrioridadeRecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Resource::SetEvictionPriority(PonteiroTrabalho,
		Param_PrioridadeRecurso
	);
}




//Métodos da interface proprietaria(ICarenD3D11DeviceChild)

/// <summary>
/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
/// </summary>
/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
/// para transforma em sua interface original.</param>
CarenResult CarenD3D11Texture1D::GetDevice(ICaren^ Param_Out_DispositivoD3D11)
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
CarenResult CarenD3D11Texture1D::GetPrivateData(
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
CarenResult CarenD3D11Texture1D::SetPrivateData(
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
CarenResult CarenD3D11Texture1D::SetPrivateDataInterface(
	String^ Param_Guid, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11DeviceChild::SetPrivateDataInterface(PonteiroTrabalho,
		Param_Guid,
		Param_Interface
	);
}