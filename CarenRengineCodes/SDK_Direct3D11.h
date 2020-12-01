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


#pragma once
#include "SDK_Base.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace Direct3D11
	{
		/// <summary>
		/// (ID3D11DeviceChild) - Uma interface de dispositivo-criança acessa dados utilizados por um dispositivo.
		/// Existem vários tipos de interfaces de dispositivo filho, todos os quais herdam essa interface. Eles incluem shaders, objetos de estado e layouts de entrada.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um dispositivo filho comum a diversas interfaces do D3D11.")]
		[Guid("94683637-081E-4955-99C9-FBF6A2D8953B")]
		public interface class ICarenD3D11DeviceChild : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
			/// </summary>
			/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
			/// para transforma em sua interface original.</param>
			CarenResult ObterDispositivo(ICaren^ Param_Out_DispositivoD3D11);

			/// <summary>
			/// (GetPrivateData)[TESTE - PRECISA VERIFICAR SE A CONVERSAO ESTÁ CORRETA] - Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
			/// </summary>
			/// <param name="Param_Guid">GUID associado com os dados.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
			/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
			/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (ObterDadosPrivados) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
			/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
			CarenResult ObterDadosPrivados(
				String^ Param_Guid,
				UInt32 Param_TamanhoBuffer,
				[Out] UInt32% Param_Out_TamanhoBufferSaida,
				[Out] ICarenBuffer^% Param_Out_BufferDados);

			/// <summary>
			/// (SetPrivateData)[TESTE - PRECISA VERIFICAR SE A CONVERSAO ESTÁ CORRETA] - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
			/// </summary>
			/// <param name="Param_Guid">GUID associado com os dados.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
			/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
			/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
			CarenResult DefinirDadosPrivados(
				String^ Param_Guid,

				UInt32 Param_TamanhoBuffer, ICarenBuffer^ Param_Buffer);

			/// <summary>
			/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
			/// </summary>
			/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
			/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
			CarenResult DefinirInterfaceDadosPrivados(
				String^ Param_Guid, ICaren^ Param_Interface);

		};

		/// <summary>
		/// (ID3D11Resource) - Uma interface de recurso fornece ações comuns em todos os recursos.
		/// Você não criar diretamente uma interface de recurso; em vez disso, você criar buffers e texturas que herdam de uma interface de recurso.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de recursos do D3D11.")]
		[Guid("710A96E2-6DAC-4735-8E6B-494353EDFA53")]
		public interface class ICarenD3D11Resource : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetEvictionPriority) - Obtém a prioridade de despejo de um recurso.
			/// </summary>
			/// <param name="Param_Out_Prioridade">Retorna a prioridade do recurso que está sendo usado.</param>
			CarenResult ObterPrioridadeDespejo([Out] Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO% Param_Out_Prioridade);

			/// <summary>
			/// (GetType) - Obtém o tipo de recurso.
			/// </summary>
			/// <param name="Param_Out_TipoRecurso">Retorna o tipo do recurso usado.</param>
			CarenResult ObterTipo([Out] Enumeracoes::CA_D3D11_TIPO_RECURSO% Param_Out_TipoRecurso);

			/// <summary>
			/// (SetEvictionPriority) - Define a prioridade de despejo de um recurso.
			/// Prioridades de recursos determinam qual recurso despejo de memória de vídeo quando o sistema ficou sem memória de vídeo. O recurso não será perdido; será removido da memória de vídeo e colocado na 
			/// memória do sistema ou possivelmente colocado no disco rígido. O recurso será carregado volta na memória de vídeo quando for necessário.
			/// </summary>
			/// <param name="Param_PrioridadeRecurso">Define o tipo do recurso sendo usado.</param>
			CarenResult DefinirPrioridadeDespejo(Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO Param_PrioridadeRecurso);
		};

		/// <summary>
		/// (ID3D11Buffer) - Uma interface de buffer acessa um recurso de reserva, que é a memória não-estruturada. Buffers de tipicamente armazenam dados vértice ou índice.
		/// Existem três tipos de buffers: vértice, índice ou um buffer de constante de sombreador.Crie um recurso de buffer chamando ICarenD3D11Device::CriarBuffer.
		/// [Um buffer deve estar ligado para o pipeline para poder ser acessado].
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface de acesso a recursos de reserva que está em memória não estruturada.")]
		[Guid("8DB85178-0EDF-40D6-AB13-5CC870DE78BB")]
		public interface class ICarenD3D11Buffer : ICarenD3D11Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém as propriedades de um recurso de reserva.
			/// </summary>
			/// <param name="Param_Out_DescBuffer">Retorna uma estrutura com a descrição do buffer de reserva.</param>
			CarenResult ObterPropriedadesRecurso([Out] Estruturas::CA_D3D11_BUFFER_DESC^% Param_Out_DescBuffer);
		};

		/// <summary>
		/// (ID3D11View) - Uma interface de exibição especifica as partes de um recurso que o gasoduto pode acessar durante o processamento.
		/// Uma interface de exibição é a interface base para todas as vistas. Existem quatro tipos de pontos de vista; uma visão de profundidade-estêncil, um modo de exibição de destino de 
		/// processamento, uma exibição de sombreador-recurso e uma visão de acesso não-ordenados.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de exibição.")]
		[Guid("176416BD-1354-4AF5-8CA3-E87E4FAD63E3")]
		public interface class ICarenD3D11View : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetResource) - Obtém o recurso que é acessado por meio dessa visualização.
			/// </summary>
			/// <param name="Param_Out_Recurso">Retorna um ponteiro para o recurso que é acessado através desta vista.</param>
			CarenResult ObterRecurso([Out] ICarenD3D11Resource^% Param_Out_Recurso);
		};

		/// <summary>
		/// (ID3D11Fence) - Representa um Fence, um objeto usado para sincronização da CPU e uma ou mais GPUs. Esta interface é equivalente ao inteface Direct3D 12 ID3D12Fence, 
		/// e também é usada para sincronização entre Direct3D 11 e Direct3D 12 em cenários interoperabilidade.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface de sincronicação para CPU e GPU's.")]
		[Guid("70F0630F-A113-4F82-AA14-F9A8ED16F836")]
		public interface class ICarenD3D11Fence : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (CreateSharedHandle) - Cria uma Handle compartilhada em um objeto de Fence.
			/// </summary>
			/// <param name="Param_AtributosSec">Uma estrutura CA_ATRIBUTOS_SEGURANCA que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e um valor booleanoque determina se os
			/// processos filho podem herdar a Handle retornada. Defina esse parâmetro como NULO se quiser processos filho que o aplicativo pode criar para não herdar a Handle devolvida pelo (CriarHandlerCompartilhada) se você 
			/// quiser que o recurso associado à Handle retornada obtenha um descritor de segurança padrão. O membro do lpSecurityDescriptor da estrutura especifica um CA_DESCRITOR_SEGURANCA para o recurso. Defina esse membro como 
			/// NULO se quiser que o tempo de execução atribua um descritor de segurança padrão ao recurso associado à Handle retornada. As ACLs no descritor de segurança padrão para o recurso vêm do token principal ou de 
			/// personificação do criador.</param>
			/// <param name="Param_TipoAcesso">Atualmente, o único valor que este parâmetro aceita é GENERIC_ALL(CA_ACCESS_RIGHTS::CA_ACR_GENERIC_ALL)</param>
			/// <param name="Param_Nome">Uma sequência UNICODE com término NULO que contém o nome para associar com o heap compartilhado. O nome é limitado a MAX_PATH caracteres. A comparação de nomes é sensível a maiúsculas 
			/// e minúsculas.</param>
			/// <param name="Param_Out_SharedHandle">Recebe o valor NT HANDLE para o recurso a compartilhar. Você pode usar está Handle em chamadas para acessar o recurso.</param>
			CarenResult CriarHandlerCompartilhada(
				CA_ATRIBUTOS_SEGURANCA^ Param_AtributosSec, 
				UInt32 Param_TipoAcesso, 
				String^ Param_Nome, 
				[Out] IntPtr% Param_Out_SharedHandle);

			/// <summary>
			/// (GetCompletedValue) - Obtém o valor atual do Fence.
			/// </summary>
			/// <param name="Param_Out_Valor">Obtém o valor atual do Fence.</param>
			CarenResult ObterValorAtual([Out] UInt64% Param_Out_Valor);

			/// <summary>
			/// (SetEventOnCompletion) - Especifica um evento que deve ser disparado quando a vedação atinge um determinado valor.
			/// </summary>
			/// <param name="Param_ValorDisparo">O valor do Fence quando o evento deve ser sinalizado.</param>
			/// <param name="Param_HandleEvento">Uma handle para o objeto do evento.</param>
			CarenResult DefinirEvento_NaConclusao(
				UInt64 Param_ValorDisparo,
				ICarenWindowsEvent^ Param_HandleEvento);
		};

		/// <summary>
		/// (ID3D11BlendState) - A interface mistura-Estado detém uma descrição para o estado que você pode ligar para o estágio de saída-fusão de mistura.
		/// Mistura aplica uma função simples para combinar valores de saída de um sombreador de pixel com dados em um destino de processamento. Você tem controle sobre como os pixels são misturados por meio de um 
		/// conjunto predefinido de operações de mistura e preblending operações.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface de mistura de estado(BlendSate).")]
		[Guid("C5C2DDA2-1FEA-4426-ABEF-6A9CDB110FF0")]
		public interface class ICarenD3D11BlendState : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a descrição para o estado que você usou para criar o objeto de mistura-estado de mistura.
			/// </summary>
			/// <param name="Param_Out_DescEstado">Retorna uma estrutura com a descrição de um misturador de estado(Blend State).</param>
			CarenResult ObterDescriçaoEstado([Out] Estruturas::CA_D3D11_BLEND_DESC^% Param_Out_DescEstado);
		};

		/// <summary>
		/// (ID3D11BlendState1) - A interface mistura-Estado detém uma descrição para o estado que você pode ligar para o estágio de saída-fusão de mistura.
		/// Mistura aplica uma função simples para combinar valores de saída de um sombreador de pixel com dados em um destino de processamento. Você tem controle sobre como os pixels são misturados por meio de um 
		/// conjunto predefinido de operações de mistura e preblending operações.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface de mistura de estado(BlendSate).")]
		[Guid("99981A6B-28AA-4227-A8F6-0C798176A20A")]
		public interface class ICarenD3D11BlendState1 : ICarenD3D11BlendState
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtém a descrição para o estado que você usou para criar o objeto de mistura-estado de mistura.
			/// </summary>
			/// <param name="Param_Out_DescEstado">Retorna uma estrutura com a descrição de um misturador de estado(Blend State).</param>
			CarenResult ObterDescriçaoEstado1([Out] Estruturas::CA_D3D11_BLEND_DESC1^% Param_Out_DescEstado);
		};

		/// <summary>
		/// (ID3D11ClassLinkage) - Essa interface encapsula uma ligação dinâmica HLSL.
		/// Um objeto de ligação de classe pode conter até 64K obtido instâncias. Uma instância ficou é um identificador que faz referência a um nome de variável em qualquer sombreador é criado com esse objeto de 
		/// enlace. Quando você cria um sombreador com um objeto de classe de ligação, o tempo de execução reúne essas instâncias e as armazena no objeto de enlace de classe.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma encapsulção de ligação dinâmica HLSL.")]
		[Guid("899CE190-23B6-41E0-9B5D-69C5B5D5ADA6")]
		public interface class ICarenD3D11ClassLinkage : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (CreateClassInstance) - Inicializa um objeto de instância da classe que representa uma instância da classe HLSL.
			/// </summary>
			/// <param name="Para_NomeTipoClasse">O nome de tipo de uma classe para inicializar.</param>
			/// <param name="Param_DeslocamentoBufferConstante">Identifica o (Buffer Constante) que contém os dados de classe.</param>
			/// <param name="Param_DeslocamentoVetorConstante">O deslocamento de quatro componentes vetor desde o início do buffer constante onde os dados de classe vão começar. Consequentemente, isto não é um deslocamento de byte.</param>
			/// <param name="Param_DeslocamentoTextura">O slot de textura para a primeira textura; pode haver múltiplas texturas seguindo o deslocamento.</param>
			/// <param name="Param_DeslocamentoAmostrador">O slot de amostra para o primeiro sampler; pode haver vários amostradores seguindo o deslocamento.</param>
			/// <param name="Param_Out_ClasseInstance">Recebe um ponteiro para a interface (ICarenD3D11ClassInstance) para ser inicializada. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult CriarInstanciaClasseHLSL(
				String^ Para_NomeTipoClasse,
				UInt32 Param_DeslocamentoBufferConstante,
				UInt32 Param_DeslocamentoVetorConstante,
				UInt32 Param_DeslocamentoTextura,
				UInt32 Param_DeslocamentoAmostrador,
				ICaren^ Param_Out_ClasseInstance);

			/// <summary>
			/// (GetClassInstance) - Obtém o objeto de instância da classe que representa a classe especificada de HLSL.
			/// </summary>
			/// <param name="Param_NomeInstanciaClasse">O nome de uma classe para o qual deseja obter a instância de classe.</param>
			/// <param name="Param_IndiceInstancia">O índice da instância da classe.</param>
			/// <param name="Param_Out_InstanceClasse">Recebe um ponteiro para a interface (ICarenD3D11ClassInstance) para ser inicializada. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterInstanciaClasse(String^ Param_NomeInstanciaClasse, UInt32 Param_IndiceInstancia, ICaren^ Param_Out_InstanceClasse);
		};

		/// <summary>
		/// (ID3D11ClassInstance) - Essa interface encapsula uma classe HLSL.
		/// Essa interface é criada chamando ICarenD3D11ClassLinkage::CriarInstanciaClasseHLSL. A interface é usada quando a vinculação de recursos de sombreamento para o pipeline usando APIs como 
		/// ICarenD3D11DeviceContext::VSDefinirShader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma classe HLSL encapsulada.")]
		[Guid("3B9047F8-B294-400C-902D-333EB012959E")]
		public interface class ICarenD3D11ClassInstance : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetClassLinkage) - Obtém o objeto de ID3D11ClassLinkage associado com a classe atual de HLSL
			/// </summary>
			/// <param name="Param_Out_ClassLinkageAssociado">Retorna a interface do Class Linkage associado a classe atual de HLSL.</param>
			CarenResult ObterClassLinkage([Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkageAssociado);

			/// <summary>
			/// (GetDesc) - Obtém uma descrição da classe atual de HLSL.
			/// </summary>
			/// <param name="Param_Out_DescClasseHLSL">Retorna uma estrutura que contém a Descrição da classe atual.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_CLASS_INSTANCE_DESC^% Param_Out_DescClasseHLSL);

			/// <summary>
			/// (GetInstanceName) - Obtém o nome de instância da classe atual de HLSL.
			/// Este método só irá retornar um nome válido somente para instâncias adquiridas usando ICarenD3D11ClassLinkage::ObterInstanciaClasse.
			/// </summary>
			/// <param name="Param_Out_NomeInstancia">Retorna o nome da instânca atual de HLSL.</param>
			CarenResult ObterNomeInstancia([Out] String^% Param_Out_NomeInstancia);

			/// <summary>
			/// (GetTypeName) - Obtém o tipo da classe atual de HLSL.
			/// Este método só irá retornar um nome válido somente para instâncias adquiridas usando ICarenD3D11ClassLinkage::ObterInstanciaClasse.
			/// </summary>
			/// <param name="Param_Out_NomeTipoHLSL">Retorna o nome do tipo da classe atual do HLSL.</param>
			CarenResult ObterNomeTipoHLSL([Out] String^% Param_Out_NomeTipoHLSL);
		};

		/// <summary>
		/// (ID3D11ComputeShader) - Uma interface de computação-shader gerencia um programa executável (um compute shader) que controla o estágio de computação-shader.
		/// A interface de computação-shader não tem métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores são aplicadas a partir de um conjunto comum de características referidas 
		/// como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por expor os métodos da ID3D11ComputeShader.")]
		[Guid("473DFA94-D339-4DB6-B0A7-F4988E161593")]
		public interface class ICarenD3D11ComputeShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11Asynchronous) - Essa interface encapsula métodos para recuperar dados da GPU de forma assíncrona.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Recupera dados de forma assincrona.")]
		[Guid("05F9D4F6-07F5-46BC-99A4-7F906463966B")]
		public interface class ICarenD3D11Asynchronous : ICarenD3D11DeviceChild
		{
			/// <summary>
		   /// Propriedade que define se a classe foi descartada.
		   /// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDataSize) - Obtém o tamanho dos dados (em bytes) que é a saída ao chamar ICarenD3D11DeviceContext::ObterDados.
			/// </summary>
			/// <param name="Param_TamanhoDados">Retorna o tamanho dos dados (em bytes) que são emitidos ao chamar ICarenD3D11DeviceContext::ObterDados.</param>
			CarenResult ObterTamanhoDados([Out] UInt32% Param_TamanhoDados);
		};

		/// <summary>
		/// (ID3D11Query) - Interface responsável por consultar informações da GPU.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de consulta.")]
		[Guid("1F2F4246-B0A1-429B-B6A5-2E8F9D97F824")]
		public interface class ICarenD3D11Query : ICarenD3D11Asynchronous
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém uma descrição de consulta.
			/// </summary>
			/// <param name="Param_Out_DescConsulta">Retorna uma estrutura para a descrição da consulta.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_QUERY_DESC^% Param_Out_DescConsulta);
		};

		/// <summary>
		/// (ID3D11Query1) - Interface responsável por consultar informações da GPU.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de consulta.")]
		[Guid("CAD59A9E-F320-4A2E-B04D-A93A5C51F9BD")]
		public interface class ICarenD3D11Query1 : ICarenD3D11Query
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtém uma descrição de consulta.
			/// </summary>
			/// <param name="Param_Out_DescConsulta">Retorna uma estrutura para a descrição da consulta.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_QUERY_DESC1^% Param_Out_DescConsulta);
		};

		/// <summary>
		/// (ID3D11Counter) - Essa interface encapsula métodos para medir o desempenho de GPU. Esta é uma classe derivada de ICarenD3D11Asynchronous.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um medidor de desempenho de GPU")]
		[Guid("5F66F518-FD6F-4C31-88EF-B1C537598A39")]
		public interface class ICarenD3D11Counter : ICarenD3D11Asynchronous
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém uma descrição do contador.
			/// </summary>
			/// <param name="Param_Out_DescContador">Retorna uma estrutura que descreve o contador atual.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_DESC_CONTADOR^% Param_Out_DescContador);
		};

		/// <summary>
		/// (ID3D11DepthStencilState) - É uma interface de estado de profundidade estêncil que contém uma descrição para o estado de profundidade-estêncil que você pode ligar para o estágio de saída-fusão.
		/// Para criar um objeto de estado de profundidade estêncil, chame o método ICarenD3D11Device::CriarDepthStencilState. Para vincular o objeto de estado de profundidade estêncil para o estágio de saída-fusão, chame o método 
		/// ICarenD3D11DeviceContext::OMDefinirDepthStencilState.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa o estado de profundidade estêncil que contém uma descrição para o (Depth-Stencil).")]
		[Guid("B6E5942B-D4D6-4692-9090-39EB562BDC83")]
		public interface class ICarenD3D11DepthStencilState : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a descrição para o estado de profundidade-estêncil que você usou para criar o objeto de profundidade-estêncil-estado.
			/// </summary>
			/// <param name="Param_Out_DescEstadoStencil">Retorna uma estrutura que contém a descrição do estado de profundidade estêncil usado.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_Out_DescEstadoStencil);
		};

		/// <summary>
		/// (ID3D11DepthStencilView) - Uma interface de (visualização de estêncil de profundidade) acessa um recurso de textura durante o teste de estêncil de profundidade.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Acessa um recurso de textura durante um teste de profundidade estência(Depth-Stencil).")]
		[Guid("272D89C1-1256-4B67-A410-0D03BDB3FBC5")]
		public interface class ICarenD3D11DepthStencilView : ICarenD3D11View
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a visão de profundidade-estêncil.
			/// Para criar uma exibição de profundidade-estêncil, chame o método ICarenD3D11Device::CriarDepthStencilView.
			/// Para vincular uma visão de profundidade - estêncil para o pipeline, chamada ICarenD3D11DeviceContext::OMDefinirRenderTargets.
			/// </summary>
			/// <param name="Param_Out_DescViewStencil">Retorna uma estrutura que contém a descrição da visão de profundidade estêncil.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_Out_DescViewStencil);
		};

		/// <summary>
		/// (ID3D11RenderTargetView) - Uma interface de exibição-render-alvo identifica os sub-recursos render-alvo que podem ser acessados durante o processamento.
		/// Um RenderTarget é um recurso que pode ser gravado pelo estágio de saída-fusão no final de um passe de render. Cada alvo processado também deve ter uma visão de profundidade-estêncil correspondente.
		/// Para criar uma exibição de destino de processamento, chamada ICarenD3D11Device::CriarRenderTargetView. Para associar um modo de exibição de destino de processamento pipeline, chame o método 
		/// ICarenD3D11DeviceContext::OMSetRenderTargets.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um destino de renderização alvo.")]
		[Guid("EF960687-1261-490A-83DB-EB0242448F14")]
		public interface class ICarenD3D11RenderTargetView : ICarenD3D11View
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém as propriedades de uma exibição de destino de render.
			/// </summary>
			/// <param name="Param_Out_DescRenderDestino">Retorna uma estrutura que contém a descrição de exibição de destino do Render.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^% Param_Out_DescRenderDestino);
		};

		/// <summary>
		/// (ID3D11RenderTargetView1) - Uma interface de exibição-render-alvo identifica os sub-recursos render-alvo que podem ser acessados durante o processamento.
		/// Um RenderTarget é um recurso que pode ser gravado pelo estágio de saída-fusão no final de um passe de render. Cada alvo processado também deve ter uma visão de profundidade-estêncil correspondente.
		/// Para criar uma exibição de destino de processamento, chamada ICarenD3D11Device3::CriarRenderTargetView1. Para associar um modo de exibição de destino de processamento pipeline, chame o método 
		/// ICarenD3D11DeviceContext::OMSetRenderTargets.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um destino de renderização alvo.")]
		[Guid("E24326AA-8BCC-409E-85B3-9240A181744F")]
		public interface class ICarenD3D11RenderTargetView1 :ICarenD3D11RenderTargetView
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos.

			/// <summary>
			/// (GetDesc1) - Obtém as propriedades de uma exibição de destino de render.
			/// </summary>
			/// <param name="Param_Out_DescRenderDestino">Retorna uma estrutura que contém a descrição de exibição de destino do Render.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC1^% Param_Out_DescRenderDestino);
		};

		/// <summary>
		/// (ID3D11UnorderedAccessView) - Interface de exibição que especifica as partes de um recurso que o gasoduto pode acessar durante o processamento.
		/// Para criar uma visão para um recurso de acesso não-ordenada, chame o método ICarenD3D11Device::CriarVisãoRecursoAcessoNaoOrdenado.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Visão de acesso não ordenada representa as partes de um recurso que o pipeline pode acessar durante a renderização.")]
		[Guid("C2C20D02-E15A-44AF-8D33-5B13E3F4B80F")]
		public interface class ICarenD3D11UnorderedAccessView : ICarenD3D11View
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém uma descrição do recurso.
			/// </summary>
			/// <param name="Param_Out_DescRecurso">Retorna uma estrutura que contém a descrição de um recurso de visualização não ordenado.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_Out_DescRecurso);
		};

		/// <summary>
		/// (ID3D11UnorderedAccessView1) - Interface de exibição que especifica as partes de um recurso que o gasoduto pode acessar durante o processamento.
		/// Para criar uma visão para um recurso de acesso não-ordenada, chame o método ICarenD3D11Device3::CriarVisaoRecursoAcessoNaoOrdenado1.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Visão de acesso não ordenada representa as partes de um recurso que o pipeline pode acessar durante a renderização.")]
		[Guid("38FA8027-FEB5-467E-B2B7-C8E487E77B3F")]
		public interface class ICarenD3D11UnorderedAccessView1 : ICarenD3D11UnorderedAccessView
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos


			/// <summary>
			/// (GetDesc1) - Obtém uma descrição do recurso.
			/// </summary>
			/// <param name="Param_Out_DescRecurso">Retorna uma estrutura que contém a descrição de um recurso de visualização não ordenado.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^% Param_Out_DescRecurso);
		};

		/// <summary>
		/// (ID3D11SamplerState) - A interface do amostrador-Estado detém uma descrição para o estado de amostra que você pode ligar para qualquer estágio de sombreador do gasoduto(Graphics Pipeline) para referência por operações 
		/// de amostra de textura.
		/// Para criar um objeto amostrador-estado, chame o método ICarenD3D11Device::CriarSamplerState.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um amostrador-Estado que contém uma descrição para o estado de amostra ligada em um estágio do sombreador.")]
		[Guid("858230B7-F03E-4715-8A55-E174684F1598")]
		public interface class ICarenD3D11SamplerState : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a descrição para o estado de amostra que você usou para criar o objeto de estado amostrador.
			/// </summary>
			/// <param name="Param_Out_DescAmostrador">Retorna uma estrutura que contém a descrição do amostrador.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_SAMPLER_DESC^% Param_Out_DescAmostrador);
		};

		/// <summary>
		/// (ID3D11ShaderResourceView1) - Uma interface de ShaderResourceView especifica os subrecursos que um sombreador pode acessar durante a 
		/// renderização. Exemplos de recursos sombreadores incluem um buffer constante, um buffer de textura e uma textura.
		/// Para criar uma visualização de recursos de sombreadores, chame o método  ICarenD3D11Device::CriarVisualizadoRescursoShader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um subrecurso que um sombreador pode acessar.")]
		[Guid("F8FF9012-B8A1-469C-A278-1BBDDB366110")]
		public interface class ICarenD3D11ShaderResourceView : ICarenD3D11View
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a descrição do sombreador de recurso do modo de exibição.
			/// </summary>
			/// <param name="Param_Out_DescSombreadorRecurso">Retorna uma estrutura que contém a descrição do sobreador de exbição de recuso.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_Out_DescSombreadorRecurso);
		};

		/// <summary>
		/// (ID3D11ShaderResourceView1) - Uma interface de ShaderResourceView especifica os subrecursos que um sombreador pode acessar durante a 
		/// renderização. Exemplos de recursos sombreadores incluem um buffer constante, um buffer de textura e uma textura.
		/// Para criar uma visualização de recursos de sombreadores, chame o método  ICarenD3D11Device3::CriarVisualizadoRescursoShader1.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um subrecurso que um sombreador pode acessar.")]
		[Guid("812B0E84-BB67-41E0-BD90-40ABF3BDD1AC")]
		public interface class ICarenD3D11ShaderResourceView1 : ICarenD3D11ShaderResourceView
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtém a descrição do sombreador de recurso do modo de exibição.
			/// </summary>
			/// <param name="Param_Out_DescSombreadorRecurso">Retorna uma estrutura que contém a descrição do sobreador de exbição de recuso.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^% Param_Out_DescSombreadorRecurso);
		};

		/// <summary>
		/// (ID3D11PixelShader) - Uma interface de pixel-shader gerencia um programa executável (um sombreador de pixel) que controla o estágio de sombreador de pixel.
		/// A interface de pixel-shader tem não métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores em são aplicadas a partir de um conjunto comum de características referidas 
		/// como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de sombreamento de pixel.")]
		[Guid("191FB8C2-D346-40D6-8590-E215681AA77A")]
		public interface class ICarenD3D11PixelShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11Predicate) - Uma interface de predicado que determina se a geometria deve ser processada dependendo dos resultados de uma chamada de desenho anterior.
		/// Existem dois tipos de predicados: fluxo de estouro de saída de predicados e predicados de oclusão. Predicados de fluxo de estouro de sáida causam qualquer geometria que residem nos buffers de fluxo de saída que 
		/// foram transbordaram para não ser processado. Predicados de oclusão causam qualquer geometria que não tinha uma única amostra passar os testes de profundidade/estêncil para não serem processados.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de processamento de geometrias.")]
		[Guid("366AFE2C-D22D-44F5-8CDC-0BB6CC8E1A79")]
		public interface class ICarenD3D11Predicate : ICarenD3D11Query
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11RasterizerState) - A interface do rasterizador-Estado detém uma descrição para o rasterizador de estado que você pode ligar para o rasterizador de palco.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um rasterizador de estado(RasterizerState).")]
		[Guid("523852A4-D4B1-4B49-88CD-B7F17EEE9DDA")]
		public interface class ICarenD3D11RasterizerState : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
			/// </summary>
			/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_Out_DescRasterizador);
		};

		/// <summary>
		/// (ID3D11RasterizerState1) - A interface do rasterizador-Estado detém uma descrição para o rasterizador de estado que você pode ligar para o rasterizador de palco.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um rasterizador de estado(RasterizerState).")]
		[Guid("41B8C43A-A011-49EC-AB5B-0E155837E815")]
		public interface class ICarenD3D11RasterizerState1 : ICarenD3D11RasterizerState
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
			/// </summary>
			/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizador);
		};

		/// <summary>
		/// (ID3D11RasterizerState2) - A interface do rasterizador-Estado detém uma descrição para o rasterizador de estado que você pode ligar para o rasterizador de palco.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um rasterizador de estado(RasterizerState).")]
		[Guid("1A82D929-D807-453E-9B31-063684210319")]
		public interface class ICarenD3D11RasterizerState2 : ICarenD3D11RasterizerState1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetDesc2) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
			/// </summary>
			/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
			CarenResult ObterDescrição2([Out] Estruturas::CA_D3D11_RASTERIZER_DESC2^% Param_Out_DescRasterizador);
		};

		/// <summary>
		/// (ID3D11VertexShader) - Uma interface de sombreador de vértices gerencia um programa executável (um sombreador de vértices) que controla o estágio de sombreador de vértices.
		/// A interface de sombreador de vértices tem não métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores são aplicadas a partir de um conjunto comum de características 
		/// referidas como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de sombreamento de vertice(Vertex)")]
		[Guid("60D8DB27-B58F-48CC-A939-60744EA137A4")]
		public interface class ICarenD3D11VertexShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11DomainShader) - Interface de domínio-shader gerencia um programa executável (um sombreador de domínio) que controla a fase de domínio-shader.
		/// A interface de domínio-shader tem não métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores são aplicadas a partir de um conjunto comum de características referidas como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de sombreamento de domínio(Domain)")]
		[Guid("EC3EDB9C-323C-452D-9111-733267861A29")]
		public interface class ICarenD3D11DomainShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11GeometryShader) - Interface de geometria-shader gerencia um programa executável (um sombreador de geometria) que controla o estágio de geometria-shader.
		/// A interface de geometria-shader tem não métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores são aplicadas a partir de um conjunto comum de características referidas como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de sombreamento de geometria(Geometry)")]
		[Guid("27A2ABDF-DB9D-4B90-B58D-5105B5E62339")]
		public interface class ICarenD3D11GeometryShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11HullShader) - Uma interface de casco-shader gerencia um programa executável (um sombreador de casco) que controla o estágio de casco-shader.
		/// A interface de Hull-Shader tem não métodos; Use HLSL para implementar a funcionalidade de sombreador. Todos os sombreadores são aplicadas a partir de um conjunto comum de características referidas como o núcleo comum-shader.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de sombreamento de casco(Hull)")]
		[Guid("637F96F8-1F75-4A3F-ABC5-4A44795AD6FC")]
		public interface class ICarenD3D11HullShader : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11InputLayout) - Interface de layout de entrada contém uma definição de como alimentar dados de vértice que são colocados para fora na memória no (Input-Assembler Stage) do pipeline de gráficos.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um layout de entrada.")]
		[Guid("C93436FD-AEBA-4A42-B32B-66640C16A88A")]
		public interface class ICarenD3D11InputLayout : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID3D11CommandList) - Interface responsável por encapsular uma lista de comandos gráficos para reprodução.
		/// Não há nenhum método de criação explícita, simplesmente declarar uma interface ICarenD3D11CommandList, em seguida, chamar o ICarenD3D11DeviceContext::FinCommandList para gravar comandos ou ICarenD3D11DeviceContext::ExecuteCommandList 
		/// para reproduzir comandos.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma interface de lista de comandos gráficos.")]
		[Guid("6EFF8E15-F195-45CB-ACAB-C3270F0C4A41")]
		public interface class ICarenD3D11CommandList : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetContextFlags) - Obtém os sinalizadores de inicialização associados ao contexto diferido que criou a lista de comandos.
			/// </summary>
			/// <param name="Param_Out_SinalizadoresContexto">Retorna os sinalizadores de contexto. 
			/// Atenção: O sinalizador de contexto é reservado para uso futuro e é sempre 0.</param>
			CarenResult ObterFlagsContexto([Out] UInt32% Param_Out_SinalizadoresContexto);
		};

		/// <summary>
		/// (ID3DDeviceContextState) - Interface responsável por representar um objeto de estado de contexto, que contém informações de estado e comportamento sobre um dispositivo 
		/// Microsoft Direct3D.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um objeto de estado de contexto.")]
		[Guid("833B07E5-E209-4164-977C-2C2CA0D7BBDD")]
		public interface class ICarenD3DDeviceContextState : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//NAO POSSUI MÉTODOS!
		};

		/// <summary>
		/// (ID3D11DeviceContext) - A interface representa um contexto de dispositivo que gera comandos de renderização.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por gerar comandos de Renderização.")]
		[Guid("8526B1B8-8FB8-4AE6-9E8E-A27A249F8A81")]
		public interface class ICarenD3D11DeviceContext : ICarenD3D11DeviceChild
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (Begin) - Marca o início de uma série de comandos.
			/// </summary>
			/// <param name="Param_Async">Um ponteiro para a interface de sincronização.</param>
			CarenResult Begin(ICarenD3D11Asynchronous^ Param_Async);

			/// <summary>
			/// (ClearDepthStencilView) - Limpa o recurso de profundidade-estêncil.
			/// </summary>
			/// <param name="Param_DepthStencil">Ponteiro para o estêncil de profundidade a ser apurados.</param>
			/// <param name="Param_ClearFlags">Identifica o tipo de dados para limpar </param>
			/// <param name="Param_Depth">Limpe o buffer de profundidade com esse valor. Este valor irá ser fixada entre 0 e 1.</param>
			/// <param name="Param_Stencil">Limpe o buffer de estêncil com esse valor.</param>
			CarenResult LimparDepthStencilView(
				ICarenD3D11DepthStencilView^ Param_DepthStencil,
				Enumeracoes::CA_D3D11_CLEAR_FLAG Param_ClearFlags,
				float Param_Depth,
				Byte Param_Stencil);

			/// <summary>
			/// (ClearRenderTargetView) - Defina todos os elementos em um destino de processamento para um valor.
			/// </summary>
			/// <param name="Param_RenderTarget">Ponteiro para o destino de processamento.</param>
			/// <param name="Param_Cor">Uma estrutura de 4 componentes que representam a cor para preencher o destino de processamento.</param>
			CarenResult ClearRenderTargetView(
				ICarenD3D11RenderTargetView^ Param_RenderTarget,
				Estruturas::CA_DXGI_RGBA^ Param_Cor);

			/// <summary>
			/// (ClearState) - Restaure todas as configurações padrão. 
			/// </summary>
			CarenResult RestaurarConfiguracoesDefault();

			/// <summary>
			/// (ClearUnorderedAccessViewFloat) - Limpa um recurso de acesso não ordenada, com um valor float.
			/// Essa API funciona em FLOAT, UNORM e SNORM não ordenada acesso visualizações (UAVs), com formato de conversão de FLOAT para * norma se for caso disso. Em outros UAVs, a operação é inválida e a chamada 
			/// não atingirá o driver.
			/// </summary>
			/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
			/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
			CarenResult LimparRecursoNaoOrdenadoFloat(
				ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
				cli::array<float>^ Param_Valores);

			/// <summary>
			/// (ClearUnorderedAccessViewUint) - Limpa um recurso de acesso não ordenada com valores de bit de precisão.
			/// Essa API copia o menor n bits de cada elemento da matriz para o correspondente canalizo, onde n é o número de bits no canal ith do formato de recurso (por exemplo, R8G8B8_FLOAT tem 8 bits para os 3 
			/// primeiros canais). Isto funciona em qualquer UAV com nenhuma conversão de formato. Para uma visão de buffer CRU ou estruturados, somente o primeiro valor de elemento matriz é usado.
			/// </summary>
			/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
			/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
			CarenResult LimparRecursoNaoOrdenadoUint(
				ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
				cli::array<UInt32>^ Param_Valores);

			/// <summary>
			/// (CopyResource) - Copie todo o conteúdo do recurso de fonte para o recurso de destino usando o GPU.
			/// </summary>
			/// <param name="Param_DestinoRecurso">Um ponteiro para a interface ID3D11Resource que representa o DESTINO do recurso.</param>
			/// <param name="Param_OrigemRecurso">Um ponteiro para a interface ID3D11Resource que representa a FONTE de recursos.</param>
			CarenResult CopiarRecurso(
				ICarenD3D11Resource^ Param_DestinoRecurso,
				ICarenD3D11Resource^ Param_OrigemRecurso);

			/// <summary>
			/// (CopyStructureCount) - Copia dados de um buffer de dados de comprimento variável a segurar.
			/// </summary>
			/// <param name="Param_DestinoBuffer">Ponteiro para ID3D11Buffer. Isso pode ser qualquer recurso de buffer que outros comandos de cópia, tais como ICarenD3D11DeviceContext::CopiarRecurso ou 
			/// ICarenD3D11DeviceContext::CopiarSubRecursoRegiao, são capazes de gravar.</param>
			/// <param name="Param_DestinoAlignedOffsetByte">Offset do início do Param_DestinoBuffer para gravar contagem de estrutura(vértice) UINT 32 bits de Param_OrigemView.</param>
			/// <param name="Param_OrigemView">Ponteiro para um ID3D11UnorderedAccessView de um recurso de Buffer estruturado criado com D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER especificado 
			/// quando o UAV foi criado. Esses tipos de recursos têm contadores ocultos rastreando "quantos" registros foram escritos.</param>
			CarenResult CopiarStructureCount(
				ICarenD3D11Buffer^ Param_DestinoBuffer,
				UInt32 Param_DestinoAlignedOffsetByte,
				ICarenD3D11UnorderedAccessView^ Param_OrigemView);

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
			CarenResult CopiarSubRecursoRegiao(
				ICarenD3D11Resource^ Param_DestinoRecurso,
				UInt32 Param_IndiceSubrecrusoDestino,
				UInt32 Param_DestX,
				UInt32 Param_DestY,
				UInt32 Param_DestZ,
				ICarenD3D11Resource^ Param_FonteRecurso,
				UInt32 Param_IndiceSubrecrusoFonte,
				Estruturas::CA_D3D11_BOX^ Param_OrigemBox
			);

			/// <summary>
			/// (CSGetConstantBuffers) - Obtém os buffers constantes usados pelo estágio de computação do Shader(Sombreamento).
			/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar IUnknown:: Release sobre as interfaces retornadas quando eles não são mais necessários 
			/// para evitar vazamentos de memória.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumerosBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_BuffersConstantes">Recebe uma matriz com os ponteiros para os buffers constantes.</param>
			CarenResult CSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumerosBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_BuffersConstantes);

			/// <summary>
			/// (CSGetSamplers) - Obtém uma variedade de interfaces de estado do amostrador desde a fase de computação-shader. 
			/// </summary>
			/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroSamplers">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
			/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot).</param>
			/// <param name="Param_Out_SamplersState">Recebe uma matriz com os ponteiros para os amostradores de estado(Samplers States).</param>
			CarenResult CSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroSamplers,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_SamplersState);

			/// <summary>
			/// (CSGetShader) - Se o sombreador de computação atualmente definido no dispositivo.
			/// </summary>
			/// <param name="Param_Out_ComputeShader">Retorna uma ponteiro para a interface de Shader Compute.</param>
			/// <param name="Param_Out_ArrayClassInstance">Retorna um Array que contém ponteiros para Instâncias de Classe.</param>
			/// <param name="Param_Out_QuantidadeClass">Retorna a quantidade de itens no array do parametro (Param_Out_ArrayClassInstance).</param>
			CarenResult CSObterShader(
				[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_ArrayClassInstance,
				[Out] UInt32% Param_Out_QuantidadeClass);

			/// <summary>
			/// (CSGetShaderResources) - Obter os recursos de computação-shader.
			/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
			/// necessários para evitar vazamentos de memória.
			/// </summary>
			/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
			/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizShaderRecursoSombreador">Retorna uma Matriz com ponteiros de exibição de recurso de sombreador retornado pelo Dispositivo.</param>
			CarenResult CSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroRecursos,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizShaderRecursoSombreador);

			/// <summary>
			/// (CSGetUnorderedAccessViews) - Obtém uma matriz de pontos de vista de um recurso não-ordenado.
			/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
			/// necessários para evitar vazamentos de memória.
			/// </summary>
			/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para retornar (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroUAVs">Número de pontos de vista para obter (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizInterfacesNaoOrdenadas">Retorna uma Matriz que contém ponteiros para as interfaces ID3D11UnorderedAccessView.</param>
			CarenResult CSObterUnorderedAccessViews(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroUAVs,
				[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizInterfacesNaoOrdenadas);

			/// <summary>
			/// (CSSetConstantBuffers) - Define os constantes buffers usados pela fase computação-shader.
			/// O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
			/// Se o aplicativo deseja o sombreador para acessar outras partes da reserva, ele deve chamar o método CSDefinirConstantBuffers1 em vez disso.
			/// </summary>
			/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
			CarenResult CSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (CSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de computação-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroSamplers">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
			/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizSamplers">Uma matriz de interfaces do amostrador de estado a serem definidas no dispositivo.</param>
			CarenResult CSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroSamplers,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizSamplers);

			/// <summary>
			/// (CSSetShader) - Defina um sombreador de computação para o dispositivo.
			/// O número máximo de instâncias que pode ter um sombreador é 256.
			/// </summary>
			/// <param name="Param_ComputeShader">Ponteiro para um sombreador de computação. Passando NULO (DESABILITA) o sombreador para este estágio de pipeline.</param>
			/// <param name="Param_MatrizClassInstance">Um ponteiro para uma matriz que contem as interfaces de instâncias de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader 
			/// vai ser desativado. Definir Param_MatrizClassInstance para NULO se o sombreador não usa quaisquer interfaces.</param>
			/// <param name="Param_QuantidadeClassInstances">A quantidade de itens no array do parametro (Param_MatrizClassInstance).</param>
			CarenResult CSDefinirShader(
				ICarenD3D11ComputeShader^ Param_ComputeShader,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizClassInstance,
				UInt32 Param_QuantidadeClassInstances);

			/// <summary>
			/// (CSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de computação-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
			/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot).</param>
			/// <param name="Param_MatrizShaderRecursoSombreador">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
			CarenResult CSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroRecursos,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizShaderRecursoSombreador);

			/// <summary>
			/// (CSSetUnorderedAccessViews) - Define uma matriz de pontos de vista para um recurso não-ordenada.
			/// </summary>
			/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para começar a configuração (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1). D3D11_1_UAV_SLOT_COUNT é definido como 64.</param>
			/// <param name="Param_NumeroUAVs">Número de pontos de vista para definir (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizInterfacesNaoOrdenadas">Um ponteiro para uma matriz de ponteiros de ID3D11UnorderedAccessView a ser definido pelo método.</param>
			/// <param name="Param_MatrizInitialUAVsCount">Uma matriz de acrescentar e consumir deslocamentos de reserva. Um valor de -1 indica que para manter o atual deslocamento. Quaisquer outros valores definir o 
			/// contador oculto para aquele UAV (APPENDABLE) e consumíveis. Param_MatrizInitialUAVsCount só é relevante para UAVs que foram criados com qualquer D3D11_BUFFER_UAV_FLAG_APPEND ou 
			/// D3D11_BUFFER_UAV_FLAG_COUNTER especificado quando o UAV foi criado; caso contrário, o argumento é ignorado.</param>
			CarenResult CSDefinirUnorderedAccessViews(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroUAVs,
				cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizInterfacesNaoOrdenadas,
				cli::array<UInt32>^ Param_MatrizInitialUAVsCount);

			/// <summary>
			/// (Dispatch) - Execute uma lista de comando de um grupo de discussão.
			/// </summary>
			/// <param name="Param_NumeroGrupoExpedidoX">O número de grupos expedidos na direção X. NumeroGrupoExpedidoX deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
			/// <param name="Param_NumeroGrupoExpedidoY">O número de grupos expedidos na direção Y. NumeroGrupoExpedidoY deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
			/// <param name="Param_NumeroGrupoExpedidoZ">O número de grupos expedidos na direção Z. NumeroGrupoExpedidoZ deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535). 
			/// Em nível de recurso 10 o valor para NumeroGrupoExpedidoZ deve ser 1.</param>
			CarenResult Despacho(
				UInt32 Param_NumeroGrupoExpedidoX,
				UInt32 Param_NumeroGrupoExpedidoY,
				UInt32 Param_NumeroGrupoExpedidoZ);

			/// <summary>
			/// (DispatchIndirect) - Execute uma lista de comando por um ou mais grupos de discussão.
			/// Você chamar este método para executar comandos em um (Compute Shader).
			/// </summary>
			/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que deve ser carregado com os dados que corresponde à lista de argumento para ICarenD3D11DeviceContext::Despacho.</param>
			/// <param name="Param_AlinhamentoBytesOffsetForArgs">Um deslocamento de byte alinhado entre o início do buffer e os argumentos.</param>
			CarenResult DespachoIndireto(
				ICarenD3D11Buffer^ Param_BufferForArgs,
				UInt32 Param_AlinhamentoBytesOffsetForArgs);

			/// <summary>
			/// (Draw) - Desenhe não-indexados, instância não primitivos.
			/// O Draw envia trabalhos para o pipeline de renderização. Os dados de vértice para uma chamada de desenho normalmente vêm de um buffer de vértice que está vinculado ao pipeline. Mesmo sem qualquer buffer 
			/// de vértices vinculado ao pipeline, você pode gerar seus próprios dados de vértice em seu sombreador de vértice usando a semântica do valor do sistema SV_VertexID para determinar o vértice atual que o 
			/// tempo de execução está processando.
			/// </summary>
			/// <param name="Param_NumeroVertices">Número de vértices para desenhar.</param>
			/// <param name="Param_LocalizacaoVertice">Índice do primeiro vértice, que é geralmente um deslocamento em um buffer de vértice.</param>
			CarenResult Desenhar(
				UInt32 Param_NumeroVertices,
				UInt32 Param_LocalizacaoVertice);

			/// <summary>
			/// (DrawAuto) - Desenhe a geometria de um tamanho desconhecido.
			/// Uma API de desenho envia trabalho para o pipeline de renderização. Esta API submete o trabalho de um tamanho desconhecido que foi processado pelos estágios montador de entrada, sombreador de vértice e 
			/// fluxo-saída; o trabalho pode ou não ter passado pelo estágio de sombreamento de geometria.
			/// </summary>
			CarenResult DesenharAuto();

			/// <summary>
			/// (DrawIndexed) - Sorteio indexado, não-instanced primitivos.
			/// Se a soma dos dois índices é negativa, o resultado da chamada de função é indefinido.
			/// </summary>
			/// <param name="Param_NumeroIndices">Número de índices para desenhar.</param>
			/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
			/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
			CarenResult DesenharIndexado(
				UInt32 Param_NumeroIndices,
				UInt32 Param_StartIndexLocalizacao,
				Int32 Param_BaseVerticeLocalizacao);

			/// <summary>
			/// (DrawIndexedInstanced) - Desenhe indexados, instanciados primitivos.
			/// </summary>
			/// <param name="Param_QuantidadeIndicesPorInstnacia">Número de índices de ler o buffer de índice para cada instância.</param>
			/// <param name="Param_QuantidadeInstnacias">Número de instâncias para desenhar.</param>
			/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
			/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
			/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>
			CarenResult DesenharIndexadoInstaciado(
				UInt32 Param_QuantidadeIndicesPorInstnacia,
				UInt32 Param_QuantidadeInstnacias,
				UInt32 Param_StartIndexLocalizacao,
				Int32 Param_BaseVerticeLocalizacao,
				UInt32 Param_StartInstanciaLocalizacao);

			/// <summary>
			/// (DrawIndexedInstancedIndirect) - Desenhe primitivos indexados, instanciado, gerado pelo GPU.
			/// </summary>
			/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
			/// <param name="Param_AlinhamentoBytesOffsetForArgs">Deslocamento em Param_BufferForArgs para o início da GPU gerado primitivos.</param>
			CarenResult DesenharIndexadoInstaciadoIndireto(
				ICarenD3D11Buffer^ Param_BufferForArgs,
				UInt32 Param_AlinhamentoBytesOffsetForArgs);

			/// <summary>
			/// (DrawInstanced) - Desenhe não-indexados, instanciado primitivos.
			/// Instância pode prolongar o desempenho, reutilizando a mesma geometria para desenhar vários objetos em uma cena. Um exemplo de criação de instância pode ser desenhar o mesmo objeto com posições 
			/// diferentes e cores.
			/// </summary>
			/// <param name="Param_QuantidadeVerticiesPorInstnacia">Número de vértices para desenhar.</param>
			/// <param name="Param_QuantidadeInstnacias">Número de instâncias para desenhar.</param>
			/// <param name="Param_StartVerticeLocalizacao">Índice do primeiro vértice.</param>
			/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>			
			CarenResult DesenharInstanciado(
				UInt32 Param_QuantidadeVerticiesPorInstnacia,
				UInt32 Param_QuantidadeInstnacias,
				UInt32 Param_StartVerticeLocalizacao,
				UInt32 Param_StartInstanciaLocalizacao);

			/// <summary>
			/// (DrawInstancedIndirect) - Desenhe primitivos instanciado, gerado pelo GPU.
			/// </summary>
			/// <param name="Param_BufferDadosPrimitivos">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
			/// <param name="Param_DeslocamentoDados">Deslocamento em (Param_BufferDadosPrimitivos) para o início da GPU gerado primitivos.</param>
			CarenResult DesenharInstanciadoIndiretamente(
				ICarenD3D11Buffer^% Param_BufferDadosPrimitivos,
				UInt32 Param_DeslocamentoDados);

			/// <summary>
			/// (DSGetConstantBuffers) - Obtém os buffers constantes usados por fase de domínio-shader.
			/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
			CarenResult DSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (DSGetSamplers) - Obtém uma variedade de interfaces de estado amostrador desde a fase de domínio-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_Amostradores">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
			/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizAmostradoresEstado">Uma matriz para as interfaces com amostradores de estado.</param>
			CarenResult DSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_Amostradores,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizAmostradoresEstado);

			/// <summary>
			/// (DSGetShader) - Se o sombreador de domínio atualmente definido no dispositivo.
			/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
			/// </summary>
			/// <param name="Param_Out_SombreadorDominio">Retorna a interface para o sombreador de dominio.</param>
			/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz que contém interface de instâncias de classe.</param>
			/// <param name="Param_Out_ElementosMatriz">Retorna a quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
			CarenResult DSObterShader(
				[Out] ICarenD3D11DomainShader^% Param_Out_SombreadorDominio,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
				[Out] UInt32% Param_Out_ElementosMatriz);

			/// <summary>
			/// (DSGetShaderResources) - Obter os recursos de domínio-shader. 
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_QuantidadeRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
			/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador a ser retornado pelo dispositivo.</param>
			CarenResult DSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_QuantidadeRecursos,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizRecursoShader);

			/// <summary>
			/// (DSSetConstantBuffers) - Define os constantes buffers usados pela fase de domínio-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
			CarenResult DSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (DSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de domínio-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Indice na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_Amostradores">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
			/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces amostrador-estado a ser dado ao dispositivo.</param>
			CarenResult DSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_Amostradores,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

			/// <summary>
			/// (DSSetShader) - Defina um sombreador de domínio para o dispositivo.
			/// </summary>
			/// <param name="Param_SombreadorDominio">Ponteiro para um sombreador de domínio. Passando NULO desabilita o sombreador para este estágio de pipeline.</param>
			/// <param name="Param_MatrizInstanciasClasse">Um ponteiro para uma matriz de instância da classe interfaces. Cada interface usada por um sombreador deve ter uma instância de 
			/// classe correspondente ou o shader vai ser desativado. Definir Param_MatrizInstanciasClasse para NULO se o sombreador não usa quaisquer interfaces.</param>
			/// <param name="Param_ElementosMatriz">A quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
			CarenResult DSDefinirShader(
				ICarenD3D11DomainShader^ Param_SombreadorDominio,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciasClasse,
				UInt32 Param_ElementosMatriz);

			/// <summary>
			/// (DSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de domínio-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_QuantidadeRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
			/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
			CarenResult DSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_QuantidadeRecursos,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizRecursoShader);

			/// <summary>
			/// (End) - Marca o fim de uma série de comandos.
			/// Use ICarenD3D11DeviceContext::Begin para marcar o início de uma série de comandos.
			/// </summary>
			/// <param name="Param_Async">Um ponteiro para uma interface de ID3D11Asynchronous .</param>
			CarenResult End(ICarenD3D11Asynchronous^ Param_Async);

			/// <summary>
			/// (ExecuteCommandList) - Comandos de filas de uma lista de comandos para um dispositivo.
			/// </summary>
			/// <param name="Param_FilaComandos">Um ponteiro para uma interface ID3D11CommandList que encapsula uma lista de comandos graficos.</param>
			/// <param name="Param_RestaurarEstadoContexto">Um sinalizador booleano que determina se o estado do contexto de destino é salvo antes e restaurado após a execução de uma lista de comandos. Use TRUE para indicar que o tempo de 
			/// execução precisa salvar e restaurar o estado. Use FALSE para indicar que nenhum estado deve ser salvo ou restaurado, o que faz com que o contexto de destino retorne ao seu estado padrão após a 
			/// execução da lista de comandos. Normalmente, os aplicativos devem usar FALSE, a menos que restaurem o estado para ser quase equivalente ao estado que o tempo de execução restauraria se TRUE fosse 
			/// passado. Quando os aplicativos usam FALSE , eles podem evitar transições de estado desnecessárias e ineficientes.</param>
			CarenResult ExecutarComandosLista(
				ICarenD3D11CommandList^ Param_FilaComandos,
				Boolean Param_RestaurarEstadoContexto);

			/// <summary>
			/// (FinishCommandList) - Crie um comando lista e registro gráficos comandos nele.
			/// </summary>
			/// <param name="Param_RestDeferidoEstadoContexto">Um sinalizador booleano que determina se o tempo de execução salva o estado de contexto adiado antes de executar FinishCommandList e restaurá-lo posteriormente. 
			/// Use TRUE para indicar que o tempo de execução precisa salvar e restaurar o estado. Use FALSE para indicar que o tempo de execução não salvará nem restaurará nenhum estado. Nesse caso, o contexto deferido 
			/// retornará ao seu estado padrão após a conclusão desta chamada. Para obter informações sobre o estado padrão, consulte ICarenD3D11DeviceContext::ClearState. Normalmente, use FALSE, a menos que você restaure 
			/// o estado para ser quase equivalente ao estado que o tempo de execução restauraria se você passasse por TRUE . Quando você usa FALSE, você pode evitar transições de estado desnecessárias e ineficientes.</param>
			/// <param name="Param_Out_FilaComandos">Retorna um ponteiro da interface ICarenD3D11CommandList que é inicializado com as informações da lista de comandos gravados. O objeto ICarenD3D11CommandList 
			/// resultante é imutável e só pode ser usado com ICarenD3D11DeviceContext::ExecutarListaComandos.</param>
			CarenResult TerminarComandosLista(
				Boolean Param_RestDeferidoEstadoContexto,
				[Out] ICarenD3D11CommandList^% Param_Out_FilaComandos);

			/// <summary>
			/// (Flush) - Envia comandos de cima enfileirado no buffer de comandos para a unidade de processamento gráfico (GPU).
			/// </summary>
			CarenResult Flush();

			/// <summary>
			/// (GenerateMips) - Gera mipmaps para o recurso de sombreador determinado.
			/// </summary>
			/// <param name="Param_RecursoSombreador">Um ponteiro para uma interface ICarenD3D11ShaderResourceView que representa o recurso de sombreador.</param>
			CarenResult GerarMipmaps(ICarenD3D11ShaderResourceView^ Param_RecursoSombreador);

			/// <summary>
			/// (GetContextFlags) - Obtém os sinalizadores de inicialização associados com o atual contexto diferido.
			/// </summary>
			/// <param name="Param_Out_ContextFlags">recebe as bandeiras que foram fornecidos à ContextFlags parâmetro de ICarenD3D11Device::CreateDeferredContext; no entanto, o sinalizador de contexto é reservado para 
			/// uso futuro.</param>
			CarenResult ObterContextFlags([Out] UInt32% Param_Out_ContextFlags);

			/// <summary>
			/// (GetData) - Obter dados a partir da unidade de processamento gráfico (GPU) de forma assíncrona.
			/// </summary>
			/// <param name="Param_Async">Um ponteiro para uma interface ICarenD3D11Asynchronous para o objeto sobre o qual (ObterDados) recupera dados.</param>
			/// <param name="Param_Dados">Ponteiro para uma interface de buffer que receberá os dados. Se NULO, (ObterDados) será usado apenas para verificar o estado. O tipo de saída de dados depende do tipo de interface assíncrona.</param>
			/// <param name="Param_TamanhoDados">Tamanho dos dados a serem recuperados ou 0. Deve ser 0 quando (Param_Dados) for NULO.</param>
			/// <param name="Param_FlagsGetData">Bandeiras opcionais. Pode ser 0 ou qualquer combinação das bandeiras enumeradas por CA_D3D11_ASYNC_GETDATA_FLAG.</param>
			CarenResult ObterDados(
				ICarenD3D11Asynchronous^ Param_Async,
				ICarenBuffer^% Param_Dados,
				UInt32 Param_TamanhoDados,
				Enumeracoes::CA_D3D11_ASYNC_GETDATA_FLAG Param_FlagsGetData);

			/// <summary>
			/// (GetPredication) - Obtém o estado do predicado de renderização.
			/// </summary>
			/// <param name="Param_Out_Predicado">Recebe um ponteiro para um predicado. O valor armazenado aqui será NULO na criação do dispositivo.</param> 
			/// <param name="Param_Out_ValuePredicado">Recebe um valor booleano para preencher o valor de comparação de predicado. FALSE na criação do dispositivo.</param>
			CarenResult ObterPredicado(
				[Out] ICarenD3D11Predicate^% Param_Out_Predicado,
				[Out] Boolean% Param_Out_ValuePredicado);

			/// <summary>
			/// (GetResourceMinLOD) - Obtém o mínimo nível de detalhe(LOD).
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para uma interface que representa um recurso.</param> 
			/// <param name="Param_Out_LODMinimo">Retorna o LOD minímo.</param> 
			CarenResult ObterResourceMinLOD(ICarenD3D11Resource^ Param_Recurso, [Out] float% Param_Out_LODMinimo);

			/// <summary>
			/// (GetType) - Obtém o tipo de contexto de dispositivo.
			/// </summary>
			/// <param name="Param_Out_ContextoDispositivo">Retorna as opções de contexto do dispositivo.</param> 
			CarenResult ObterTipo([Out] Enumeracoes::CA_D3D11_DEVICE_CONTEXT_TYPE% Param_Out_ContextoDispositivo);

			/// <summary>
			/// (GSGetConstantBuffers) - Se os buffers constantes usados pela fase geometria shader pipeline.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
			CarenResult GSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (GSGetSamplers) - Obtém uma variedade de interfaces de estado amostrador desde a fase de gasoduto de sombreamento de geometria.
			/// </summary>
			/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
			CarenResult GSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

			/// <summary>
			/// (GSGetShader) - Obtém o sombreador de geometria atualmente definido no dispositivo.
			/// </summary>
			/// <param name="Param_Out_SombreadorGeometria">Retorna uma interface para o sombreador de Geometria.</param>
			/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
			/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
			CarenResult GSObterShader(
				[Out] ICarenD3D11GeometryShader^% Param_Out_SombreadorGeometria,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
				[Out] UInt32% Param_Out_QuantidadeInstancias);

			/// <summary>
			/// (GSGetShaderResources) - Obtém os recursos de geometria obscuros.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
			CarenResult GSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (GSSetConstantBuffers) - Define os constantes buffers usados pela fase geometria shader pipeline.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
			CarenResult GSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (GSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline de sombreador geometria.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
			CarenResult GSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

			/// <summary>
			/// (GSSetShader) - Defina um sombreador de geometria para o dispositivo.
			/// </summary>
			/// <param name="Param_SombreadorGeometria">Ponteiro para um sombreador de Geometria. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
			/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
			/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
			CarenResult GSDefinirShader(
				ICarenD3D11GeometryShader^ Param_SombreadorGeometria,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
				UInt32 Param_NumeroInstanciasClasse);

			/// <summary>
			/// (GSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreamento de geometria.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
			CarenResult GSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (HSGetConstantBuffers) - Se os buffers constantes usados pela fase casco-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
			CarenResult HSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (HSGetSamplers) - Obtém uma variedade de interfaces de estado amostrador desde a fase de casco-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
			CarenResult HSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

			/// <summary>
			/// (HSGetShader) - Obtém o Sombreador de Casco atualmente definido no dispositivo.
			/// </summary>
			/// <param name="Param_Out_SombreadorCasco">Retorna uma interface para o Sombreador de Casco.</param>
			/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
			/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
			CarenResult HSObterShader(
				[Out] ICarenD3D11HullShader^% Param_Out_SombreadorCasco,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
				[Out] UInt32% Param_Out_QuantidadeInstancias);

			/// <summary>
			/// (HSGetShaderResources) - Obtém os recursos do sombreador de casco(Hull).
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
			CarenResult HSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (HSSetConstantBuffers) - Defina os constantes buffers usados pelo palco casco-shader.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
			CarenResult HSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (HSSetSamplers) - Defina uma matriz de Estados do amostrador para a fase de sombreamento de casco(Hull).
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
			CarenResult HSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

			/// <summary>
			/// (HSSetShader) - Defina um sombreador de casco para o dispositivo.
			/// </summary>
			/// <param name="Param_SombreadorCasco">Ponteiro para um Sombreador de Casco(Hull). Passar em NULO desativa o shader para este estágio de pipeline.</param>  
			/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
			/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
			CarenResult HSDefinirShader(
				ICarenD3D11HullShader^ Param_SombreadorCasco,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
				UInt32 Param_NumeroInstanciasClasse);

			/// <summary>
			/// (HSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreamento de casco(Hull).
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
			CarenResult HSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (IAGetIndexBuffer) - Obter um ponteiro para o buffer de índice que é vinculado à fase de entrada-montador.
			/// </summary>
			/// <param name="Param_Out_Buffer">Retorna um ponteiro para o buffer.</param>
			/// <param name="Param_Out_Formato">Retorna uma especificação do formato dos dados no buffer de índice. Esses formatos oferecem o tamanho e o tipo de dados no buffer. Os formatos só permitidos para dados 
			/// de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
			/// <param name="Param_Out_Deslocamento">Retorna o Deslocamento(Offset) (em bytes) desde o início do buffer de índice, o primeiro índice para usar.</param>
			CarenResult IAObterIndexBuffer(
				[Out] ICarenD3D11Buffer^% Param_Out_Buffer,
				[Out] Enumeracoes::CA_DXGI_FORMAT% Param_Out_Formato,
				[Out] UInt32% Param_Out_Deslocamento);

			/// <summary>
			/// (IAGetInputLayout) - Obter um ponteiro para o objeto de entrada-layout que está vinculado para o estágio de entrada-montador.
			/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
			/// necessários para vitar vazamentos de memória.
			/// </summary>
			/// <param name="Param_Out_InputLayout">Reretorna um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
			CarenResult IAObterInputLayout([Out] ICarenD3D11InputLayout^% Param_Out_InputLayout);

			/// <summary>
			/// (IAGetPrimitiveTopology) - Obter informações sobre o tipo primitivo e a ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
			/// </summary>
			/// <param name="Param_Out_TipoPrimitivo"></param>
			CarenResult IAObterPrimitiveTopology([Out] Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY% Param_Out_TipoPrimitivo);

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
			CarenResult IAObterVertexBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizVertexBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizStrides,
				[Out] cli::array<UInt32>^% Param_Out_MatrizDeslocamentos);

			/// <summary>
			/// (IASetIndexBuffer) - Vincule um buffer do índice para o estágio de entrada-montador.
			/// </summary>
			/// <param name="Param_Buffer">Um ponteiro para um objeto ICarenD3D11Buffer, que contém os índices. O buffer do índice deve ter sido criado com o sinalizador D3D11_BIND_INDEX_BUFFER .</param>
			/// <param name="Param_Formato">Um CA_D3D11_DXGI_FORMAT que especifica o formato dos dados no buffer de índice. Os formatos só permitidos para dados de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
			/// <param name="Param_Deslocamento">Offset (em bytes) do início do buffer de índice para o primeiro índice para usar.</param>
			CarenResult IADefinirIndexBuffer(
				ICarenD3D11Buffer^ Param_Buffer,
				Enumeracoes::CA_DXGI_FORMAT Param_Formato,
				UInt32 Param_Deslocamento);

			/// <summary>
			/// (IASetInputLayout) - Vincule um objeto de layout de entrada para o estágio de entrada-montador.
			/// </summary>
			/// <param name="Param_InputLayout">Um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
			CarenResult IADefinirInputLayout(ICarenD3D11InputLayout^ Param_InputLayout);

			/// <summary>
			/// (IASetPrimitiveTopology) - Vincule informações sobre o tipo primitivo e ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
			/// </summary>
			/// <param name="Param_TipoPrimitivo">O tipo de primitivo e ordenação dos dados primitivos.</param>
			CarenResult IADefinirPrimitiveTopology(Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY Param_TipoPrimitivo);

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
			CarenResult IADefinirVertexBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizVertexBuffers,
				cli::array<UInt32>^ Param_MatrizStrides,
				cli::array<UInt32>^ Param_MatrizDeslocamentos);

			/// <summary>
			/// (map) - Obtém um ponteiro para os dados contidos em um sub-recurso e nega o acesso GPU para aquele sub-recurso.
			/// Esse método também retorna DXGI_ERROR_WAS_STILL_DRAWING se MapFlags especifica D3D11_MAP_FLAG_DO_NOT_WAIT e a GPU ainda não está terminado com o recurso.
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para uma interface de ID3D11Resource .</param>
			/// <param name="Param_IndiceSubRecurso">O Indice para o sub-recruso.</param>
			/// <param name="Param_PermissõesAcessoRecurso">Um D3D11_MAP valor digitado que especifica a CPU ler e escrever permissões para um recurso.</param>
			/// <param name="Param_MapFlags">Sinalizador que especifica que a CPU faz quando a GPU está ocupado. Este sinalizador é opcional. Define como (CA_D3D11_MAP_FLAG::Zero) para deixar como opcional.</param>
			/// <param name="Param_Out_RecrusoMapeado">Uma estrutura de CA_D3D11_MAPPED_SUBRESOURCE para o sub-recurso mapeado. Essa estrutura pode ser NULA as vezes. Consulte a documentação.</param>
			CarenResult Map(
				ICarenD3D11Resource^ Param_Recurso,
				UInt32 Param_IndiceSubRecurso,
				Enumeracoes::CA_D3D11_MAP Param_PermissõesAcessoRecurso,
				Enumeracoes::CA_D3D11_MAP_FLAG Param_MapFlags,
				[Out] Estruturas::CA_D3D11_MAPPED_SUBRESOURCE^% Param_Out_RecrusoMapeado);

			/// <summary>
			/// (OMGetBlendState) - Obtém o estado de mistura da fase de saída-fusão.
			/// </summary>
			/// <param name="Param_Out_EstadoMitura">Retorna um ponteiro para a interface de estado de mistura.</param>
			/// <param name="Param_Out_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA.</param>
			/// <param name="Param_Out_SampleMask">Retorna um valor para uma máscara de amostra.</param>
			CarenResult OMObterBlendState(
				[Out] ICarenD3D11BlendState^% Param_Out_EstadoMitura,
				[Out] cli::array<float>^% Param_Out_MatrizFatoresMistura,
				[Out] UInt32% Param_Out_SampleMask);

			/// <summary>
			/// (OMGetDepthStencilState) - Obtém o estado de profundidade-estêncil da fase de saída-fusão.
			/// </summary>
			/// <param name="Param_Out_DepthStencilState">Retorna um ponteiro para interface de estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
			/// <param name="Param_Out_StencilRef">Retorna um valor para um estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
			CarenResult OMObterDepthStencilState(
				[Out] ICarenD3D11DepthStencilState^% Param_Out_DepthStencilState,
				[Out] UInt32% Param_Out_StencilRef);

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
			CarenResult OMObterRenderTargets(
				UInt32 Param_NumeroViews,
				Boolean Param_IgnorarRecuperaçãoDestino,
				[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTargetViews,
				Boolean Param_IgnorarRecuperaçãoModoExibição,
				[Out] ICarenD3D11DepthStencilView^% Param_Out_DepthStencilView);

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
			CarenResult OMObterRenderTargetsAndUnorderedAccessViews(
				UInt32 Param_NumeroRTVs,
				Boolean Param_IgnorarRenderTargetView,
				[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTarget,
				Boolean Param_IgnorarDepthStencilView,
				[Out] ICarenD3D11DepthStencilView^ Param_Out_DepthStencilView,
				UInt32  Param_UAVStartSlot,
				UInt32  Param_NumeroUAVs,
				Boolean Param_IgnorarUnorderedAccessView,
				[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizUnorderedAccessViews);

			/// <summary>
			/// (OMSetBlendState) - Defina o estado de mistura da fase de saída-fusão.
			/// Para criar uma interface de mistura-estado, chamade o método ICarenD3D11Device::CriarBlendState.
			/// </summary>
			/// <param name="Param_EstadoMitura">Ponteiro para um estado de mistura interface. Passe nulo para um estado de mistura padrão.</param>
			/// <param name="Param_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA. Os fatores de mistura modulate valores para o shader de pixel, processar o alvo, ou ambos. Se você 
			/// tiver criado o objeto de mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, a fase de mistura usa a matriz não-nulos de mistura fatores. Se você não criar o objeto de 
			/// mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, fase de mesclagem não usa a matriz não-nulos de misturam fatores; o tempo de execução armazena os mistura de fatores, 
			/// e mais tarde pode chamar ICarenD3D11DeviceContext::OMObterBlendState para recuperar os fatores de mistura. Se você transmitir NULO, o tempo de execução usa ou armazena um fator de mistura igual 
			/// a {1, 1, 1, 1}.</param>
			/// <param name="Param_SampleMask">cobertura de amostra de 32 bits. O valor padrão é 0xffffffff. Uma máscara de amostra determina quais amostras atualizadas em todos os destinos de processamento ativo. 
			/// O mapeamento de bits em uma máscara de amostra para amostras em um destino processar multisample é da responsabilidade de um aplicativo individual. Sempre é aplicada uma máscara de amostra; 
			/// é independente de se multisampling é habilitado e não depende de se um aplicativo usa multisample render destinos.</param>
			CarenResult OMDefinirBlendState(
				ICarenD3D11BlendState^ Param_EstadoMitura,
				cli::array<float>^ Param_MatrizFatoresMistura,
				UInt32 Param_SampleMask);

			/// <summary>
			/// (OMSetDepthStencilState) - Define o estado de profundidade-estêncil da fase de saída-fusão.
			/// [Atenção] -> O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
			/// </summary>
			/// <param name="Param_DepthStencilState">Ponteiro para um estado de profundidade-estêncil interface para ligar o dispositivo. Defina NULO para usar o estado padrão listado em D3D11_DEPTH_STENCIL_DESC.</param>
			/// <param name="Param_StencilRef">Valor de referência para executar contra ao fazer um teste de profundidade-estêncil.</param>
			CarenResult OMDefinirDepthStencilState(
				ICarenD3D11DepthStencilState^ Param_DepthStencilState,
				UInt32 Param_StencilRef);

			/// <summary>
			/// (OMSetRenderTargets) - Ligar um ou mais destinos de processamento atomicamente e a profundidade-estêncil buffer para o estágio de saída-fusão.
			/// </summary>
			/// <param name="Param_NumeroViews">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas 
			/// na matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro.</param>
			/// <param name="Param_MatizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumViews é 0, não render destinos são vinculados.</param>
			/// <param name="Param_DepthStencilView">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
			CarenResult OMDefinirRenderTargets(
				UInt32 Param_NumeroViews,
				cli::array<ICarenD3D11RenderTargetView^>^ Param_MatizRenderTargetViews,
				ICarenD3D11DepthStencilView^ Param_DepthStencilView);

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
			CarenResult OMDefinirRenderTargetsAndUnorderedAccessViews(
				UInt32 Param_NumeroRTVs,
				cli::array <ICarenD3D11RenderTargetView^>^ Param_MatrizRenderTargetViews,
				ICarenD3D11DepthStencilView^ Param_DepthStencil,
				UInt32 Param_UAVStartSlot,
				UInt32 Param_NumeroUAVs,
				cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizUnorderedAccessViews,
				cli::array<UInt32>^ Param_MatrizUAVInitialCounts);

			/// <summary>
			/// (PSGetConstantBuffers) - Se os buffers constantes usados por fase de gasoduto do sombreador de pixel. 
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
			CarenResult PSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (PSGetSamplers) - Obtém uma matriz de Estados amostrador desde a fase de gasoduto de sombreador de pixel.
			/// </summary>
			/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
			CarenResult PSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

			/// <summary>
			/// (PSGetShader) -  Obtém o sombreador de pixel atualmente definido no dispositivo.
			/// </summary>
			/// <param name="Param_Out_SombreadorPixel">Retorna uma interface para o Sombreador de Pixel.</param>
			/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
			/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
			CarenResult PSObterShader(
				[Out] ICarenD3D11PixelShader^% Param_Out_SombreadorPixel,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
				[Out] UInt32% Param_Out_QuantidadeInstancias);

			/// <summary>
			/// (PSGetShaderResources) - Obter o pixel sombreador recursos.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
			CarenResult PSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (PSSetConstantBuffers) - Define os constantes buffers usados pela fase de gasoduto do sombreador de pixel.
			/// </summary>
			/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param>
			CarenResult PSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (PSSetSamplers) - Defina uma matriz de Estados amostrador à fase de gasoduto de sombreador de pixel.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
			CarenResult PSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

			/// <summary>
			/// (PSSetShader) - Define um sombreador de pixel para o dispositivo.
			/// </summary>
			/// <param name="Param_Out_SombreadorPixel">Ponteiro para um Sombreador de Pixel. Passar NULO desativa o shader para este estágio de pipeline.</param>  
			/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
			/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
			CarenResult PSDefinirShader(
				ICarenD3D11PixelShader^ Param_Out_SombreadorPixel,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
				UInt32 Param_NumeroInstanciasClasse);

			/// <summary>
			/// (PSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de pixel.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
			CarenResult PSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (ResolveSubresource) - Copie um recurso multisampled para um recurso não-multisampled.
			/// </summary>
			/// <param name="Param_RecursoDestino">Recurso de destino. Deve ser um criado com o sinalizador D3D11_USAGE_DEFAULT e single-amostrados.</param>
			/// <param name="Param_IndiceSubRecursoDestino">Um índice baseado em zero, que identifica o sub-recurso de destino. Use D3D11CalcSubresource para calcular o índice.</param>
			/// <param name="Param_RecursoOrigem">Fonte de recursos. Deve ser multisampled.</param>
			/// <param name="Param_IndiceSubRecursoOrigem">O sub-recurso fonte de fonte de recursos.</param>
			/// <param name="Param_DXGIFormato">Um CA_DXGI_FORMAT que indica como o recurso multisampled será resolvido para um recurso único-amostrados.</param>
			CarenResult ResolverSubRecurso(
				ICarenD3D11Resource^ Param_RecursoDestino,
				UInt32 Param_IndiceSubRecursoDestino,
				ICarenD3D11Resource^ Param_RecursoOrigem,
				UInt32 Param_IndiceSubRecursoOrigem,
				Enumeracoes::CA_DXGI_FORMAT Param_DXGIFormato);

			/// <summary>
			/// (RSGetScissorRects) - Obtém a matriz de scissor retângulos vinculado à fase rasterizer.
			/// </summary>
			/// <param name="Param_Out_NumeroRects">O número de retângulos de tesoura (intervalos entre 0 e D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) ligados; defina Param_ChecarQuantidade para TRUE para usar 
			/// Param_Out_NumeroRects para ver quantos retângulos seriam retornados.</param>
			/// <param name="Param_ChecarQuantidade">Define como (TRUE) para obter a quantidade de retangulos que seriam retornados. Se esse valor for TRUE, o parametro (Param_Out_Rects) não retorna nada.</param>
			/// <param name="Param_Out_Rects">Uma matriz de retângulos scissor. Se Param_NumeroRects for maior que o número de (Scissor Rects) atualmente vinculada, membros não utilizados da matriz conterá 0.</param>
			CarenResult RSObterScissorRects(
				[Out] UInt32% Param_Out_NumeroRects,
				Boolean Param_ChecarQuantidade,
				[Out] cli::array<Estruturas::CA_RECT^>^% Param_Out_Rects);

			/// <summary>
			/// (RSGetState) - Obtém o estado do rasterizador do rasterizador estágio do pipeline.
			/// </summary>
			/// <param name="Param_Out_EstadoRasterizador">Um ponteiro para um estado de rasterizador interface para preencher com as informações do dispositivo.</param>
			CarenResult RSObterState([Out] ICarenD3D11RasterizerState^% Param_Out_EstadoRasterizador);

			/// <summary>
			/// (RSGetViewports) - Obtém a matriz de viewports vinculadas à fase rasterizer.
			/// </summary>
			/// <param name="Param_ObterQuantidadeViewports">Define para (TRUE) para obter o número de viewports atualmente definidas. Se (TRUE), Param_Out_MatrizViewports retorna NULO.</param>
			/// <param name="Param_Ref_NumeroViewports">.Na entrada deve definir a quantidade de viewports que seram obtidas. Na saida, ela retorna a quantidade real de viewports retornadas pelo
			/// parametro (Param_Out_MatrizViewports).</param>
			/// <param name="Param_Out_MatrizViewports">Uma matriz de estruturas CA_D3D11_VIEWPORT para as viewports que estão vinculadas à fase do rasterizador.</param>
			CarenResult RSObterViewports(
				Boolean Param_ObterQuantidadeViewports,
				UInt32% Param_Ref_NumeroViewports,
				[Out] cli::array<Estruturas::CA_D3D11_VIEWPORT^>^% Param_Out_MatrizViewports);

			/// <summary>
			/// (RSSetScissorRects) - Vincule uma matriz de retângulos de tesoura para o rasterizador de palco.
			/// </summary>
			/// <param name="Param_NumeroRects">Número de retângulos de tesoura para ligar.</param>
			/// <param name="Param_MatrizRects">Uma matriz de retângulos scissor.</param>
			CarenResult RSDefinirScissorRects(
				UInt32 Param_NumeroRects,
				cli::array<Estruturas::CA_RECT^>^ Param_MatrizRects);

			/// <summary>
			/// (RSSetState) - Defina o estado do rasterizador para o rasterizador de estágio do pipeline.
			/// </summary>
			/// <param name="Param_EstadoRasterizador">Ponteiro para uma interface de estado rasterizador para vincular ao pipeline.</param>
			CarenResult RSDefinirState(ICarenD3D11RasterizerState^ Param_EstadoRasterizador);

			/// <summary>
			/// (RSSetViewports) - Ligar a uma matriz de viewports para o rasterizador de estágio do pipeline.
			/// </summary>
			/// <param name="Param_NumeroViewports">Número de viewports para vincular.</param>
			/// <param name="Param_MatrizViewports">Uma matriz de estruturas D3D11_VIEWPORT para vincular ao dispositivo. Consulte a página de estrutura para obter detalhes sobre como o tamanho da viewport depende do nível de recurso do dispositivo que foi alterado 
			/// entre o Direct3D 11 e o Direct3D 10.</param>
			CarenResult RSDefinirViewports(
				UInt32 Param_NumeroViewports,
				cli::array<Estruturas::CA_D3D11_VIEWPORT^>^ Param_MatrizViewports);

			/// <summary>
			/// (SetPredication) - Defina um predicado de renderização.
			/// </summary>
			/// <param name="Param_Predicate">Um ponteiro para a interface ICarenD3D11Predicate que representa o predicado de renderização. Um valor NULO indica predicação "não"; Nesse caso, o valor de 
			/// (Param_ValorPredicado) é irrelevante, mas será preservado para ICarenD3D11DeviceContext::ObterPredicado.</param>
			/// <param name="Param_ValorPredicado">Se TRUE, a renderização será afetada quando as condições do predicado forem cumpridas. Se FALSE, a renderização será afetada quando as condições não forem atendidas.</param>
			CarenResult DefinirPredication(
				ICarenD3D11Predicate^ Param_Predicate,
				Boolean Param_ValorPredicado);

			/// <summary>
			/// (SetResourceMinLOD) - Define o mínimo nível-de-detalhe (LOD) para um recurso.
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para um ID3D11Resource que representa o recurso.</param>
			/// <param name="Param_MinLOD">O nível de detalhamento, que varia entre 0 e o número máximo de níveis de mipmap do recurso. Por exemplo, o número máximo de níveis mipmap de uma textura 1D é especificado na 
			/// MipLevels membro do D3D11_TEXTURE1D_DESC estrutura.</param>
			CarenResult DefinirResourceMinLOD(
				ICarenD3D11Resource^ Param_Recurso,
				float Param_MinLOD);

			/// <summary>
			/// (SOGetTargets) - Obtém os amortecedores de saída alvo para a fase de saída de fluxo do gasoduto.
			/// </summary>
			/// <param name="Param_NumeroBuffers">O número de Buffers a serem obtidos.</param>
			/// <param name="Param_Out_MatrizBuffers">Recebe a matriz com os buffers de saida retornado do dispositivo.</param>
			CarenResult SOObterTargets(
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (SOSetTargets) - Defina os buffers de saída de destino para o fluxo de saída estágio do pipeline.
			/// </summary>
			/// <param name="Param_NumeroBuffers">O número de buffer para ligar ao dispositivo. Um máximo de quatro buffers de saída pode ser definido. Se menos de quatro forem definidos pela chamada, 
			/// os slots de buffer restantes serão definidos como NULO.</param>
			/// <param name="Param_MatrizBuffers">A matriz de buffers de saída para ligar ao dispositivo. Os buffers devem ter sido criados com o sinalizador D3D11_BIND_STREAM_OUTPUT.</param>  
			/// <param name="Param_DeslocamentosBuffers">Matriz de deslocamentos para os buffers de saída de (Param_MatrizBuffers), um deslocamento para cada buffer. Os valores de deslocamento devem estar 
			/// em bytes.</param>
			CarenResult SODefinirTargets(
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_DeslocamentosBuffers);

			/// <summary>
			/// (unmap) - Invalida o ponteiro para um recurso e reabilita o acesso da GPU para esse recurso.
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para o recurso a ser invalido.</param>
			/// <param name="Param_SubrecursoInvalidado">O Id do subrecurso a ser (Desmapeado).</param>
			CarenResult Unmap(
				ICarenD3D11Resource^ Param_Recurso,
				UInt32 Param_SubrecursoInvalidado);

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
			CarenResult AtualizarSubresource(
				ICarenD3D11Resource^ Param_RecursoDestino,
				UInt32 Param_SubrecursoDestino,
				Estruturas::CA_D3D11_BOX^ Param_Caixa,
				ICarenBuffer^ Param_DadosOrigemMemoria,
				UInt32 Param_TamanhoLinhaOrigem,
				UInt32 Param_TamhoFatiaProdundidade);

			/// <summary>
			/// (VSGetConstantBuffers) - Se os buffers constantes usados pela fase vértice shader pipeline.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
			CarenResult VSObterConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

			/// <summary>
			/// (VSGetSamplers) - Obter uma matriz de Estados amostrador desde a fase de gasoduto de shader de vértice.
			/// </summary>
			/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
			CarenResult VSObterSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

			/// <summary>
			/// (VSGetShader) - Obtém o vértice shader atualmente definido no dispositivo.
			/// </summary>
			/// <param name="Param_Out_SombreadorVertice">Retorna uma interface para o sombreador de vertice.</param>
			/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
			/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
			CarenResult VSObterShader(
				[Out] ICarenD3D11VertexShader^% Param_Out_SombreadorVertice,
				[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
				[Out] UInt32% Param_Out_QuantidadeInstancias);

			/// <summary>
			/// (VSGetShaderResources) - Obter o vértice shader recursos.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
			CarenResult VSObterShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

			/// <summary>
			/// (VSSetConstantBuffers) - Define os constantes buffers usados pela fase vértice shader pipeline.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
			/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
			CarenResult VSDefinirConstantBuffers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

			/// <summary>
			/// (VSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline vértice shader.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
			CarenResult VSDefinirSamplers(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroAmostradores,
				cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

			/// <summary>
			/// (VSSetShader) - Defina um sombreador de vértices para o dispositivo.
			/// </summary>
			/// <param name="Param_ShaderVertice">Ponteiro para um sombreador de vértice. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
			/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
			/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
			CarenResult VSDefnirShader(
				ICarenD3D11VertexShader^ Param_ShaderVertice,
				cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
				UInt32 Param_NumeroInstanciasClasse);

			/// <summary>
			/// (VSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de vértices.
			/// </summary>
			/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
			/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
			/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
			CarenResult VSDefinirShaderResources(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroViews,
				cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);
		};

		/// <summary>
		/// (ID3D11DeviceContext1) - Interface representa um contexto de dispositivo; é usado para realizar comandos de renderização. O ICarenD3D11DeviceContext1 
		/// adiciona novos métodos aos do ICarenD3D11DeviceContext.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por gerar comandos de Renderização.")]
		[Guid("FB873D13-9A02-47CD-BD88-E616AE96E1AE")]
		public interface class ICarenD3D11DeviceContext1 : ICarenD3D11DeviceContext
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos
		
			/// <summary>
			/// (ClearView) - Define todos os elementos em uma visão de recurso para um valor.
			/// </summary>
			/// <param name="Param_View">Um ponteiro para uma interface ICarenD3D11View que representa a visão de recurso a ser limpa.</param>
			/// <param name="Param_Cor">Um conjunto de 4 componentes(RGBA) que representa a cor para usar para limpar a visão de recurso.</param>
			/// <param name="Param_ArrayRetangulos">Um array de estruturas (CA_RECT) para os retângulos na visão de recursos para limpar. Se NULO, o (ClearView) limpa toda a superfície.</param>
			/// <param name="Param_QuantidadeItems">O número de retângulos no array (Param_ArrayRetangulos).</param>
			CarenResult ClearView(
				ICarenD3D11View^ Param_View,
				cli::array<float>^ Param_Cor,
				cli::array<CA_RECT^>^ Param_ArrayRetangulos,
				UInt32 Param_QuantidadeItems);

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
			/// <param name="Param_CopyFlags">Um valor CA_D3D11_COPY_FLAGS que especifica como realizar a operação de cópia. Se você especificar zero para nenhuma opção de cópia, CopiarSubRecursoRegiao1 se comporta como ICarenD3D11DeviceContext::CopiarSubRecursoRegiao. Para os drivers de exibição existentes que não podem processar essas bandeiras, o tempo de execução não as usa.</param>
			CarenResult CopiarSubRecursoRegiao1(
				ICarenD3D11Resource^ Param_DestinoRecurso,
				UInt32 Param_IndiceSubrecrusoDestino,
				UInt32 Param_DestX,
				UInt32 Param_DestY,
				UInt32 Param_DestZ,
				ICarenD3D11Resource^ Param_FonteRecurso,
				UInt32 Param_IndiceSubrecrusoFonte,
				Estruturas::CA_D3D11_BOX^ Param_OrigemBox,
				CA_D3D11_COPY_FLAGS Param_CopyFlags);

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
			CarenResult CSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult CSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);

			/// <summary>
			/// (DiscardResource) - Descarta um recurso do contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para a interface de recurso a ser dercartada. O recurso deve ter sido criado com uso D3D11_USAGE_DEFAULT ou D3D11_USAGE_DYNAMIC, 
			/// caso contrário, o tempo de execução derruba a chamada para o (DescartarRecurso); se a camada de depuração estiver ativada, o tempo de execução retorna uma mensagem de erro.</param>
			CarenResult DescartarRecurso(ICarenD3D11Resource^ Param_Recurso);

			/// <summary>
			/// (DiscardView) - Descarta uma visão de recurso do contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
			/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
			/// retorna uma mensagem de erro.</param>
			CarenResult DiscardView(ICarenD3D11View^ Param_Visão);

			/// <summary>
			/// (DiscardView1) - Descarta os elementos especificados em uma visão de recurso do contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
			/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
			/// retorna uma mensagem de erro.</param>
			/// <param name="Param_MatrizRetangulos">Uma matriz de estruturas CA_RECT para os retângulos na visão de recurso para descartar. Se NULO, o DiscardView1 descarta toda a 
			/// visualização e se comporta da mesma forma que o DiscardView.</param>
			/// <param name="Param_NumeroRetangulos">A quantidade de retangulos no array (Param_MatrizRetangulos).</param>
			CarenResult DiscardView1(ICarenD3D11View^ Param_Visão, cli::array<CA_RECT^>^ Param_MatrizRetangulos, UInt32 Param_NumeroRetangulos);

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
			CarenResult DSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult DSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);

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
			CarenResult GSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult GSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);

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
			CarenResult HSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult HSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);

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
			CarenResult PSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult PSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);

			/// <summary>
			/// (SwapDeviceContextState) - Ativa o objeto de estado de contexto dado e altera o comportamento atual do dispositivo para Direct3D 11, Direct3D 10.1 ou Direct3D 10.
			/// </summary>
			/// <param name="Param_Estado">Um ponteiro para a interface ICarenD3DDeviceContextState para o objeto de estado de contexto que foi criado anteriormente através do método 
			/// ICarenD3D11Device1::CriarDispositivoEstadoContexto. Se o SwapDeviceContextState for chamado com o (Param_Estado) definido como NULO,a chamada não tem efeito.</param>
			/// <param name="Param_Out_EstadoAnterior">Recebe um ponteiro para a interface ICarenD3DDeviceContextState com o estado do objeto anteriormente ativado.</param>
			CarenResult SwapDeviceContextState(
				ICarenD3DDeviceContextState^ Param_Estado, 
				[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoAnterior);

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
			/// o (AtualizarSubresource1) se comporta como ICarenD3D11DeviceContext::AtualizarSubresource. Para os drivers de exibição existentes que não podem processar essas bandeiras, 
			/// o tempo de execução não as usa.</param>
			CarenResult AtualizarSubresource1(
				ICarenD3D11Resource^ Param_RecursoDestino,
				UInt32 Param_SubrecursoDestino,
				Estruturas::CA_D3D11_BOX^ Param_Caixa,
				ICarenBuffer^ Param_DadosOrigemMemoria,
				UInt32 Param_TamanhoLinhaOrigem,
				UInt32 Param_TamhoFatiaProdundidade,
				CA_D3D11_COPY_FLAGS Param_CopyFlags);

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
			CarenResult VSObterConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
				[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
				[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

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
			CarenResult VSDefinirConstantBuffers1(
				UInt32 Param_StartSlot,
				UInt32 Param_NumeroBuffers,
				cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
				cli::array<UInt32>^ Param_MatrizInicioConstante,
				cli::array<UInt32>^ Param_MatrizNumeroConstantes);
		};

		/// <summary>
		/// (ID3D11DeviceContext2) - Interface representa um contexto de dispositivo; é usado para realizar comandos de renderização. O ICarenD3D11DeviceContext2 
		/// adiciona novos métodos aos do ICarenD3D11DeviceContext1.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por gerar comandos de Renderização.")]
		[Guid("B62157D4-65D2-4BAC-BEAD-0AF193015CC7")]
		public interface class ICarenD3D11DeviceContext2 : ICarenD3D11DeviceContext1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (BeginEventInt) - Permite que as aplicações anotem o início de uma gama de comandos gráficos,  fim de fornecer mais contexto ao que a GPU está executando. Quando o registro ETW (ou uma ferramenta suportada) é ativado, um marcador adicional está correlacionado entre os cronogramas da CPU e GPU.
			/// </summary>
			/// <param name="Param_Label">Uma sequência opcional que será registrada na ETW quando o registro ETW estiver ativo. Se '#d' aparecer na sequência, ele será substituído pelo valor do parâmetro Param_Data semelhante à forma como o printf funciona.</param>
			/// <param name="Param_Data">Um valor de dados assinado que será registrado na ETW quando o registro ETW estiver ativo.</param>
			CarenResult BeginEventInt(
				String^ Param_Label, 
				Int32 Param_Data);

			/// <summary>
			/// (CopyTileMappings) - Copia mapeamentos de um recurso de ladrilhos de origem para um recurso de revestimento de destino.
			/// </summary>
			/// <param name="Param_DestinoRecursoTiled">Um ponteiro para o recurso de Tiled de destino.</param>
			/// <param name="Param_DestinoCoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tiles de destino.</param>
			/// <param name="Param_OrigemRecursoTiled">Um ponteiro para o recurso de Tiled de origem.</param>
			/// <param name="Param_OrigemCoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tiles de origem.</param>
			/// <param name="Param_TamanhoRegiaoTiled">Uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região de Tiles.</param>
			/// <param name="Param_Flags">Uma combinação de valores D3D11_TILE_MAPPING_FLAGS que são combinados usando uma operação ou bitwise. O único valor válido é D3D11_TILE_MAPPING_NO_OVERWRITE,o que indica que 
			/// os comandos anteriormente enviados ao dispositivo que ainda podem estar sendo executados não fazem referência a nenhuma das regiões de Tiles que estão sendo atualizadas. O dispositivo pode então evitar 
			/// ter que lavar o trabalho anteriormente enviado para realizar a atualização de mapeamento de Tiles.</param>
			CarenResult CopyTileMappings(
				ICarenD3D11Resource^ Param_DestinoRecursoTiled, 
				CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_DestinoCoordenadasInicio,
				ICarenD3D11Resource^ Param_OrigemRecursoTiled,
				CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_OrigemCoordenadasInicio,
				CA_D3D11_TILE_REGION_SIZE^ Param_TamanhoRegiaoTiled,
				CA_D3D11_TILE_MAPPING_FLAGS Param_Flags);

			/// <summary>
			/// (CopyTiles) - Copia Tiles do buffer ao recurso de ladrilhos ou vice-versa.
			/// </summary>
			/// <param name="Param_RecursoTiled">Um ponteiro para o recurso da Tile.</param>
			/// <param name="Param_CoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tile.</param>
			/// <param name="Param_TamanhoRegiaoTile">Uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região do Tile.</param>
			/// <param name="Param_Buffer">Um ponteiro para uma ICarenD3D11Buffer que representa um buffer padrão, dinâmico ou de encenação.</param>
			/// <param name="Param_BufferStartOffsetInBytes">O Offset, em bytes no (Param_Buffer) para iniciar a operação.</param>
			/// <param name="Param_CopyFlags">Uma combinação de valores CA_D3D11_TILE_COPY_FLAG que são combinados usando uma operação OU bitwise e que identifica como copiar Tiles.</param>
			CarenResult CopyTiles(
				ICarenD3D11Resource^ Param_RecursoTiled, 
				CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_CoordenadasInicio, 
				CA_D3D11_TILE_REGION_SIZE^ Param_TamanhoRegiaoTile,
				ICarenD3D11Buffer^ Param_Buffer,
				UInt64 Param_BufferStartOffsetInBytes,
				CA_D3D11_TILE_COPY_FLAG Param_CopyFlags);

			/// <summary>
			/// (EndEvent) - Permite que as aplicações anotem o fim de uma gama de comandos gráficos.
			/// </summary>
			CarenResult EndEvent();

			/// <summary>
			/// (IsAnnotationEnabled) - Permite que os aplicativos determinem quando uma solicitação de captura ou perfil está ativada.
			/// </summary>
			/// <param name="Param_Out_Estado">Retorna TRUE se a captura ou o perfil for ativado e FALSO de outra forma.</param>
			CarenResult IsAnnotationEnabled([Out] bool% Param_Out_Estado);

			/// <summary>
			/// (ResizeTilePool) - Redimensiona uma Tile Pool.
			/// </summary>
			/// <param name="Param_TilePool">Um ponteiro para a interface ICarenD3D11Buffer que contém o Tile a ser redimensionado.</param>
			/// <param name="Param_NovoSizeBytes">O novo tamanho em bytes do Pool de Tiles. O tamanho deve ser um múltiplo de 64 KB ou 0.</param>
			CarenResult ResizeTilePool(
				ICarenD3D11Buffer^ Param_TilePool, 
				UInt64 Param_NovoSizeBytes);

			/// <summary>
			/// (SetMarkerInt) - Permite que aplicativos anotem comandos gráficos.
			/// </summary>
			/// <param name="Param_Label">Uma sequência opcional que será registrada na ETW quando o registro ETW estiver ativo. Se '#d' aparecer na sequência, ele será substituído pelo valor do parâmetro Param_Data semelhante à forma como o printf funciona.</param>
			/// <param name="Param_Data">Um valor de dados assinado que será registrado na ETW quando o registro ETW estiver ativo.</param>
			CarenResult SetMarkerInt(
				String^ Param_Label, 
				Int32 Param_Data);

			/// <summary>
			/// (TiledResourceBarrier) - Especifica uma restrição de pedidos de acesso de dados entre múltiplos recursos ladrilhos.
			/// </summary>
			/// <param name="Param_TiledResourceOrViewAccessBeforeBarrier">Um ponteiro para uma ICarenD3D11Resource ou ICarenD3D11View para um recurso que foi criado com a bandeira D3D11_RESOURCE_MISC_TILED. As operações de 
			/// acesso neste objeto devem ser concluídas antes das operações de acesso no objeto que especifica o (Param_TiledResourceOrViewAccessAfterBarrier).</param>
			/// <param name="Param_TiledResourceOrViewAccessAfterBarrier">Um ponteiro para uma ICarenD3D11Resource ou ICarenD3D11View para um recurso que foi criado com a bandeira D3D11_RESOURCE_MISC_TILED. As operações de acesso neste objeto devem começar após as operações de acesso no objeto que especifica o PTiledResourceOrViewAccessBeforeBarrier.</param>
			CarenResult TiledResourceBarrier(
				ICarenD3D11DeviceChild^ Param_TiledResourceOrViewAccessBeforeBarrier,
				ICarenD3D11DeviceChild^ Param_TiledResourceOrViewAccessAfterBarrier);

			/// <summary>
			/// (UpdateTileMappings) - Atualiza mapeamentos de locais de ladrilhos em recursos ladrilhos para locais de memória em um pool de Tiles.
			/// </summary>
			/// <param name="Param_RecursoTiled">Um ponteiro para o recurso de Tiles.</param>
			/// <param name="Param_QuantidadeReigoesRecursoTiled">O número de regiões de recursos de Tiles.</param>
			/// <param name="Param_MatrizCoordernadasInicioRecursoTiled">Uma matriz de estruturas CA_D3D11_TILED_RESOURCE_COORDINATE que descrevem as coordenadas iniciais das regiões de recursos ladrilhos. O parâmetro 
			/// (Param_QuantidadeReigoesRecursoTiled) especifica o número de estruturas CA_D3D11_TILED_RESOURCE_COORDINATE na matriz.</param>
			/// <param name="Param_MatrizSizeReigoesRecursoTiled">Uma matriz de estruturas CA_D3D11_TILE_REGION_SIZE que descrevem os tamanhos das regiões de recursos tiles. O parâmetro (Param_QuantidadeReigoesRecursoTiled) 
			/// especifica o número de estruturas CA_D3D11_TILE_REGION_SIZE na matriz.</param>
			/// <param name="Param_TilePool">Um ponteiro para um Pool de Tiles.</param>
			/// <param name="Param_NumeroRanges">O número de faixas de Tiles.</param>
			/// <param name="Param_MatrizFlagsRange">Uma matriz de CA_D3D11_TILE_RANGE_FLAG que descrevem cada faixa de Tile-Pool. O parâmetro (Param_NumeroRanges) especifica o número de valores na matriz.</param>
			/// <param name="Param_MatrizOffsetStartTiledPool">Uma série de deslocamentos no pool de tiles. São compensações de tiles baseadas em 0, contando em tiles (não bytes).</param>
			/// <param name="Param_MatrizQuantidadeRangesTile">Uma matriz de valores que especificam o número de tiles em cada faixa de Tile-Pool. O parâmetro (Param_NumeroRanges) especifica o número de valores na matriz.</param>
			/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_TILE_MAPPING_FLAGS que são combinados usando uma operação ou bitwise.</param>
			CarenResult UpdateTileMappings(
				ICarenD3D11Resource^ Param_RecursoTiled,
				UInt32 Param_QuantidadeReigoesRecursoTiled,
				cli::array<CA_D3D11_TILED_RESOURCE_COORDINATE^>^ Param_MatrizCoordernadasInicioRecursoTiled,
				cli::array<CA_D3D11_TILE_REGION_SIZE^>^ Param_MatrizSizeReigoesRecursoTiled,
				ICarenD3D11Buffer^ Param_TilePool,
				UInt32 Param_NumeroRanges,
				cli::array<CA_D3D11_TILE_RANGE_FLAG>^ Param_MatrizFlagsRange,
				cli::array<UInt32>^ Param_MatrizOffsetStartTiledPool,
				cli::array<UInt32>^ Param_MatrizQuantidadeRangesTile,
				CA_D3D11_TILE_MAPPING_FLAGS Param_Flags);

			/// <summary>
			/// (UpdateTiles) - Atualiza as Tiles copiando da memória do aplicativo para o recurso de ladrilhos.
			/// </summary>
			/// <param name="Param_DestRecursoTiled">Um ponteiro para o recurso tiled a ser atualizado.</param>
			/// <param name="Param_CoordernadasInicioRecursoTiled">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso Tiled.</param>
			/// <param name="Param_SizeReigoesRecursoTiled">uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região do Tile.</param>
			/// <param name="Param_OrigemDadosTile">Um ponteiro para a memória que contém os dados do Tile de origem que o UpdateTiles usa para atualizar o recurso de Tiles.</param>
			/// <param name="Param_CopyFlags">Uma combinação de valores D3D11_TILE_COPY_FLAG que são combinados usando uma operação ou bitwise. O único valor válido é 
			/// D3D11_TILE_COPY_NO_OVERWRITE. Os outros valores não são significativos aqui, embora por definição o valor D3D11_TILE_COPY_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE 
			/// é basicamente o que o UpdateTiles faz, mas fontes da memória do aplicativo.</param>
			CarenResult UpdateTiles(
				ICarenD3D11Resource^ Param_DestRecursoTiled,
				CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_CoordernadasInicioRecursoTiled,
				CA_D3D11_TILE_REGION_SIZE^ Param_SizeReigoesRecursoTiled,
				ICarenBuffer^ Param_OrigemDadosTile,
				CA_D3D11_TILE_COPY_FLAG Param_CopyFlags);
		};

		/// <summary>
		/// (ID3D11DeviceContext3) - Interface representa um contexto do dispositivo; é usado para realizar comandos de renderização. O ICarenD3D11DeviceContext3 
		/// adiciona novos métodos aos do ICarenD3D11DeviceContext2.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por gerar comandos de Renderização.")]
		[Guid("7163CB91-6DA2-4A0D-A67A-486952F70AF5")]
		public interface class ICarenD3D11DeviceContext3 : ICarenD3D11DeviceContext2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos


			/// <summary>
			/// (Flush1) - 	Envia comandos enfileirados no buffer de comando para a unidade de processamento gráfico (GPU), com um tipo de contexto especificado e uma alça opcional 
			/// de eventos para criar uma consulta de eventos.
			/// </summary>
			/// <param name="Param_TypeContexto">Um valor CA_D3D11_CONTEXT_TYPE que especifica o contexto em que ocorre uma consulta, como uma fila de comando 3D, fila de computação 3D, 
			/// fila de cópia 3D, vídeo ou imagem.</param>
			/// <param name="Param_Handle">Uma Handle opcional de eventos. Quando especificado, este método cria uma consulta de eventos. Flush1 opera de forma assíncrona, portanto, 
			/// pode retornar antes ou depois que a GPU terminar executando os comandos gráficos enfileirados, que eventualmente serão concluídos.</param>
			CarenResult Flush1(CA_D3D11_CONTEXT_TYPE Param_TypeContexto, ICarenWindowsEvent^ Param_Handle);

			/// <summary>
			/// (GetHardwareProtectionState) - Obtém um valor que define se a proteção de hardware está ativada.
			/// </summary>
			/// <param name="Param_Out_ProtecaoHardwareHabilitada">Retorna TRUE se a proteção de hardware estiver habilitada, caso contrario, FALSE.</param>
			CarenResult ObterStatusProtecaoHardware([Out] bool% Param_Out_ProtecaoHardwareHabilitada);

			/// <summary>
			/// (SetHardwareProtectionState) - Define o estado de proteção de hardware.
			/// </summary>
			/// <param name="Param_EstadoProtecao">Um valor booleano que define o estado da proteção de Hardware.</param>
			CarenResult DefinirStatusProtecaoHardware(bool Param_EstadoProtecao);
		};

		/// <summary>
		/// (ID3D11DeviceContext4) - Interface representa um contexto do dispositivo; é usado para realizar comandos de renderização. O ICarenD3D11DeviceContext4 
		/// adiciona novos métodos aos do ICarenD3D11DeviceContext3.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por gerar comandos de Renderização.")]
		[Guid("A7E2D5DA-B61D-4A0D-96C7-3C3A9CE07EDD")]
		public interface class ICarenD3D11DeviceContext4 : ICarenD3D11DeviceContext3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (Signal) - Atualiza uma Fence para um valor especificado depois que todos os trabalhos anteriores terminarem.
			/// Este método só se aplica a contextos de modo imediato.
			/// </summary>
			/// <param name="Param_Fence">Um ponteiro para a interface do objeto ICarenD3D11Fence.</param>
			/// <param name="Param_Valor">Um valor para definir o Fence.</param>
			CarenResult Sinal(ICarenD3D11Fence^ Param_Fence, UInt64 Param_Valor);

			/// <summary>
			/// (Wait) - Espera até que uma Fence especificada atinja ou exceda o valor especificado antes que o trabalho futuro possa começar.
			/// Este método só se aplica a contextos de modo imediato.
			/// </summary>
			/// <param name="Param_Fence">Um ponteiro para a interface do objeto ICarenD3D11Fence.</param>
			/// <param name="Param_Valor">O valor que o contexto do dispositivo está esperando a cerca alcançar ou exceder. Então, quando o ICarenD3D11Fence::ObterValorCompletado
			/// é maior do que ou igual ao (Param_Valor), a espera é encerrada.</param>
			CarenResult Aguardar(ICarenD3D11Fence^ Param_Fence, UInt64 Param_Valor);
		};

		/// <summary>
		/// (ID3D11Texture1D) -  Interface de textura 1D acessa dados de texel, que é a memória estruturada.
		/// Texturas não podem ser vinculadas diretamente ao pipeline; em vez disso, um modo de exibição deve ser criado e vinculado. Usando um modo de exibição, dados de textura podem ser interpretados em tempo de execução 
		/// dentro de certas restrições. 
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Interface responsável por expor os métodos da ID3D11Texture1D.")]
		[Guid("DA903CD4-062B-46E2-9BB1-074A2B734CDD")]
		public interface class ICarenD3D11Texture1D : ICarenD3D11Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtem as propriedades do recurso de textura.
			/// </summary>
			/// <param name="Param_Out_PropsTextura1D">Retorna uma estrutura com as descrições do recuso.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_Out_PropsTextura1D);
		};

		/// <summary>
		/// (ID3D11Texture2D) - Interface de textura 2D gerencia dados de texel, que é a memória estruturada.
		/// Texturas não podem ser vinculadas diretamente ao pipeline; em vez disso, um modo de exibição deve ser criado e vinculado. Usando um modo de exibição, dados de textura podem ser interpretados em tempo de execução 
		/// dentro de certas restrições.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma Textura 2D.")]
		[Guid("06D50069-5E46-4550-ABF7-FC2975D5B3F2")]
		public interface class ICarenD3D11Texture2D : ICarenD3D11Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtém as propriedades do recurso de textura.
			/// </summary>
			/// <param name="Param_Out_PropsTextura2D">Retorna uma estrutura com as descrições do recuso.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_Out_PropsTextura2D);
		};

		/// <summary>
		/// (ID3D11Texture2D1) - Interface de textura 2D gerencia dados de texel, que é a memória estruturada.
		/// Texturas não podem ser vinculadas diretamente ao pipeline; em vez disso, um modo de exibição deve ser criado e vinculado. Usando um modo de exibição, dados de textura podem ser interpretados em tempo de execução 
		/// dentro de certas restrições.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma Textura 2D.")]
		[Guid("1EB09630-211F-44E1-8C65-0F7DA0B2DB1F")]
		public interface class ICarenD3D11Texture2D1 : ICarenD3D11Texture2D
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtém as propriedades do recurso de textura.
			/// </summary>
			/// <param name="Param_Out_PropsTextura2D">Retorna uma estrutura com as descrições do recuso.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_TEXTURE2D_DESC1^% Param_Out_PropsTextura2D);
		};

		/// <summary>
		/// (ID3D11Texture3D) - Interface de textura 3D gerencia dados de texel, que é a memória estruturada.
		/// Texturas não podem ser vinculadas diretamente ao pipeline; em vez disso, um modo de exibição deve ser criado e vinculado. Usando um modo de 
		/// exibição, dados de textura podem ser interpretados em tempo de execução dentro de certas restrições.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma Textura 3D")]
		[Guid("18279842-D923-4B61-8350-C9C4732B6048")]
		public interface class ICarenD3D11Texture3D : ICarenD3D11Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc) - Obtem as propriedades do recurso de textura.
			/// </summary>
			/// <param name="Param_Out_PropsTextura3D">Retorna uma estrutura com as descrições do recuso.</param>
			CarenResult GetDesc([Out] Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_Out_PropsTextura3D);
		};

		/// <summary>
		/// (ID3D11Texture3D1) - Interface de textura 3D gerencia dados de texel, que é a memória estruturada.
		/// Texturas não podem ser vinculadas diretamente ao pipeline; em vez disso, um modo de exibição deve ser criado e vinculado. Usando um modo de 
		/// exibição, dados de textura podem ser interpretados em tempo de execução dentro de certas restrições.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa uma Textura 3D")]
		[Guid("8405B02A-6879-4268-8CB6-53BAAE7FDB88")]
		public interface class ICarenD3D11Texture3D1 : ICarenD3D11Texture3D
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (GetDesc1) - Obtem as propriedades do recurso de textura.
			/// </summary>
			/// <param name="Param_Out_PropsTextura3D">Retorna uma estrutura com as descrições do recuso.</param>
			CarenResult GetDesc1([Out] Estruturas::CA_D3D11_TEXTURE3D_DESC1^% Param_Out_PropsTextura3D);
		};

		/// <summary>
		/// (ID3D11Device) - A interface de dispositivo representa um adaptador virtual; é usado para criar recursos.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("BE9C630E-DE6E-4C19-8AF3-F24238B9C381")]
		public interface class ICarenD3D11Device : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (CheckCounter) - Obtém o tipo, nome, unidades de medida e uma descrição de um contador existente.
			/// </summary>
			/// <param name="Param_DescContador">Ponteiro para uma descrição do contador (CA_D3D11_DESC_CONTADOR). Especifica qual contador informação é para ser obtida sobre.</param>
			/// <param name="Param_Out_TipoDadoContador">Ponteiro para o tipo de dados de um contador (CA_D3D11_TIPO_DADO_CONTADOR). Especifica o tipo de dados do contador de ser obtido.</param>
			/// <param name="Param_Out_NumeroContadores">Ponteiro para o número de contadores de hardware que são necessários para esse tipo de contador ser criado. Todas as instâncias do mesmo tipo contador usam os contadores de hardware mesmo.</param>
			/// <param name="Param_Out_NomeContador">Sequência a ser preenchido com um nome breve para o contador. Pode ser NULL se o aplicativo não está interessado em nome do balcão.</param>
			/// <param name="Param_Out_LarguraNomeContador">Comprimento da sequência de caracteres retornada para Param_Out_NomeContador.</param>
			/// <param name="Param_Out_NomeUnidadeMedidas">Nome das unidades de medidas um contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
			/// <param name="Param_Out_LarguraNomeUnidade">Comprimento da sequência de caracteres retornado para o Param_Out_NomeUnidadeMedidas.</param>
			/// <param name="Param_Out_DescContador">Uma descrição do contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
			/// <param name="Param_Out_LarguraDescContador">Comprimento da sequência de caracteres retornada para Param_Out_DescContador.</param>
			CarenResult VerificarContador(
				Estruturas::CA_D3D11_DESC_CONTADOR^ Param_DescContador,
				[Out] Enumeracoes::CA_D3D11_TIPO_DADO_CONTADOR% Param_Out_TipoDadoContador,
				[Out] UInt32% Param_Out_NumeroContadores,
				[Out] String^% Param_Out_NomeContador,
				[Out] UInt32% Param_Out_LarguraNomeContador,
				[Out] String^% Param_Out_NomeUnidadeMedidas,
				[Out] UInt32% Param_Out_LarguraNomeUnidade,
				[Out] String^% Param_Out_DescContador,
				[Out] UInt32% Param_Out_LarguraDescContador
			);

			/// <summary>
			/// (CheckCounterInfo) - Obter informações de um contador.
			/// </summary>
			/// <param name="Param_Out_InfoContador">Recebe uma estrutura com as informações do contador.</param>
			CarenResult VerificarInformacoesContador([Out] Estruturas::CA_D3D11_INFO_CONTADOR^% Param_Out_InfoContador);

			/// <summary>
			/// (CheckFeatureSupport) - Obtém informações sobre os recursos que são suportados pelo driver de gráficos atuais.
			/// </summary>
			/// <param name="Param_RecursoPesquisa">Um membro do CA_D3D11_RECURSO tipo enumerado que descreve qual recurso de consulta para apoio.</param>
			/// <param name="Param_Out_SuporteRecurso">Após a conclusão do método, a passado estrutura é preenchida com dados que descreve o suporte para o recurso.</param>
			/// <param name="Param_Out_TamanhoEstrutura">O tamanho da estrutura passado para o parâmetro Param_Out_SuporteRecurso.</param>
			CarenResult VerificarRecursosSuportados(
				Enumeracoes::CA_D3D11_RECURSO Param_RecursoPesquisa,
				[Out] Estruturas::CA_D3D11_FEATURE_DATA_THREADING^% Param_Out_SuporteRecurso,
				[Out] UInt32% Param_Out_TamanhoEstrutura
			);

			/// <summary>
			/// (CheckFormatSupport) - Obter o apoio de um determinado formato do dispositivo de vídeo instalado.
			/// </summary>
			/// <param name="Param_Formato">Uma enumeração de CA_DXGI_FORMAT que descreve um formato para o qual deseja verificar se há suporte.</param>
			/// <param name="Param_Out_RecursosSuportados">Um campo de bits de D3D11_FORMAT_SUPPORT valores de enumeração que descreve como o formato especificado 
			/// é suportado no dispositivo instalado. Os valores são ORed juntos.</param>
			CarenResult VerificarFormatoSuportado(
				Enumeracoes::CA_DXGI_FORMAT Param_Formato,
				[Out] Enumeracoes::CA_D3D11_FORMATO_SUPORTE% Param_Out_RecursosSuportados);

			/// <summary>
			/// (CheckMultisampleQualityLevels) - Obter o número de níveis de qualidade disponíveis durante multisampling completo.
			/// Quando multisampling uma textura, o número de níveis de qualidade disponíveis para um adaptador é dependente do formato de textura usado e o número de amostras 
			/// solicitadas. O número máximo de níveis de qualidade é definido pelo D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT em D3D11.h. Se esse método retorna 0, a combinação de 
			/// contagem de formato e amostra não tem suporte para o adaptador instalado.
			/// </summary>
			/// <param name="Param_Formato">O formato de textura. Consulte CA_DXGI_FORMAT.</param>
			/// <param name="Param_NumeroAmostras">O número de amostras durante multisampling completo.</param>
			/// <param name="Param_Out_NumeroNiveisQualidade">Recebe o número de níveis de qualidade suportada pelo adaptador.</param>
			CarenResult ObterNiveisQualidadeDisponiveis(
				Enumeracoes::CA_DXGI_FORMAT Param_Formato,
				UInt32 Param_NumeroAmostras, [Out] UInt32% Param_Out_NumeroNiveisQualidade);

			/// <summary>
			/// (CreateBlendState) - Crie um objeto de mistura-estado que encapsules o estado de combinação para o estágio de saída-fusão.
			/// </summary>
			/// <param name="Param_DescMistura">Uma descrição do estado de mistura.</param>
			/// <param name="Param_Out_BlendState">Recebe uma interface para o objeto de estado de mistura criado.</param>
			CarenResult CriarBlendState(
				Estruturas::CA_D3D11_BLEND_DESC^% Param_DescMistura,
				[Out] ICarenD3D11BlendState^% Param_Out_BlendState);

			/// <summary>
			/// (CreateBuffer) - Cria um buffer (buffer de vértice, buffer de índice ou constante de sombreador buffer).
			/// </summary>
			/// <param name="Param_DescBuffer">Uma estrutura(CA_D3D11_BUFFER_DESC) que descreve o buffer.</param>
			/// <param name="Param_DescDadosInit">uma estrutura(CA_D3D11_SUBRESOURCE_DATA) que descreve os dados de inicialização; Use NULL para alocar espaço só(com a exceção que não pode ser NULL se o sinalizador de 
			/// uso é D3D11_USAGE_IMMUTABLE). Se você não passar nada para este paramêtro, o conteúdo inicial da memória para o buffer é indefinido. Neste caso, você precisa escrever o conteúdo do buffer de outra 
			/// maneira, antes que o recurso é lido.</param>
			/// <param name="Param_ValidarPametros">Defina como TRUE para validar os paramêtros de entrada do método. Se TRUE, Param_Out_InterfaceBuffer retorna NULO.</param>
			/// <param name="Param_Out_InterfaceBuffer">Recebe a interface ICarenD3D11Buffer para o objeto de buffer criado.</param>
			CarenResult CriarBuffer(
				Estruturas::CA_D3D11_BUFFER_DESC^% Param_DescBuffer,
				Estruturas::CA_D3D11_SUBRESOURCE_DATA^% Param_DescDadosInit,
				Boolean Param_ValidarPametros,
				[Out] ICarenD3D11Buffer^% Param_Out_InterfaceBuffer);

			/// <summary>
			/// (CreateClassLinkage) - Cria bibliotecas de enlace de classe para permitir a ligação de sombreador dinâmico.
			/// </summary>
			/// <param name="Param_Out_ClassLinkage">Recebe a interface(ICarenD3D11ClassLinkage) de ligação de classe.</param>
			CarenResult CriarClassLinkage([Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkage);

			/// <summary>
			/// (CreateComputeShader) - Crie um sombreador de computação.
			/// </summary>
			/// <param name="Param_SombreadorCompilado">Um ponteiro para um objeto que contém um sombreador compilado. Geralmente se obtém esse ponteiro através do método (ICarenD3D10Blod::ObterPonteiroBuffer).</param>
			/// <param name="Param_TamanhoSombreador">O Tamanho do sombreador no paramêtro(Param_SombreadorCompilado). Se está compilado com o ICarenD3D10Blod, utilize o método (ObterTamanhoBuffer) para recuperar esse valor.</param>
			/// <param name="Param_ClasseLigação">Um ponteiro para um ICarenD3D11ClassLinkage, que representa a interface de ligação de classe; o valor pode ser NULO.</param>
			/// <param name="Param_ValidarParametros">Se TRUE, o método vai validar os paramêtros de entrada. Se for validado com sucesso, o método retorna SS_FALSE em vez de S_OK.</param>
			/// <param name="Param_Out_ComputeShader">Recebe a interface(ICarenD3D11ComputeShader). Se (Param_ValidarPametros) for TRUE, esse parametro retorna um objeto NULO.</param>
			CarenResult CriarShaderCompute(
				ICaren^ Param_SombreadorCompilado,
				UInt64 Param_TamanhoSombreador,
				ICarenD3D11ClassLinkage^ Param_ClasseLigação,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader);

			/// <summary>
			/// (CreateCounter) - Crie um objeto de contador para medir o desempenho de GPU.
			/// </summary>
			/// <param name="Param_DescContador">Uma estrutura que contém a descrição do contador a ser criado.</param>
			/// <param name="Param_Out_ContadorGPU">Recebe a interface que contem uma descrição do contador.</param>
			CarenResult CriarContador(
				Estruturas::CA_D3D11_DESC_CONTADOR^% Param_DescContador,
				[Out] ICarenD3D11Counter^% Param_Out_ContadorGPU);

			/// <summary>
			/// (CreateDeferredContext) - Cria um contexto diferido, que pode gravar listas de comando.
			/// </summary>
			/// <param name="Param_FlagsContexto">Reservado. Use 0.</param>
			/// <param name="Param_Out_D3D11Contexto">Recebe a interface ICarenD3D11DeviceContext.</param>
			CarenResult CriarContextoDiferido(
				UInt32 Param_FlagsContexto,
				[Out] ICarenD3D11DeviceContext^% Param_Out_D3D11Contexto);

			/// <summary>
			/// (CreateDepthStencilState) - Crie um objeto de estado de profundidade-estêncil que encapsula as informações de teste de profundidade-estêncil para o estágio de saída-fusão.
			/// </summary>
			/// <param name="Param_DepthStencil">Uma estrutura(CA_D3D11_DEPTH_STENCIL_DESC) que descreve o estado de profundidade do Stencil.</param>
			/// <param name="Param_Out_InterfaceStencil">Recebe a interface (ICarenD3D11DepthStencilState) de estado de profundidade do Stencil.</param>
			CarenResult CriarDepthStencilState(
				Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_DepthStencil,
				[Out] ICarenD3D11DepthStencilState^% Param_Out_InterfaceStencil);

			/// <summary>
			/// (CreateDepthStencilView) - Crie uma exibição de profundidade-estêncil para acessar dados de recurso.
			/// </summary>
			/// <param name="Param_Resource">Ponteiro para o recurso que irá servir como a profundidade-superfície estêncil. Este recurso deve ter sido criado com o sinalizador (D3D11_BIND_DEPTH_STENCIL).</param>
			/// <param name="Param_DepthStencilView">Ponteiro para uma descrição de profundidade-estêncil-vista. Defina este parâmetro como NULL para criar uma exibição que acessa o mipmap nível 0 do recurso 
			/// inteiro (usando o recurso foi criado com o formato).</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_InterfaceStencilView retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_InterfaceStencilView">Recebe a interface do Depth Stencil View do D3D11.</param>
			CarenResult CriarDepthStencilView(
				ICarenD3D11Resource^ Param_Resource,
				Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_DepthStencilView,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11DepthStencilView^% Param_Out_InterfaceStencilView
			);

			/// <summary>
			/// (CreateDomainShader) - Crie um sombreador de domínio.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_DomainShader retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_DomainShader">Recebe a interface do Domain Shader.</param>
			CarenResult CriarShaderDomain(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11DomainShader^% Param_Out_DomainShader);

			/// <summary>
			/// (CreateGeometryShader) - Crie um sombreador de geometria.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
			CarenResult CriarShaderGeometry(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader);

			/// <summary>
			/// (CreateGeometryShaderWithStreamOutput) - Cria um sombreador de geometria que pode gravar em streaming de buffers de saída.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_SODeclarationArray">Uma matriz de CA_D3D11_SO_DECLARATION_ENTRY. Não pode ser NULO se Param_NumeroEntradas > 0.</param>
			/// <param name="Param_NumeroEntradas">O número de entradas no fluxo de saída declaração (varia de 0 a D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT).</param>
			/// <param name="Param_BufferStrideArray">Uma matriz de passos de reserva; cada passo é do tamanho de um elemento para o buffer.</param>
			/// <param name="Param_NumeroStrides">O número de passos (ou buffers) em Param_BufferStrideArray (varia de 0 a D3D11_SO_BUFFER_SLOT_COUNT).</param>
			/// <param name="Param_NumeroIndicesFluxo">O número de índice do fluxo a ser enviado para o palco do rasterizador (varia de 0 a D3D11_SO_STREAM_COUNT - 1). Conjunto para D3D11_SO_NO_RASTERIZED_STREAM se nenhum fluxo for ser rasterizada.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
			CarenResult CriarShaderGeometryComSaidaFluxo
			(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				cli::array<Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^>^ Param_SODeclarationArray,
				UInt32 Param_NumeroEntradas,
				cli::array<UInt32>^ Param_BufferStrideArray,
				UInt32 Param_NumeroStrides,
				UInt32 Param_NumeroIndicesFluxo,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader
			);

			/// <summary>
			/// (CreateHullShader) - Crie um sombreador de casco.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
			/// <param name="Param_Out_HullShader">Recebe a interface do Hull Shader.</param>
			CarenResult CriarHullShader(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				[Out] ICarenD3D11HullShader^% Param_Out_HullShader
			);

			/// <summary>
			/// (CreateInputLayout) - Crie um objeto de entrada-layout para descrever os dados do buffer de entrada para o estágio de entrada-montador.
			/// </summary>
			/// <param name="Param_ArrayTiposDadosEntrada">Uma matriz de tipos de dados de entrada do estágio de entrada-montador; cada tipo é descrito por uma descrição do elemento</param>
			/// <param name="Param_CountElementos">O número de tipos de dados de entrada na matriz de elementos de entrada.</param>
			/// <param name="Param_ShaderByteCode">Um ponteiro para o shader compilado. O código compilado de sombreador contém uma assinatura de entrada que é validada contra a matriz de elementos.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Out_InputLayout">Recebe a interface do Input Layout.</param>
			CarenResult CriarObjetoEntradaLayout(
				cli::array<Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^>^ Param_ArrayTiposDadosEntrada,
				UInt32 Param_CountElementos,
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout
			);

			/// <summary>
			/// (CreatePixelShader) - Crie um sombreador de pixel.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_PixelShader retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_PixelShader">Recebe a interface do Hull Shader.</param>
			CarenResult CriarPixelShader(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11PixelShader^% Param_Out_PixelShader);

			/// <summary>
			/// (CreatePredicate) - Cria um predicado.
			/// </summary>
			/// <param name="Param_DescPredicado">Ponteiro para uma descrição de consulta onde o tipo de consulta deve ser uma D3D11_QUERY_SO_OVERFLOW_PREDICATE ou D3D11_QUERY_OCCLUSION_PREDICATE</param>
			/// <param name="Param_Out_Predicado">Recebe a interface do Predicado criado.</param>
			CarenResult CriarPredicado(
				Estruturas::CA_D3D11_QUERY_DESC^% Param_DescPredicado,
				[Out] ICarenD3D11Predicate^% Param_Out_Predicado);

			/// <summary>
			/// (CreateQuery) - Essa interface encapsula métodos para consultar informações da GPU.
			/// </summary>
			/// <param name="Param_DescQuery">Uma descrição da interface de consulta a ser criada.</param>
			/// <param name="Param_Out_Query">Recebe a interface de consulta criada.</param>
			CarenResult CriarQuery(
				Estruturas::CA_D3D11_QUERY_DESC^% Param_DescQuery,
				[Out] ICarenD3D11Query^% Param_Out_Query);

			/// <summary>
			/// (CreateRasterizerState) - Crie um objeto de estado rasterizador que informa o rasterizador de palco como se comportar.
			/// </summary>
			/// <param name="Param_DescRasterizador">Uma estrutura com a descrição do estado do rasterizador.</param>
			/// <param name="Param_Out_Rasterizador">Recebe a interface de Rasterização criada.</param>
			CarenResult CriarEstadoRasterizador(
				Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_DescRasterizador,
				[Out] ICarenD3D11RasterizerState^% Param_Out_Rasterizador);

			/// <summary>
			/// (CreateRenderTargetView) - Cria uma exibição de destino de processamento para acesso a dados de recurso.
			/// </summary>
			/// <param name="Param_Resource">Um ponteiro para interface ID3D11Resource que representa um destino de processamento. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_RENDER_TARGET .</param>
			/// <param name="Param_DescRender">Uma estrutura D3D11_RENDER_TARGET_VIEW_DESC que representa uma descrição do modo de exibição render-alvo. Defina este parâmetro como NULL para criar uma exibição 
			/// que acessa todos os sub-recursos mipmap nível 0.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ViewRender retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_ViewRender">Recebe a interface do visualizador de render.</param>
			CarenResult CriarVisualizadorRenderizacaoDestino(
				ICarenD3D11Resource^ Param_Resource,
				Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11RenderTargetView^% Param_Out_ViewRender);

			/// <summary>
			/// (CreateSamplerState) - Crie um objeto de sampler-estado que encapsula as informações de amostragem para uma textura.
			/// </summary>
			/// <param name="Param_DescSampler">Uma descrição do estado do amostrador</param>
			/// <param name="Param_Out_SamplerState">Recebe a interface do Sampler Sate.</param>
			CarenResult CriarSamplerState(
				Estruturas::CA_D3D11_SAMPLER_DESC^% Param_DescSampler,
				[Out] ICarenD3D11SamplerState^% Param_Out_SamplerState);

			/// <summary>
			/// (CreateShaderResourceView) - Crie uma exibição de sombreador-recurso para acessar dados em um recurso.
			/// </summary>
			/// <param name="Param_Recurso">Ponteiro para o recurso que irá servir como entrada para um sombreador. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_SHADER_RESOURCE .</param>
			/// <param name="Param_DescExbi">Ponteiro para uma descrição de exibição de sombreador-recurso (veja D3D11_SHADER_RESOURCE_VIEW_DESC). Defina este parâmetro como NULL para criar uma 
			/// exibição que acessa o recurso inteiro (usando o recurso foi criado com o formato).</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ShaderView retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_ShaderView">Recebe a interface para o visualizador de Shader.</param>
			CarenResult CriarVisualizadoRescursoShader(
				ICarenD3D11Resource^ Param_Recurso,
				Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_DescExbi,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11ShaderResourceView^% Param_Out_ShaderView);

			/// <summary>
			/// (CreateTexture1D) - Cria uma matriz de texturas 1D.
			/// </summary>
			/// <param name="Param_DescTextura1D">Uma estrutura CA_D3D11_TEXTURE1D_DESC que descreve um recurso de textura 1D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
			/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
			/// mipmap para 0.</param>
			/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 1D. Aplicativos não é possível especificar NULL para 
			/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
			/// quando eles são criados.</param>
			/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura1D retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_Textura1D">Recebe a interface que contém o buffer da interface de Textura 1D.</param>
			CarenResult CriarTextura1D(
				Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_DescTextura1D,
				cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
				UInt32 Param_TamanhoArraySubRecursos,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11Texture1D^% Param_Out_Textura1D);

			/// <summary>
			/// (CreateTexture2D) - Crie uma matriz de texturas 2D.
			/// </summary>
			/// <param name="Param_DescTextura2D">Uma estrutura CA_D3D11_TEXTURE2D_DESC que descreve um recurso de textura 2D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
			/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
			/// mipmap para 0.</param>
			/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 2D. Aplicativos não é possível especificar NULL para 
			/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
			/// quando eles são criados.</param>
			/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura2D retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_Textura2D">Recebe a interface que contém o buffer da interface de Textura 2D.</param>
			CarenResult CriarTextura2D(
				Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_DescTextura2D,
				cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
				UInt32 Param_TamanhoArraySubRecursos,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11Texture2D^% Param_Out_Textura2D);

			/// <summary>
			/// (CreateTexture3D) - Crie uma única textura 3D.
			/// </summary>
			/// <param name="Param_DescTextura3D">Uma estrutura CA_D3D11_TEXTURE3D_DESC que descreve um recurso de textura 3D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
			/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
			/// mipmap para 0.</param>
			/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 3D. Aplicativos não é possível especificar NULL para 
			/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
			/// quando eles são criados.</param>
			/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura3D retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_Textura3D">Recebe a interface que contém o buffer da interface de Textura 3D.</param>
			CarenResult CriarTextura3D(
				Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_DescTextura3D,
				cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
				UInt32 Param_TamanhoArraySubRecursos,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11Texture3D^% Param_Out_Textura3D);

			/// <summary>
			/// (CreateUnorderedAccessView) - Cria uma visão para acessar um recurso de acesso não ordenada.
			/// </summary>
			/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
			/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
			/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
			/// <param name="Param_Out_Interface">Recebe a interface do Recurso de acesso não ordenado.</param>
			CarenResult CriarVisãoRecursoAcessoNaoOrdenado(
				ICarenD3D11Resource^ Param_Recurso,
				Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_DescSombreador,
				[Out] ICarenD3D11UnorderedAccessView^% Param_Out_Interface);

			/// <summary>
			/// (CreateVertexShader) - Crie um objeto shader de vértice de um sombreador compilado.
			/// </summary>
			/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
			/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
			/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
			/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_VertexShaderInterface retorna NULL se esse paramêtro for verdadeiro.</param>
			/// <param name="Param_Out_VertexShader">Recebe a interface do Vertex Shader.</param>
			CarenResult CriarShaderVertice(
				ICaren^ Param_ShaderByteCode,
				UInt64 Param_TamanhoByteCode,
				ICarenD3D11ClassLinkage^ Param_Linkage,
				Boolean Param_ValidarParametros,
				[Out] ICarenD3D11VertexShader^% Param_Out_VertexShader);

			/// <summary>
			/// (GetCreationFlags) - Se os sinalizadores usados durante a chamada para criar o dispositivo com D3D11CreateDevice.
			/// </summary>
			/// <param name="Param_Out_Flags">Recebe um flags de bit a bits da enumerção (CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS) que contém o modo de criaçã do dispositivo.</param>
			CarenResult ObterFlagsCriaçãoDevice([Out] Enumeracoes::CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS% Param_Out_Flags);

			/// <summary>
			/// (GetDeviceRemovedReason) - A razão por que o dispositivo foi removido. Esse método retorna um (ResultCode) informando o motivo.
			/// </summary>
			CarenResult ObterRazãoDispositivoRemovido();

			/// <summary>
			/// (GetExceptionMode) - Obter os sinalizadores de modo de exceção.
			/// </summary>
			/// <param name="Param_Out_Except">Um valor que contém um ou mais sinalizadores de exceção; Cada sinalizador especifica uma condição que fará com que uma exceção seja levantada. Os sinalizadores estão 
			/// listados em D3D11_RAISE_FLAG. Um valor padrão de 0 significa que não há sinalizadores.</param>
			CarenResult ObterSinalizadoresModoExceção([Out] Enumeracoes::CA_D3D11_RAISE_FLAG% Param_Out_Except);

			/// <summary>
			/// (GetFeatureLevel) - Obtém o nível de funcionalidade de dispositivo de hardware.
			/// </summary>
			/// <param name="Param_Out_NivelRecurso">Recebe um flag de bits a bits de um ou mais sinlizadores de niveis de recuso do dispositivo de hardware.</param>
			CarenResult ObterNivelRecurso([Out] Enumeracoes::CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecurso);

			/// <summary>
			/// (GetImmediateContext) - Obtém um contexto imediato, que pode reproduzir listas de comando.
			/// </summary>
			/// <param name="Param_Out_ImediateContextInterface">Recebe a interface do contexto do dispositivo.</param>
			CarenResult ObterContextoImediato([Out] ICarenD3D11DeviceContext^% Param_Out_ImediateContextInterface);

			/// <summary>
			/// (GetPrivateData) - Obtém os dados definidos pelo aplicativo de um dispositivo.
			/// </summary>
			/// <param name="Param_Guid">O Guid associado ao buffer.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer de saida.</param>
			/// <param name="Param_Out_TamanhoBufferSaida">Recebe o tamanho que total do buffer no parametro (Param_Out_Buffer).</param>
			/// <param name="Param_Out_Buffer">Recebe a interface que gerencia o buffer retornado.</param>
			CarenResult ObterDadosPrivados(
				String^ Param_Guid,
				UInt32 Param_TamanhoBuffer,
				[Out] UInt32% Param_Out_TamanhoBufferSaida,
				[Out] ICarenBuffer^% Param_Out_Buffer);

			/// <summary>
			/// (OpenSharedResource) - Dar um dispositivo de acesso a um recurso compartilhado, criado em um dispositivo diferente.
			/// </summary>
			/// <param name="Param_Handle">Um identificador de recurso.</param>
			/// <param name="Param_GuidInterface">O identificador globalmente exclusivo (GUID) para a interface do recurso.</param>
			/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface do recurso que foi ganhado acesso. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult AbrirRecursoCompartilhado(
				IntPtr Param_Handle,
				String^ Param_GuidInterface,
				ICaren^ Param_Out_InterfaceSolicitada);

			/// <summary>
			/// (SetExceptionMode) - Obter os sinalizadores de modo de exceção.
			/// </summary>
			/// <param name="Param_RaiseFlags">Os flags de modo de exceção.</param>
			CarenResult DefinirSinalizadoresModoExceção(UInt32 Param_RaiseFlags);

			/// <summary>
			/// (SetPrivateData) - Define os dados para um dispositivo e associa esses dados a um guid.
			/// </summary>
			/// <param name="Param_Guid">O Guid associado ao buffer.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer de entrada.</param>
			/// <param name="Param_Buffer">Ponteiro para os dados sejam armazenados com este dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer dados anteriormente associados com o 
			/// guid serão destruídos.</param>
			CarenResult DefinirDadosPrivados(
				String^ Param_Guid,
				UInt32 Param_TamanhoBuffer,
				ICarenBuffer^ Param_Buffer);

			/// <summary>
			/// (SetPrivateDataInterface) - Associar uma interface IUnknown-derivado desta criança de dispositivo e associar essa interface com um guid definido pelo aplicativo.
			/// </summary>
			/// <param name="Param_Guid">O Guid associado a interface a ser definida.</param>
			/// <param name="Param_Interface">Ponteiro para uma interface derivada de IUnknown para ser associado ao filho do dispositivo.</param>
			CarenResult DefinirPrivateDataInterface(
				String^ Param_Guid,
				ICaren^ Param_Interface);
		};

		/// <summary>
		/// (ID3D11Device1) - A interface de dispositivo representa um adaptador virtual; é usado para criar recursos. A ICarenD3D11Device1 adiciona novos 
		/// métodos aos da ICarenD3D11Device.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("6BA1CD08-8CEA-45CF-80CB-43AEC30A6F13")]
		public interface class ICarenD3D11Device1 : ICarenD3D11Device
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos


			/// <summary>
			/// (CreateBlendState1) - Cria um objeto de estado-mistura que encapsula o estado de mistura para o estágio de fusão de saída e permite a configuração 
			/// de operações lógicas.
			/// </summary>
			/// <param name="Param_Out_DescBlend">Recebe uma estrutura CA_D3D11_BLEND_DESC1 que descreve o BlendSate(Misturador de estado).</param>
			/// <param name="Param_Out_BlendState">Recebe um ponteiro para a interface ICarenD3D11BlendState1 do misturador de estado.</param>
			CarenResult CriarBlendState1([Out] CA_D3D11_BLEND_DESC1^% Param_Out_DescBlend, [Out] ICarenD3D11BlendState1^% Param_Out_BlendState);

			/// <summary>
			/// (CreateDeferredContext1) - Cria um contexto diferido, que pode gravar listas de comando.
			/// </summary>
			/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
			/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interfcace ICarenD3D11DeviceContext1 do contexto diferido.</param>
			CarenResult CriarContextoDiferido1(UInt32 Param_ContextFlags, [Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoDiferido);

			/// <summary>
			/// (CreateDeviceContextState) - Cria um objeto de estado de contexto que detém todo o estado Microsoft Direct3D e algum comportamento Direct3D.
			/// </summary>
			/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG que são combinados usando uma operação ou bitwise. 
			/// O valor resultante especifica como criar o objeto de estado de contexto. A bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADEDé atualmente é 
			/// a única bandeira definida. Se o dispositivo original foi criado com D3D11_CREATE_DEVICE_SINGLETHREADED, você deve criar todos os objetos de estado 
			/// de contexto daquele dispositivo com a bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADED.</param>
			/// <param name="Param_NiveisRecurso">Uma matriz de valores CA_D3D_FEATURE_LEVEL. A matriz pode conter elementos da lista a seguir e determina a ordem dos 
			/// níveis de recurso para os quais a criação é tentada. Ao contrário do D3D11CreateDevice, você não pode definir (Param_NiveisRecurso) para NULO porque 
			/// não há um array padrão de nível de recurso.</param>
			/// <param name="Param_QuantidadeNiveisRecurso">O número de elementos em (Param_NiveisRecurso). Ao contrário do D3D11CreateDevice, você deve definir os 
			/// Níveis de Recursos para maiores de 0, porque você não pode definir (Param_NiveisRecurso) para NULO.</param>
			/// <param name="Param_VersaoSDK">A versão SDK. Você deve definir este parâmetro para D3D11_SDK_VERSION.</param>
			/// <param name="Param_RIIDInterfaceEmulada">O identificador globalmente único (GUID) para a interface emulada. Esse valor especifica o comportamento do 
			/// dispositivo quando o objeto de estado de contexto está ativo.</param>
			/// <param name="Param_Out_NivelRecursoDefinido">Recebe o nivel de recurso que foi aceito.</param>
			/// <param name="Param_Out_EstadoContextoDispositivo">Recebe um ponteiro para um objeto ICarenD3DDeviceContextState que representa o estado de um dispositivo Direct3D.</param>
			CarenResult CriarDispositivoEstadoContexto(
				CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG Param_Flags, 
				cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso,
				UInt32 Param_QuantidadeNiveisRecurso,
				UInt32 Param_VersaoSDK,
				String^ Param_RIIDInterfaceEmulada,
				[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoDefinido,
				[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoContextoDispositivo);

			/// <summary>
			/// (CreateRasterizerState1) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de 
			/// amostras enquanto o UAV renderiza ou rasteriza.
			/// </summary>
			/// <param name="Param_Out_DescRasterizer">Recebe uma estrutura com a descrição do rasterizador.</param>
			/// <param name="Param_Out_Rasterizador">Recebe um ponteiro para a interface do rasterizador de estado.</param>
			CarenResult CriarEstadoRasterizador1(
				[Out] CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizer, 
				[Out] ICarenD3D11RasterizerState1^% Param_Out_Rasterizador);

			/// <summary>
			/// (GetImmediateContext1) - Obtém um contexto imediato, que pode reproduzir listas de comando.
			/// </summary>
			/// <param name="Param_Out_ContextoImediato">Recebe um ponteiro para a interface ICarenD3D11DeviceContext1 do contexto imediato.</param>
			CarenResult ObterContextoImediato1([Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoImediato);

			/// <summary>
			/// (OpenSharedResource1) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado por uma alça e que foi criado em um dispositivo diferente.
			/// </summary>
			/// <param name="Param_HandleRecurso">Uma Handle para abrir o recurso. </param>
			/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
			/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
			/// não pode ser NULO.</param>
			CarenResult AbrirRecursoCompartilhado1(
				IntPtr Param_HandleRecurso, 
				String^ Param_RIIDInterface, 
				ICaren^% Param_Ref_InterfaceRecurso);

			/// <summary>
			/// (OpenSharedResourceByName) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado pelo nome e que foi criado em um dispositivo 
			/// diferente.
			/// </summary>
			/// <param name="Param_Nome">O nome do recurso para abrir. Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_TipoAcesso">Os direitos de acesso solicitados ao recurso. Você pode utilizar as enumerações CA_ACCESS_RIGHTS e 
			/// CA_DXGI_SHARED_RESOURCE_RW para definir este valor.</param>
			/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
			/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
			/// não pode ser NULO.</param>
			CarenResult AbrirRecursoCompartilhadoPorNome(
				String^ Param_Nome, 
				UInt32 Param_TipoAcesso, 
				String^ Param_RIIDInterface, 
				ICaren^% Param_Ref_InterfaceRecurso);
		};

		/// <summary>
		/// (ID3D11Device2) - A interface de dispositivo representa um adaptador virtual; é usado para criar recursos. A ICarenD3D11Device2 adiciona novos 
		/// métodos aos da ICarenD3D11Device1.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("DB5B3C4A-F2D5-4400-ABD4-12E5BDBE48A6")]
		public interface class ICarenD3D11Device2 : ICarenD3D11Device1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (CheckMultisampleQualityLevels1) - Obtenha o número de níveis de qualidade disponíveis durante a multiamostragem.
			/// </summary>
			/// <param name="Param_Formato">O formato de textura durante a multiamostragem.</param>
			/// <param name="Param_QuantidadeSample">O número de amostras durante a multiamostragem.</param>
			/// <param name="Param_Flags">Uma combinação de D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAGS valores que são combinados usando uma operação ou bitwise. 
			/// Atualmente, apenas D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE é suportado.</param>
			/// <param name="Param_Out_NiveisQualidade">Recebe o número de níveis de qualidade suportados pelo adaptador</param>
			CarenResult ObterNiveisQualidadeDisponiveis1(
				CA_DXGI_FORMAT Param_Formato,
				UInt32 Param_QuantidadeSample,
				CA_D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG Param_Flags,
				[Out] UInt32% Param_Out_NiveisQualidade);

			/// <summary>
			/// (CreateDeferredContext2) - Cria um contexto diferido, que pode gravar listas de comando.
			/// </summary>
			/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
			/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto diferido.</param>
			CarenResult CriarContextoDiferido2(
				UInt32 Param_ContextFlags, 
				[Out] ICarenD3D11DeviceContext2^% Param_Out_ContextoDiferido);

			/// <summary>
			/// (GetImmediateContext2) - Obtém um contexto imediato, que pode reproduzir listas de comando.
			/// </summary>
			/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto imediato.</param>
			CarenResult ObterContextoImediato2([Out] ICarenD3D11DeviceContext2^% Param_Out_Contexto);

			/// <summary>
			/// (GetResourceTiling) - Obtém informações sobre como um recurso de Tiles é dividido em blocos.
			/// </summary>
			/// <param name="Param_Recurso">Um ponteiro para a interface de recurso ICarenD3D11Resource a ser obtida as informações.</param>
			/// <param name="Param_Out_NumeroTilesParaRecurso">Uma variável que recebe o número de Tiles necessárias para armazenar todo o recurso de Tiles.</param>
			/// <param name="Param_Out_DescPackedMip">Uma estrutura CA_D3D11_PACKED_MIP_DESC que o (ObterRecursoTiling) preenche com informações sobre como os 
			/// mipmaps do recurso de Tiles estão embalados.</param>
			/// <param name="Param_Out_DescTileShape">Recebe uma estrutura CA_D3D11_TILE_SHAPE que (ObterRecursoTiling) preenche com informações sobre a forma do bloco. 
			/// São informações sobre como os pixels se encaixam nos blocos, independentemente das dimensões do recurso em Tiles, sem incluir os mipmaps compactados. 
			/// Se todo o recurso lado a lado estiver embalado, esse parâmetro não terá sentido porque o recurso lado a lado não possui layout definido para 
			/// mipmaps compactados. Nessa situação, (ObterRecursoTiling) define os membros de CA_D3D11_TILE_SHAPE como zeros.</param>
			/// <param name="Param_Ref_CountSubrecursoTile">Uma variável que contém o número de Tiles no subrecurso. Na entrada, este é o número de subrecursos para 
			/// consulta de Tiles; na saída, este é o número que foi realmente recuperado em (Param_Out_DescTileShape) (fixado ao que está disponível).</param>
			/// <param name="Param_PrimeiroSubrecursoObter">O número da primeira Tile do subrecursos para obter. (ObterRecursoTiling) ignora este parâmetro se o número 
			/// que o (Param_Ref_CountSubrecursoTile) aponta é 0.</param>
			/// <param name="Param_Out_DescTileSubrecurso">Recebe uma estrutura CA_D3D11_SUBRESOURCE_TILING que o (ObterRecursoTiling) preenche com informações sobre Tile 
			/// de subrecursos.</param>
			CarenResult ObterRecursoTiling(
				ICarenD3D11Resource^ Param_Recurso,
				[Out] UInt32% Param_Out_NumeroTilesParaRecurso,
				[Out] CA_D3D11_PACKED_MIP_DESC^% Param_Out_DescPackedMip,
				[Out] CA_D3D11_TILE_SHAPE^% Param_Out_DescTileShape,
				UInt32% Param_Ref_CountSubrecursoTile,
				UInt32 Param_PrimeiroSubrecursoObter,
				[Out] CA_D3D11_SUBRESOURCE_TILING^% Param_Out_DescTileSubrecurso);
		};

		/// <summary>
		/// (ID3D11Device3) -  A interface de dispositivo representa um adaptador virtual; é usado para criar recursos. A ICarenD3D11Device3 adiciona novos 
		/// métodos aos da ICarenD3D11Device2.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("561668D2-6281-44BF-93C9-B6EF9DBA4FA5")]
		public interface class ICarenD3D11Device3 : ICarenD3D11Device2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (CreateDeferredContext3) - Cria um contexto diferido, que pode gravar listas de comando.
			/// </summary>
			/// <param name="Param_Flags">Reservado para uso futuro. Deixe como ZERO(0).</param>
			/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface do contexto diferido 3.</param>
			CarenResult CriarContextoDiferido3(
				UInt32 Param_Flags, 
				[Out] ICarenD3D11DeviceContext3^% Param_Out_ContextoDiferido);

			/// <summary>
			/// (CreateQuery1) - Cria um objeto de consulta para consulta de informações da unidade de processamento gráfico (GPU).
			/// </summary>
			/// <param name="Param_DescQuery">Uma estrutura CA_D3D11_QUERY_DESC1 que representa uma descrição de consulta.</param>
			/// <param name="Param_Ref_Query">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Query1 para o objeto de consulta criado. Defina este parâmetro como NULO para validar os outros 
			/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarQuery1(
				CA_D3D11_QUERY_DESC1^ Param_DescQuery, 
				ICarenD3D11Query1^% Param_Ref_Query);

			/// <summary>
			/// (CreateRasterizerState2) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de amostras enquanto o UAV renderiza ou rasteriza.
			/// </summary>
			/// <param name="Param_DescRasterizador">Uma estrutura CA_D3D11_RASTERIZER_DESC2 que descreve o estado rasterizador.</param>
			/// <param name="Param_Ref_Rasterizador">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RasterizerState2 para o objeto de estado rasterizador criado. Defina este parâmetro 
			/// como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarEstadoRasterizador2(
				CA_D3D11_RASTERIZER_DESC2^ Param_DescRasterizador, 
				ICarenD3D11RasterizerState2^% Param_Ref_Rasterizador);

			/// <summary>
			/// (CreateRenderTargetView1) - Cria uma visão de destino renderizado para acessar dados de recursos.
			/// </summary>
			/// <param name="Param_Recurso">Ponteiro para a interface ICarenD3D11Resource que representa um destino de renderização. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_RENDER_TARGET.</param>
			/// <param name="Param_DescRenderTarget">Uma estrutura CA_D3D11_RENDER_TARGET_VIEW_DESC1 que representa uma descrição de exibição de destino de renderização. Defina este parâmetro como NULO para criar uma exibição que 
			/// acesse todos os subrecursos no nível 0 do mipmap.</param>
			/// <param name="Param_Ref_RenderTarget">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RenderTargetView1 para a exibição de destino de renderização criada. Defina este 
			/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarVisualizadorRenderizacaoDestino1(
				ICarenD3D11Resource^ Param_Recurso, 
				CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_DescRenderTarget, 
				ICarenD3D11RenderTargetView1^% Param_Ref_RenderTarget);

			/// <summary>
			/// (CreateShaderResourceView1) - Cria uma visão de recursos sombreadores para acessar dados em um recurso.
			/// </summary>
			/// <param name="Param_Recurso">Ponteiro para o recurso que servirá como entrada para um sombreador. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_SHADER_RESOURCE.</param>
			/// <param name="Param_DescShader">Uma estrutura CA_D3D11_SHADER_RESOURCE_VIEW_DESC1 que descreve uma visão de recursos mais sombreados. Defina esse parâmetro como NULO para criar uma exibição que acesse todo o 
			/// recurso (usando o formato com o que o recurso foi criado).</param>
			/// <param name="Param_Ref_Shader">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11ShaderResourceView1 para a exibição de recursos de sombreamento criada. Defina este 
			/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarVisualizadoRescursoShader1(
				ICarenD3D11Resource^ Param_Recurso,
				CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_DescShader,
				ICarenD3D11ShaderResourceView1^% Param_Ref_Shader);

			/// <summary>
			/// (CreateTexture2D1) - Método responsável por criar uma textura 2D.
			/// </summary>
			/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE2D_DESC1 que descreve um recurso de textura 2D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
			/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
			/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 2D. Os aplicativos não podem especificar NULO para 
			/// (Param_DadosSubrecurso) ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
			/// <param name="Param_Ref_Textura2D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture2D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
			/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarTextura2D1(
				CA_D3D11_TEXTURE2D_DESC1^ Param_DescTextura,
				cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
				ICarenD3D11Texture2D1^% Param_Ref_Textura2D);

			/// <summary>
			/// (CreateTexture3D1) - Método responsável por criar uma textura 3D.
			/// </summary>
			/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE3D_DESC1 que descreve um recurso de textura 3D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
			/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
			/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 3D. Os aplicativos não podem especificar NULO para (Param_DadosSubrecurso)
			/// ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
			/// <param name="Param_Ref_Textura3D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture3D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
			/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarTextura3D1(
				CA_D3D11_TEXTURE3D_DESC1^ Param_DescTextura,
				cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
				ICarenD3D11Texture3D1^% Param_Ref_Textura3D);

			/// <summary>
			/// (CreateUnorderedAccessView1) - Cria uma visão para acessar um recurso de acesso não ordenado.
			/// </summary>
			/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
			/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC1) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
			/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
			/// <param name="Param_Ref_ViewUnordered">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11UnorderedAccessView1 para a exibição de acesso não ordenado criada. Defina este 
			/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
			CarenResult CriarVisaoRecursoAcessoNaoOrdenado1(
				ICarenD3D11Resource^ Param_Recurso,
				Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^% Param_DescSombreador,
				ICarenD3D11UnorderedAccessView1^% Param_Ref_ViewUnordered);

			/// <summary>
			/// (GetImmediateContext3) - Obtém um contexto imediato, que pode reproduzir listas de comando.
			/// </summary>
			/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface do contexto imediato ICarenD3D11DeviceContext3.</param>
			CarenResult ObterContextoImediato3([Out] ICarenD3D11DeviceContext3^% Param_Out_Contexto);

			/// <summary>
			/// (ReadFromSubresource) - Copia dados de uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
			/// </summary>
			/// <param name="Param_BufferDestino">Um ponteiro para os dados de destino na memória.</param>
			/// <param name="Param_DestinoPassoLinha">O tamanho de uma linha dos dados de destino.</param>
			/// <param name="Param_DestinoPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de destino.</param>
			/// <param name="Param_RecursoOrigem">Um ponteiro para o recurso de origem.</param>
			/// <param name="Param_IndiceSubrecursoOrigem">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
			/// <param name="Param_CaixaOrigem">Uma caixa que define a parte do subrecurso de destino para copiar os dados de recurso. Se NULO, os dados são lidos do subrecurso destino sem deslocamento. As dimensões do destino 
			/// devem se adequar ao destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, 
			/// ou o valor frontal for maior ou igual ao valor de trás. Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
			CarenResult LerDoSubrecurso(
				ICarenBuffer^ Param_BufferDestino, 
				UInt32 Param_DestinoPassoLinha,
				UInt32 Param_DestinoPassoProfundidade, 
				ICarenD3D11Resource^ Param_RecursoOrigem,
				UInt32 Param_IndiceSubrecursoOrigem,
				CA_D3D11_BOX^ Param_CaixaOrigem);

			/// <summary>
			/// (WriteToSubresource) - Copia dados em uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
			/// </summary>
			/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
			/// <param name="Param_IndiceSubrecursoDestino">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
			/// <param name="Param_CaixaDestino">Uma caixa que define a parte do subrecurso de destino para copiar os dados do recurso em. Se NULO, os dados são gravados no subrecurso destino sem deslocamento. As dimensões da fonte 
			/// devem se encaixar no destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, ou 
			/// o valor frontal for maior ou igual ao valor de trás.Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
			/// <param name="Param_BufferOrigem">Um ponteiro para os dados de origem na memória.</param>
			/// <param name="Param_OrigemPassoLinha">O tamanho de uma linha dos dados de origem.</param>
			/// <param name="Param_OrigemPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de origem.</param>
			CarenResult EscreverParaSubrecurso(
				ICarenD3D11Resource^ Param_RecursoDestino,
				UInt32 Param_IndiceSubrecursoDestino,
				CA_D3D11_BOX^ Param_CaixaDestino,
				ICarenBuffer^ Param_BufferOrigem,
				UInt32 Param_OrigemPassoLinha,
				UInt32 Param_OrigemPassoProfundidade);
		};

		/// <summary>
		/// (ID3D11Device4) - A interface do dispositivo representa um adaptador virtual; é usado para criar recursos. ICarenD3D11Device4 adiciona novos métodos àqueles em ICarenD3D11Device3, como RegisterDeviceRemovedEvent 
		/// e UnregisterDeviceRemoved.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("D2706E04-BFB2-48A4-AF28-181C62294D56")]
		public interface class ICarenD3D11Device4 : ICarenD3D11Device3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (RegisterDeviceRemovedEvent) - Registra o evento "dispositivo removido" e indica quando um dispositivo Direct3D foi removido por qualquer motivo, usando um mecanismo de notificação assíncrona.
			/// </summary>
			/// <param name="Param_HandleEvento">Uma Handle para ser utilizada pelo evento.</param>
			/// <param name="Param_Out_Cookie">Recebe um valor para informações sobre o evento "dispositivo removido", que pode ser usado no (RemoverEvento_DispositivoRemovido) para cancelar o registro do evento.</param>
			CarenResult RegistrarEvento_DispositivoRemovido(
				ICarenWindowsEvent^ Param_HandleEvento, 
				[Out] UInt32 Param_Out_Cookie);

			/// <summary>
			/// (UnregisterDeviceRemoved) - Desregistra o evento "dispositivo removido".
			/// </summary>
			/// <param name="Param_Cookie">Um valor sobre o evento "dispositivo removido", recuperadas durante uma chamada de RegistrarEvento_DispositivoRemovido bem sucedida.</param>
			CarenResult RemoverEvento_DispositivoRemovido(UInt32 Param_Cookie);
		};

		/// <summary>
		/// (ID3D11Device5) - A interface de dispositivo representa um adaptador virtual; é usado para criar recursos. A ICarenD3D11Device5 adiciona novos 
		/// métodos aos da ICarenD3D11Device4.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Representa um adaptador virtual para criar recursos.")]
		[Guid("C497E621-030F-4CEA-AAD2-F3D41BABA516")]
		public interface class ICarenD3D11Device5 : ICarenD3D11Device4
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// (CreateFence) - Cria um objeto de cerca. 
			/// Essa função de membro é equivalente ao Direct3D 12 ID3D12Device::CreateFence função, e se aplica entre Direct3D 11 e Direct3D 12 em cenários interop.
			/// </summary>
			/// <param name="Param_DadosInicias">O valor inicial da cerca.</param>
			/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_FENCE_FLAG que são combinados usando uma operação or bitwise. O valor resultante especifica opções para a vedação.</param>
			/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface de cerca(ICarenD3D11Fence).</param>
			/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence que é usado para acessar a cerca.</param>
			CarenResult CriarFence(
				UInt64 Param_DadosInicias, 
				CA_D3D11_FENCE_FLAG Param_Flags, 
				String^ Param_RIIDInterface, 
				ICarenD3D11Fence^% Param_Ref_FenceInterface);

			/// <summary>
			/// (OpenSharedFence) - Abre uma alça para uma cerca compartilhada usando HANDLE e REFIID. Esta função de membro é uma versão limitada do Direct3D 12 ID3D12Device::OpenSharedHandle função membro, e se aplica entre 
			/// Direct3D 11 e Direct3D 12 em cenários interop.Ao contrário do ID3D12Device::OpenSharedHandle que opera com recursos, montes e cercas, a função ICarenD3D11Device5::AbrirFenceCompartilhado só funciona em cercas; 
			/// no Direct3D 11, os recursos compartilhados são abertos com a função de membro ICarenD3D11Device1::AbrirRecursoCompartilhado1.
			/// </summary>
			/// <param name="Param_Handle">A handle que foi devolvida por uma chamada para ICarenD3D11Fence::CriarHandlerCompartilhada ou ID3D12Device::CreateSharedHandle.</param>
			/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface ICarenD3D11Fence</param>
			/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence.</param>
			CarenResult AbrirFenceCompartilhado(
				IntPtr Param_Handle,
				String^ Param_RIIDInterface,
				ICarenD3D11Fence^% Param_Ref_FenceInterface);
		};

		/// <summary>
		/// (ID3D11Multithread) - Interface responsável por definir se o Dispositivo Direct3D 11 deve trabalhar de forma segura(Thread-Safe) ou não.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Gerenciamento de multihread para o D3D11.")]
		[Guid("6AB993AA-3048-4E03-8E46-462C532963EB")]
		public interface class ICarenD3D11Multithread : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos

			/// <summary>
			/// (Enter) - Entra na sessão crítica de um dispositivo.
			/// </summary>
			void Enter();

			/// <summary>
			/// (GetMultithreadProtected) - Método responsável por verificar se o Multithread está ativado ou não.
			/// </summary>
			Boolean ObterMultithreadProtected();

			/// <summary>
			/// (Leave) - Deixe a seção crítica de um dispositivo.
			/// </summary>
			void Leave();

			/// <summary>
			/// (SetMultithreadProtected) - Método responsável por definir o estado do Multithread.
			/// </summary>
			/// <param name="Param_MultiThread">O estado que deve ser definido o Multithread.</param> 
			Boolean DefinirMultithreadProtected(Boolean Param_MultiThread);
		};

		/// <summary>
		/// (ID3D10Multithread) - Interface responsável por definir se o Dispositivo Direct3D 11 deve trabalhar de forma segura(Thread-Safe) ou não.
		/// </summary>
		[CategoryAttribute("Interface D3D11")]
		[DescriptionAttribute("Gerenciamento de multihread para o D3D11")]
		[Guid("398B3F3F-5062-478E-8E6B-AE1E3E2E1291")]
		public interface class ICarenD3D10Multithread : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}




			/// <summary>
			/// (Enter) - Entra na sessão crítica de um dispositivo.
			/// </summary>
			void Enter();

			/// <summary>
			/// (GetMultithreadProtected) - Método responsável por verificar se o Multithread está ativado ou não.
			/// </summary>
			Boolean ObterMultithreadProtected();

			/// <summary>
			/// (Leave) - Deixe a seção crítica de um dispositivo.
			/// </summary>
			void Leave();

			/// <summary>
			/// (SetMultithreadProtected) - Método responsável por definir o estado do Multithread.
			/// </summary>
			/// <param name="Param_MultiThread">O estado que deve ser definido o Multithread.</param> 
			Boolean DefinirMultithreadProtected(Boolean Param_MultiThread);
		};

		/// <summary>
		/// (IDirect3DDeviceManager9) - Permite que dois threads compartilhem o mesmo dispositivo Direct3D 9 e fornece acesso aos 
		/// recursos do DirectX Video Acceleration (DXVA) do dispositivo.
		/// Essa interface é utilizada pelo Coletor de mídia de video para a alocação das amostras de vídeo.
		/// </summary>
		[CategoryAttribute("Interface D3D9")]
		[DescriptionAttribute("Representa uma interface de acesso ao DXVA(DirectX Video Acceleration).")]
		[Guid("2A4465A5-A6F0-467F-AAEE-673705EB1467")]
		public interface class ICarenDirect3DDeviceManager9 : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			/// <summary>
			/// Fecha um identificador de dispositivo Direct3D.
			/// Chame o método quando você tiver chamado o método (OpenDeviceHandle).
			/// </summary>
			/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
			virtual CarenResult FecharHandleDispositivo(IntPtr Param_Identificador);

			/// <summary>
			/// Obtém uma interface de serviço de aceleração de vídeo DirectX (DXVA).
			/// Obtenha o IID atravez da estrutura: GUIDs_MFDXVAInterfaces.
			/// </summary>
			/// <param name="Param_HandleDirect3D">Um identificador para um dispositivo Direct3D. Para obter um identificador dispositivo, chame o método: OpenDeviceHandle</param>
			/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Essa interface suporta os Seguintes IDs: IID_IDirectXVideoDecoderService, IID_IDirectXVideoProcessorService</param>
			/// <param name="Param_Out_InterfaceSolicitada">Objeto que contém a interface solicitada se o método tiver sido bem sucedido. O usuário deve criar a interface antes de chamar este método.</param>
			virtual CarenResult ObterVideoServiço(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

			/// <summary>
			/// Obtém acesso exclusivo ao dispositivo Direct3D.
			/// </summary>
			/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: OpenDeviceHandle</param>
			/// <param name="Param_Out_Dispositivo">Recebe a interface IDirect3DDevice9[NAO IMPLEMENTADA PELA BIBLIOTECA]. O usuário deve criar a interface antes de chamar este método.</param>
			/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
			/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
			virtual CarenResult LockDispositivo(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, ICaren^ Param_Out_Dispositivo);

			/// <summary>
			/// Obtém um identificador para o dispositivo Direct3D.
			/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (CloseDeviceHandle) para finalizar.
			/// </summary>
			/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
			virtual CarenResult AbirIdentificadorDispositivo3D([Out] IntPtr% Param_Out_Handle);	

			/// <summary>
			/// Define o dispositivo Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado.
			/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método com a interface(ICarenDirect3DDevice9) para o dispositivo Direct3D. 
			/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
			/// </summary>
			/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
			/// <param name="Param_Token">Token recebido no parâmetro pResetToken da função DXVA2CreateDirect3DDeviceManager9.</param>
			virtual CarenResult ResetarDispositivo(ICaren^ Param_Dispostivo3D, UInt32 Param_Token);

			/// <summary>
			/// Testa se um identificador de dispositivo Direct3D é válido.
			/// Se o método retorna ER_DXVA2_HANDLE_INVALIDA, chame o método (CloseDeviceHandle) para fechar o identificador e, em seguida, 
			/// chame (OpenDeviceHandle) novamente para obter um novo identificador. O (ResetDevice) método invalida todos os identificadores de dispositivo aberto.
			/// </summary>
			/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
			virtual CarenResult TestarIdentificadorDispositivo(IntPtr Param_HandleDispositivo3D);

			/// <summary>
			/// Desbloqueia o dispositivo Direct3D.
			/// </summary>
			/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
			/// <param name = "Param_SalvarEstadoDispositivo">Se true, o método salva o estado do dispositivo Direct3D em um bloco de estado. Internamente, o método usa o Direct3D IDirect3DStateBlock9 interface para salvar o estado dispositivo. 
			/// Na próxima vez que você chamar lockdevice com o mesmo identificador de dispositivo, o bloco de estado é restaurado.</param>
			virtual CarenResult UnlockDispositivo(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo);
		};
	}
}