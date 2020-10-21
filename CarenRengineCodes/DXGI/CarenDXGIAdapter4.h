﻿/*
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


#pragma once
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "CarenDXGIOutput.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por reprentar um subsistema de exibição, e estende essa família de interfaces para expor um 
/// método para verificar a compatibilidade de um adaptador com a Arbitrarriedade code guard (ACG).
/// </summary>
public ref class CarenDXGIAdapter4 : public ICarenDXGIAdapter4
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIAdapter4).
	IDXGIAdapter4* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenDXGIAdapter4();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenDXGIAdapter4">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenDXGIAdapter4^% Param_Out_CarenDXGIAdapter4)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenDXGIAdapter4 = gcnew CarenDXGIAdapter4();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
	}


	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenDXGIAdapter4)
public:
	/// <summary>
	/// (GetDesc3) - Obtém uma descrição 1.6 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. Esta descrição inclui 
	/// informações sobre compatibilidade com ACG.
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Recebe uma estrutura CA_DXGI_ADAPTER_DESC3 que descreve o adaptador. Este parâmetro não deve ser NULO. No hardware gráfico nível 9, 
	/// versões iniciais do ObterDescricao3(ObterDescricao1 ObterDescricao) retornam zeros para o ID PCI em (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do 
	/// adaptador e "Adaptador de Software" para a string de descrição no membro (Description). ObterDescricao3 e ObterDescricao2 retornam os valores reais de hardware nível 9 
	/// nesses membros.</param>
	virtual CarenResult ObterDescricao3([Out] CA_DXGI_ADAPTER_DESC3^% Param_Out_DescAdaptador);



	//Métodos da interface(ICarenDXGIAdapter3)
public:
	/// <summary>
	/// (QueryVideoMemoryInfo) - Este método informa o processo de uso do orçamento e do processo atual.
	/// </summary>
	/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações da memória de vídeo são consultadas. Para operação de GPU única, coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de vídeo são consultadas.</param>
	/// <param name="Param_GrupoSegmento">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
	/// <param name="Param_Out_InfoMemoria">Recebe uma estrutura CA_DXGI_QUERY_VIDEO_MEMORY_INFO com os valores atuais.</param>
	virtual CarenResult ConsultarInfoMemoriaVideo(
		UInt32 Param_NodeId,
		CA_DXGI_MEMORY_SEGMENT_GROUP Param_GrupoSegmento,
		[Out] CA_DXGI_QUERY_VIDEO_MEMORY_INFO^% Param_Out_InfoMemoria);

	/// <summary>
	/// (RegisterHardwareContentProtectionTeardownStatusEvent) - Se registra para receber notificação de eventos de proteção de proteção de conteúdo de hardware.
	/// </summary>
	/// <param name="Param_Evento">Uma Handle para o objeto de evento que o sistema operacional define quando ocorre o (TearDown) de proteção de conteúdo de hardware. </param>
	/// <param name="Param_Out_Cookie">um valor-chave que um aplicativo pode passar para o método ICarenDXGIAdapter3:::CancelarHardwareContentProtectionTeardownStatus para 
	/// descadastrar o evento de notificação que o Param_Evento especifica.</param>
	virtual CarenResult RegistrarHardwareContentProtectionTeardownStatusEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

	/// <summary>
	/// (RegisterVideoMemoryBudgetChangeNotificationEvent) - Este método estabelece uma correlação entre um objeto de sincronização da CPU e o evento de mudança orçamentária.
	/// </summary>
	/// <param name="Param_Evento">Uma Handle para o objeto de evento.</param>
	/// <param name="Param_Out_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent
	/// retorna esse valor.</param>
	virtual CarenResult RegistrarVideoMemoryBudgetChangeNotificationEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

	/// <summary>
	/// (SetVideoMemoryReservation) - Este método envia a memória física mínima necessária para uma aplicação, para o Sistema Operacional.
	/// </summary>
	/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações de memória de vídeo estão sendo definidas. Para operação de GPU única, 
	/// coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de 
	/// vídeo estão sendo definidas.</param>
	/// <param name="Param_SegmentoGrupoMemoria">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
	/// <param name="Param_ReversaMemoria">Especifica um UInt64 que define a memória física mínima necessária, em bytes.</param>
	virtual CarenResult DefinirReversaMemoriaVideo(
		UInt32 Param_NodeId,
		CA_DXGI_MEMORY_SEGMENT_GROUP Param_SegmentoGrupoMemoria,
		UInt64 Param_ReversaMemoria);

	/// <summary>
	/// (UnregisterHardwareContentProtectionTeardownStatus) - O Desregistra(Cancelar) um evento para impedi-lo de receber a notificação de eventos de proteção de 
	/// conteúdo de hardware.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent 
	/// retorna esse valor.</param>
	virtual CarenResult CancelarHardwareContentProtectionTeardownStatus(UInt32 Param_Cookie);

	/// <summary>
	/// (UnregisterVideoMemoryBudgetChangeNotification) - Este método deixa de notificar um objeto de sincronização da CPU sempre que ocorre uma mudança orçamentária. Um aplicativo pode mudar para a votação regular das informações.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent 
	/// retorna esse valor.</param>
	virtual CarenResult CancelarVideoMemoryBudgetChangeNotification(UInt32 Param_Cookie);


	//Métodos da interface(ICarenDXGIAdapter2)
public:
	/// <summary>
	/// (GetDesc2) - Obtém uma descrição 1.2 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. 
	/// Esta descrição inclui informações sobre a granularidade em que a unidade de processamento gráfico (GPU) pode ser impedida de realizar 
	/// sua tarefa atual.
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC2 que descreve o adaptador. Este parâmetro não deve ser 
	/// NULO.No hardware gráfico nível 9, versões anteriores do ObterDescricao2(ObterDescricao e ObterDescricao1) retorna zero para o 
	/// PCI ID em e (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do adaptador e "Adaptador de Software" para a descrição 
	/// do membro (Description). O ObterDescricao2 retorna os valores reais de hardware nível 9 nesses membros.</param>
	virtual CarenResult ObterDescricao2([Out] CA_DXGI_ADAPTER_DESC2^% Param_Out_DescAdaptador);


	//Métodos da interface(ICarenDXGIAdapter1)
public:
	/// <summary>
	/// (GetDesc1) - Obtém uma descrição DXGI 1.1 de um adaptador (ou cartão de vídeo).
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC1 que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (ObterDescricao1) retorna zeros para o 
	/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC1 e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
	virtual CarenResult ObterDescricao1([Out] CA_DXGI_ADAPTER_DESC1^% Param_Out_DescAdaptador);



	//Métodos da interface(ICarenDXGIAdapter)
public:
	/// <summary>
	/// (CheckInterfaceSupport) - Verifica se o sistema suporta uma interface do dispositivo para um componente gráfico.
	/// </summary>
	/// <param name="Param_GuidInterface">O GUID da interface da versão do dispositivo para a qual o suporte está sendo verificado.</param>
	/// <param name="Param_Out_UMDVersion">A versão do motorista do modo de usuário do (Param_GuidInterface). Isso só é devolvido se a interface for suportada, caso contrário, este parâmetro será -12354.</param>
	virtual CarenResult ChecarSuporteInterface(String^ Param_GuidInterface, [Out] Int64% Param_Out_UMDVersion);

	/// <summary>
	/// (EnumOutputs) - Saídas de adaptador enumerado (cartão de vídeo).
	/// </summary>
	/// <param name="Param_IndexSaida">O índice da saída.</param>
	/// <param name="Param_Out_Saida">O endereço de um ponteiro para uma interface ICarenDXGIOutput na posição especificada pelo parâmetro (Param_IndexSaida).</param>
	virtual CarenResult EnumerarSaidas(UInt32 Param_IndexSaida, [Out] ICarenDXGIOutput^% Param_Out_Saida);

	/// <summary>
	/// (GetDesc) - Obtém uma descrição DXGI 1.0 de um adaptador (ou cartão de vídeo).
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (ObterDescricao) retorna zeros para o 
	/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
	virtual CarenResult ObterDescricao([Out] CA_DXGI_ADAPTER_DESC^% Param_Out_DescAdaptador);



	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// (GetParent) - Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterPaiObjeto(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// (SetPrivateData) - Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult DefinirDadosPrivados(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// (GetPrivateData) - Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterDadosPrivados(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// (SetPrivateDataInterface) - Defina uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult DefinirDadosPrivadosInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};