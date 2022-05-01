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
#include "CarenDXGISurface2.h"

//Destruidor.
CarenDXGISurface2::~CarenDXGISurface2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGISurface2::CarenDXGISurface2()
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
CarenResult CarenDXGISurface2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISurface2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISurface2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISurface2**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISurface2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISurface2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISurface2**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISurface2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISurface2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGISurface2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGISurface2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGISurface2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGISurface2::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGISurface2::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGISurface2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGISurface2();
}


// Métodos da interface proprietária(ICarenDXGISurface2)

/// <summary>
/// (GetResource) - Obtém o índice de recursos parentais e subrecursos que suportam uma superfície de subrecursos.
/// Os objetos atuais que implementam o IDXGISurface são recursos ou visualizações. GetResource para esses objetos retorna "this" ou o 
/// recurso que suporta a exibição, respectivamente. Nesta situação, o índice de subrecursos é 0.
/// </summary>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do tipo de interface solicitado.</param>
/// <param name="Param_Out_ObjetoRecurso">Recebe um ponteiro para um buffer que recebe um ponteiro para o objeto de recurso pai para a superfície do subrecurso.  O usuário deve inicializar a interface antes de chamar este método.</param>
/// <param name="Param_Ref_IndexSubrecurso">Recebe o índice da superfície do subrecurso.</param>
CarenResult CarenDXGISurface2::GetResource(
	String^ Param_RIID, 
	ICaren^ Param_Out_ObjetoRecurso, 
	UInt32% Param_Ref_IndexSubrecurso)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::GetResource(PonteiroTrabalho,
		Param_RIID,
		Param_Out_ObjetoRecurso,
		Param_Ref_IndexSubrecurso
	);
}




// Métodos da interface ICarenDXGISurface1

/// <summary>
/// (GetDC) - Retorna um contexto de dispositivo (DC) que permite que você se torne uma superfície de Infraestrutura Gráfica Microsoft DirectX (DXGI) usando a Interface do Dispositivo Gráfico windows (GDI).
/// </summary>
/// <param name="Param_Descartar">Um valor booleano que especifica se deve preservar o conteúdo Direct3D no GDI DC. 
/// TRUE direciona o tempo de execução para não preservar o conteúdo Direct3D no GDI DC; ou seja, o tempo de execução 
/// descarta o conteúdo Direct3D. False garante que o conteúdo Direct3D esteja disponível no GDI DC.</param>
/// <param name="Param_Out_HDCHandle">Recebe um ponteiro para uma Handle(Alça) HDC que representa o contexto atual do dispositivo para renderização GDI.</param>
CarenResult CarenDXGISurface2::GetDC(
	Boolean Param_Descartar, 
	[Out] IntPtr% Param_Out_HDCHandle)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::GetDC(PonteiroTrabalho,
		Param_Descartar,
		Param_Out_HDCHandle
	);
}

/// <summary>
/// (ReleaseDC) - Libera o contexto do dispositivo GDI (DC) que está associado à superfície atual e permite que você use o Direct3D para renderizar.
/// </summary>
/// <param name="Param_Regiao">Um ponteiro para uma estrutura rect que identifica a região suja da superfície. Uma região suja é qualquer 
/// parte da superfície que você usou para renderização GDI e que você quer preservar.Esta área é usada como uma dica de desempenho para 
/// subsistema gráfico em certos cenários.Não utilize este parâmetro para restringir a renderização à região retangular especificada. 
/// Se você passar NULO, ReleaseDC considera toda a superfície como suja. Caso contrário, o (ReleaseDC) usa a área especificada pelo CA_RECT
/// como uma dica de desempenho para indicar quais áreas foram manipuladas pela renderização GDI. Você pode passar um ponteiro para uma 
/// estrutura rect vazia(um retângulo sem posição ou área) se você não alterar qualquer conteúdo.</param>
CarenResult CarenDXGISurface2::ReleaseDC(CA_RECT^ Param_Regiao)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::ReleaseDC(PonteiroTrabalho,
		Param_Regiao
	);
}




// Métodos da interface ICarenDXGISurface

/// <summary>
/// (GetDesc) - Método responsável por obter uma descrição da superfície.
/// </summary>
/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
CarenResult CarenDXGISurface2::GetDesc([Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::GetDesc(PonteiroTrabalho,
		Param_Out_DescSuperfice
	);
}

/// <summary>
/// (Map) - Método responsável por obter um ponteiro para os dados contidos na superfície e negue o acesso da GPU à superfície.
/// </summary>
/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que contém os dados mapeados da superfice.</param>
CarenResult CarenDXGISurface2::Map(
	CA_DXGI_MAP_FLAGS Param_Flags, 
	[Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::Map(PonteiroTrabalho,
		Param_Flags,
		Param_Out_RectMapeado
	);
}

/// <summary>
/// (Unmap) - Método responsável por invalidar o ponteiro para a superfície recuperada pelo ICarenDXGISurface::Map e 
/// reativar o acesso GPU ao recurso.
/// </summary>
CarenResult CarenDXGISurface2::Unmap()
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::Unmap(PonteiroTrabalho);
}




// Métodos da interface ICarenDXGIDeviceSubObject

/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISurface2::GetDevice(
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
CarenResult CarenDXGISurface2::GetParent(
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
CarenResult CarenDXGISurface2::SetPrivateData(
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
CarenResult CarenDXGISurface2::GetPrivateData(
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
CarenResult CarenDXGISurface2::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}