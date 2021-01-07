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
#include "../SDK_Direct3D11.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../Caren/CarenBuffer.h"
#include "CarenD3D11Buffer.h"
#include "CarenD3D11SamplerState.h"
#include "CarenD3D11ComputeShader.h"
#include "CarenD3D11DomainShader.h"
#include "CarenD3D11GeometryShader.h"
#include "CarenD3D11PixelShader.h"
#include "CarenD3D11VertexShader.h"
#include "CarenD3D11HullShader.h"
#include "CarenD3D11ClassInstance.h"
#include "CarenD3D11ShaderResourceView.h"
#include "CarenD3D11UnorderedAccessView.h"
#include "CarenD3D11CommandList.h"
#include "CarenD3D11Predicate.h"
#include "CarenD3D11InputLayout.h"
#include "CarenD3D11RenderTargetView.h"
#include "CarenD3D11BlendState.h"
#include "CarenD3D11DepthStencilState.h"
#include "CarenD3D11DepthStencilView.h"
#include "CarenD3D11RasterizerState.h"
#include "CarenD3DDeviceContextState.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct3D11;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um contexto de dispositivo; é usado para realizar comandos de renderização. O ICarenD3D11DeviceContext1 
/// adiciona novos métodos aos do ICarenD3D11DeviceContext.
/// </summary>
public ref class CarenD3D11DeviceContext1 : public ICarenD3D11DeviceContext1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID3D11DeviceContext1).
	ID3D11DeviceContext1* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD3D11DeviceContext1();

	~CarenD3D11DeviceContext1();


	//Conversões implicitas
public:
	static operator CarenD3D11DeviceContext1^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD3D11DeviceContext1^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD3D11DeviceContext1();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID3D11DeviceContext1*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenD3D11DeviceContext1::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenD3D11DeviceContext1)
public:
	/// <summary>
	/// (ClearView) - Define todos os elementos em uma visão de recurso para um valor.
	/// </summary>
	/// <param name="Param_View">Um ponteiro para uma interface ICarenD3D11View que representa a visão de recurso a ser limpa.</param>
	/// <param name="Param_Cor">Um conjunto de 4 componentes(RGBA) que representa a cor para usar para limpar a visão de recurso.</param>
	/// <param name="Param_ArrayRetangulos">Um array de estruturas (CA_RECT) para os retângulos na visão de recursos para limpar. Se NULO, o (ClearView) limpa toda a superfície.</param>
	/// <param name="Param_QuantidadeItems">O número de retângulos no array (Param_ArrayRetangulos).</param>
	virtual CarenResult ClearView(
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
	/// <param name="Param_CopyFlags">Um valor CA_D3D11_COPY_FLAGS que especifica como realizar a operação de cópia. Se você especificar zero para nenhuma opção de cópia, CopySubresourceRegion1 se comporta como ICarenD3D11DeviceContext::CopiarSubRecursoRegiao. Para os drivers de exibição existentes que não podem processar essas bandeiras, o tempo de execução não as usa.</param>
	virtual CarenResult CopySubresourceRegion1(
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
	virtual CarenResult CSGetConstantBuffers1(
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
	virtual CarenResult CSSetConstantBuffers1(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (DiscardResource) - Descarta um recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para a interface de recurso a ser dercartada. O recurso deve ter sido criado com uso D3D11_USAGE_DEFAULT ou D3D11_USAGE_DYNAMIC, 
	/// caso contrário, o tempo de execução derruba a chamada para o (DiscardResource); se a camada de depuração estiver ativada, o tempo de execução retorna uma mensagem de erro.</param>
	virtual CarenResult DiscardResource(ICarenD3D11Resource^ Param_Recurso);

	/// <summary>
	/// (DiscardView) - Descarta uma visão de recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
	/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
	/// retorna uma mensagem de erro.</param>
	virtual CarenResult DiscardView(ICarenD3D11View^ Param_Visão);

	/// <summary>
	/// (DiscardView1) - Descarta os elementos especificados em uma visão de recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
	/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
	/// retorna uma mensagem de erro.</param>
	/// <param name="Param_MatrizRetangulos">Uma matriz de estruturas CA_RECT para os retângulos na visão de recurso para descartar. Se NULO, o DiscardView1 descarta toda a 
	/// visualização e se comporta da mesma forma que o DiscardView.</param>
	/// <param name="Param_NumeroRetangulos">A quantidade de retangulos no array (Param_MatrizRetangulos).</param>
	virtual CarenResult DiscardView1(ICarenD3D11View^ Param_Visão, cli::array<CA_RECT^>^ Param_MatrizRetangulos, UInt32 Param_NumeroRetangulos);

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
	virtual CarenResult DSGetConstantBuffers1(
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
	virtual CarenResult DSSetConstantBuffers1(
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
	virtual CarenResult GSGetConstantBuffers1(
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
	virtual CarenResult GSSetConstantBuffers1(
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
	virtual CarenResult HSGetConstantBuffers1(
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
	virtual CarenResult HSSetConstantBuffers1(
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
	virtual CarenResult PSGetConstantBuffers1(
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
	virtual CarenResult PSSetConstantBuffers1(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (SwapDeviceContextState) - Ativa o objeto de estado de contexto dado e altera o comportamento atual do dispositivo para Direct3D 11, Direct3D 10.1 ou Direct3D 10.
	/// </summary>
	/// <param name="Param_Estado">Um ponteiro para a interface ICarenD3DDeviceContextState para o objeto de estado de contexto que foi criado anteriormente através do método 
	/// ICarenD3D11Device1::CreateDeviceContextState. Se o SwapDeviceContextState for chamado com o (Param_Estado) definido como NULO,a chamada não tem efeito.</param>
	/// <param name="Param_Out_EstadoAnterior">Recebe um ponteiro para a interface ICarenD3DDeviceContextState com o estado do objeto anteriormente ativado.</param>
	virtual CarenResult SwapDeviceContextState(
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
	/// o (UpdateSubresource1) se comporta como ICarenD3D11DeviceContext::UpdateSubresource. Para os drivers de exibição existentes que não podem processar essas bandeiras, 
	/// o tempo de execução não as usa.</param>
	virtual CarenResult UpdateSubresource1(
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
	virtual CarenResult VSGetConstantBuffers1(
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
	virtual CarenResult VSSetConstantBuffers1(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);



	//Métodos da interface(ICarenD3D11DeviceContext)
public:
	/// <summary>
	/// (Begin) - Marca o início de uma série de comandos.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para a interface de sincronização.</param>
	virtual CarenResult Begin(ICarenD3D11Asynchronous^ Param_Async);

	/// <summary>
	/// (ClearDepthStencilView) - Limpa o recurso de profundidade-estêncil.
	/// </summary>
	/// <param name="Param_DepthStencil">Ponteiro para o estêncil de profundidade a ser apurados.</param>
	/// <param name="Param_ClearFlags">Identifica o tipo de dados para limpar </param>
	/// <param name="Param_Depth">Limpe o buffer de profundidade com esse valor. Este valor irá ser fixada entre 0 e 1.</param>
	/// <param name="Param_Stencil">Limpe o buffer de estêncil com esse valor.</param>
	virtual CarenResult ClearDepthStencilView(
		ICarenD3D11DepthStencilView^ Param_DepthStencil,
		Enumeracoes::CA_D3D11_CLEAR_FLAG Param_ClearFlags,
		float Param_Depth,
		Byte Param_Stencil);

	/// <summary>
	/// (ClearRenderTargetView) - Defina todos os elementos em um destino de processamento para um valor.
	/// </summary>
	/// <param name="Param_RenderTarget">Ponteiro para o destino de processamento.</param>
	/// <param name="Param_Cor">Uma estrutura de 4 componentes que representam a cor para preencher o destino de processamento.</param>
	virtual CarenResult ClearRenderTargetView(
		ICarenD3D11RenderTargetView^ Param_RenderTarget,
		Estruturas::CA_DXGI_RGBA^ Param_Cor);

	/// <summary>
	/// (ClearState) - Restaure todas as configurações padrão. 
	/// </summary>
	virtual CarenResult ClearState();

	/// <summary>
	/// (ClearUnorderedAccessViewFloat) - Limpa um recurso de acesso não ordenada, com um valor float.
	/// Essa API funciona em FLOAT, UNORM e SNORM não ordenada acesso visualizações (UAVs), com formato de conversão de FLOAT para * norma se for caso disso. Em outros UAVs, a operação é inválida e a chamada 
	/// não atingirá o driver.
	/// </summary>
	/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
	/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
	virtual CarenResult ClearUnorderedAccessViewFloat(
		ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
		cli::array<float>^ Param_Valores);

	/// <summary>
	/// (ClearUnorderedAccessViewUint) - Limpa um recurso de acesso não ordenada com valores de bit de precisão.
	/// Essa API copia o menor n bits de cada elemento da matriz para o correspondente canalizo, onde n é o número de bits no canal ith do formato de recurso (por exemplo, R8G8B8_FLOAT tem 8 bits para os 3 
	/// primeiros canais). Isto funciona em qualquer UAV com nenhuma conversão de formato. Para uma visão de buffer CRU ou estruturados, somente o primeiro valor de elemento matriz é usado.
	/// </summary>
	/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
	/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
	virtual CarenResult ClearUnorderedAccessViewUint(
		ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
		cli::array<UInt32>^ Param_Valores);

	/// <summary>
	/// (CopyResource) - Copie todo o conteúdo do recurso de fonte para o recurso de destino usando o GPU.
	/// </summary>
	/// <param name="Param_DestinoRecurso">Um ponteiro para a interface ID3D11Resource que representa o DESTINO do recurso.</param>
	/// <param name="Param_OrigemRecurso">Um ponteiro para a interface ID3D11Resource que representa a FONTE de recursos.</param>
	virtual CarenResult CopyResource(
		ICarenD3D11Resource^ Param_DestinoRecurso,
		ICarenD3D11Resource^ Param_OrigemRecurso);

	/// <summary>
	/// (CopyStructureCount) - Copia dados de um buffer de dados de comprimento variável a segurar.
	/// </summary>
	/// <param name="Param_DestinoBuffer">Ponteiro para ID3D11Buffer. Isso pode ser qualquer recurso de buffer que outros comandos de cópia, tais como ICarenD3D11DeviceContext::CopiarRecurso ou 
	/// ICarenD3D11DeviceContext::CopiarSubRecursoRegiao, são capazes de gravar.</param>
	/// <param name="Param_DestinoAlignedOffsetByte">Offset do início do Param_DestinoBuffer para gravar contagem de estrutura(vértice) UINT 32 bits de Param_OrigemView.</param>
	/// <param name="Param_OrigemView">Ponteiro para um ID3D11UnorderedAccessView de um recurso de Buffer estruturado criado com D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER especificado 
	/// quando o UAV foi criado. Esses tipos de recursos tem escondido os contadores foram escritos "Quantos" registros de rastreamento.</param>
	virtual CarenResult CopyStructureCount(
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
	virtual CarenResult CopySubresourceRegion(
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
	virtual CarenResult CSGetConstantBuffers(
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
	virtual CarenResult CSGetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroSamplers,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_SamplersState);

	/// <summary>
	/// (CSGetShader) - Se o sombreador de computação atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_ComputeShader">Retorna uma ponteiro para a interface de Shader Compute.</param>
	/// <param name="Param_Out_ArrayClassInstance">Retorna um Array que contém ponteiros para Instâncias de Classe.</param>
	/// <param name="Param_Out_QuantidadeClass">Retorna a quantidade de itens no array do parametro (Param_Out_ArrayClassInstance).</param>
	virtual CarenResult CSGetShader(
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
	virtual CarenResult CSGetShaderResources(
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
	virtual CarenResult CSGetUnorderedAccessViews(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroUAVs,
		[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizInterfacesNaoOrdenadas);

	/// <summary>
	/// (CSSetConstantBuffers) - Define os constantes buffers usados pela fase computação-shader.
	/// O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
	/// Se o aplicativo deseja o sombreador para acessar outras partes da reserva, ele deve chamar o método CSSetConstantBuffers1 em vez disso.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	virtual CarenResult CSSetConstantBuffers(
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
	virtual CarenResult CSSetSamplers(
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
	virtual CarenResult CSSetShader(
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
	virtual CarenResult CSSetShaderResources(
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
	virtual CarenResult CSSetUnorderedAccessViews(
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
	virtual CarenResult Dispatch(
		UInt32 Param_NumeroGrupoExpedidoX,
		UInt32 Param_NumeroGrupoExpedidoY,
		UInt32 Param_NumeroGrupoExpedidoZ);

	/// <summary>
	/// (DispatchIndirect) - Execute uma lista de comando por um ou mais grupos de discussão.
	/// Você chamar este método para executar comandos em um (Compute Shader).
	/// </summary>
	/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que deve ser carregado com os dados que corresponde à lista de argumento para ICarenD3D11DeviceContext::Dispatch.</param>
	/// <param name="Param_AlinhamentoBytesOffsetForArgs">Um deslocamento de byte alinhado entre o início do buffer e os argumentos.</param>
	virtual CarenResult DispatchIndirect(
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
	virtual CarenResult Draw(
		UInt32 Param_NumeroVertices,
		UInt32 Param_LocalizacaoVertice);

	/// <summary>
	/// (DrawAuto) - Desenhe a geometria de um tamanho desconhecido.
	/// Uma API de desenho envia trabalho para o pipeline de renderização. Esta API submete o trabalho de um tamanho desconhecido que foi processado pelos estágios montador de entrada, sombreador de vértice e 
	/// fluxo-saída; o trabalho pode ou não ter passado pelo estágio de sombreamento de geometria.
	/// </summary>
	virtual CarenResult DrawAuto();

	/// <summary>
	/// (DrawIndexed) - Sorteio indexado, não-instanced primitivos.
	/// Se a soma dos dois índices é negativa, o resultado da chamada de função é indefinido.
	/// </summary>
	/// <param name="Param_NumeroIndices">Número de índices para desenhar.</param>
	/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
	/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
	virtual CarenResult DrawIndexed(
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
	virtual CarenResult DrawIndexedInstanced(
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
	virtual CarenResult DrawIndexedInstancedIndirect(
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
	virtual CarenResult DrawInstanced(
		UInt32 Param_QuantidadeVerticiesPorInstnacia,
		UInt32 Param_QuantidadeInstnacias,
		UInt32 Param_StartVerticeLocalizacao,
		UInt32 Param_StartInstanciaLocalizacao);

	/// <summary>
	/// (DrawInstancedIndirect) - Desenhe primitivos instanciado, gerado pelo GPU.
	/// </summary>
	/// <param name="Param_BufferDadosPrimitivos">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
	/// <param name="Param_DeslocamentoDados">Deslocamento em (Param_BufferDadosPrimitivos) para o início da GPU gerado primitivos.</param>
	virtual CarenResult DrawInstancedIndirect(
		ICarenD3D11Buffer^% Param_BufferDadosPrimitivos,
		UInt32 Param_DeslocamentoDados);

	/// <summary>
	/// (DSGetConstantBuffers) - Obtém os buffers constantes usados por fase de domínio-shader.
	/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	virtual CarenResult DSGetConstantBuffers(
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
	virtual CarenResult DSGetSamplers(
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
	virtual CarenResult DSGetShader(
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
	virtual CarenResult DSGetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_QuantidadeRecursos,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizRecursoShader);

	/// <summary>
	/// (DSSetConstantBuffers) - Define os constantes buffers usados pela fase de domínio-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	virtual CarenResult DSSetConstantBuffers(
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
	virtual CarenResult DSSetSamplers(
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
	virtual CarenResult DSSetShader(
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
	virtual CarenResult DSSetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizRecursoShader);

	/// <summary>
	/// (End) - Marca o fim de uma série de comandos.
	/// Use ICarenD3D11DeviceContext::Begin para marcar o início de uma série de comandos.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para uma interface de ID3D11Asynchronous .</param>
	virtual CarenResult End(ICarenD3D11Asynchronous^ Param_Async);

	/// <summary>
	/// (ExecuteCommandList) - Comandos de filas de uma lista de comandos para um dispositivo.
	/// </summary>
	/// <param name="Param_FilaComandos">Um ponteiro para uma interface ID3D11CommandList que encapsula uma lista de comandos graficos.</param>
	/// <param name="Param_RestaurarEstadoContexto">Um sinalizador booleano que determina se o estado do contexto de destino é salvo antes e restaurado após a execução de uma lista de comandos. Use TRUE para indicar que o tempo de 
	/// execução precisa salvar e restaurar o estado. Use FALSE para indicar que nenhum estado deve ser salvo ou restaurado, o que faz com que o contexto de destino retorne ao seu estado padrão após a 
	/// execução da lista de comandos. Normalmente, os aplicativos devem usar FALSE, a menos que restaurem o estado para ser quase equivalente ao estado que o tempo de execução restauraria se TRUE fosse 
	/// passado. Quando os aplicativos usam FALSE , eles podem evitar transições de estado desnecessárias e ineficientes.</param>
	virtual CarenResult ExecuteCommandList(
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
	virtual CarenResult FinishCommandList(
		Boolean Param_RestDeferidoEstadoContexto,
		[Out] ICarenD3D11CommandList^% Param_Out_FilaComandos);

	/// <summary>
	/// (Flush) - Envia comandos de cima enfileirado no buffer de comandos para a unidade de processamento gráfico (GPU).
	/// </summary>
	virtual CarenResult Flush();

	/// <summary>
	/// (GenerateMips) - Gera mipmaps para o recurso de sombreador determinado.
	/// </summary>
	/// <param name="Param_RecursoSombreador">Um ponteiro para uma interface ICarenD3D11ShaderResourceView que representa o recurso de sombreador.</param>
	virtual CarenResult GenerateMips(ICarenD3D11ShaderResourceView^ Param_RecursoSombreador);

	/// <summary>
	/// (GetContextFlags) - Obtém os sinalizadores de inicialização associados com o atual contexto diferido.
	/// </summary>
	/// <param name="Param_Out_ContextFlags">recebe as bandeiras que foram fornecidos à ContextFlags parâmetro de ICarenD3D11Device::CreateDeferredContext; no entanto, o sinalizador de contexto é reservado para 
	/// uso futuro.</param>
	virtual CarenResult GetContextFlags([Out] UInt32% Param_Out_ContextFlags);

	/// <summary>
	/// (GetData) - Obter dados a partir da unidade de processamento gráfico (GPU) de forma assíncrona.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para uma interface ICarenD3D11Asynchronous para o objeto sobre o qual (GetData) recupera dados.</param>
	/// <param name="Param_Dados">Ponteiro para uma interface de buffer que receberá os dados. Se NULO, (GetData) será usado apenas para verificar o estado. O tipo de saída de dados depende do tipo de interface assíncrona.</param>
	/// <param name="Param_TamanhoDados">Tamanho dos dados a serem recuperados ou 0. Deve ser 0 quando (Param_Dados) for NULO.</param>
	/// <param name="Param_FlagsGetData">Bandeiras opcionais. Pode ser 0 ou qualquer combinação das bandeiras enumeradas por CA_D3D11_ASYNC_GETDATA_FLAG.</param>
	virtual CarenResult GetData(
		ICarenD3D11Asynchronous^ Param_Async,
		ICarenBuffer^% Param_Dados,
		UInt32 Param_TamanhoDados,
		Enumeracoes::CA_D3D11_ASYNC_GETDATA_FLAG Param_FlagsGetData);

	/// <summary>
	/// (GetPredication) - Obtém o estado do predicado de renderização.
	/// </summary>
	/// <param name="Param_Out_Predicado">Recebe um ponteiro para um predicado. O valor armazenado aqui será NULO na criação do dispositivo.</param> 
	/// <param name="Param_Out_ValuePredicado">Recebe um valor booleano para preencher o valor de comparação de predicado. FALSE na criação do dispositivo.</param>
	virtual CarenResult GetPredication(
		[Out] ICarenD3D11Predicate^% Param_Out_Predicado,
		[Out] Boolean% Param_Out_ValuePredicado);

	/// <summary>
	/// (GetResourceMinLOD) - Obtém o mínimo nível de detalhe(LOD).
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para uma interface que represnta um recurso.</param> 
	/// <param name="Param_Out_LODMinimo">Retorna o LOD mínimo.</param> 
	virtual CarenResult GetResourceMinLOD(ICarenD3D11Resource^ Param_Recurso, [Out] float% Param_Out_LODMinimo);

	/// <summary>
	/// (GetType) - Obtém o tipo de contexto de dispositivo.
	/// </summary>
	/// <param name="Param_Out_ContextoDispositivo">Retorna as opções de contexto do dispositivo.</param> 
	virtual CarenResult GetType([Out] Enumeracoes::CA_D3D11_DEVICE_CONTEXT_TYPE% Param_Out_ContextoDispositivo);

	/// <summary>
	/// (GSGetConstantBuffers) - Se os buffers constantes usados pela fase geometria shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	virtual CarenResult GSGetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (GSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de gasoduto de sombreamento de geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	virtual CarenResult GSGetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (GSGetShader) - Obtém o sombreador de geometria atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorGeometria">Retorna uma interface para o sombreador de Geometria.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	virtual CarenResult GSGetShader(
		[Out] ICarenD3D11GeometryShader^% Param_Out_SombreadorGeometria,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (GSGetShaderResources) - Obtém os recursos de geometria obscuros.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	virtual CarenResult GSGetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (GSSetConstantBuffers) - Define os constantes buffers usados pela fase geometria shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	virtual CarenResult GSSetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (GSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline de sombreador geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	virtual CarenResult GSSetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (GSSetShader) - Defina um sombreador de geometria para o dispositivo.
	/// </summary>
	/// <param name="Param_SombreadorGeometria">Ponteiro para um sombreador de Geometria. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	virtual CarenResult GSSetShader(
		ICarenD3D11GeometryShader^ Param_SombreadorGeometria,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (GSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreamento de geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	virtual CarenResult GSSetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (HSGetConstantBuffers) - Se os buffers constantes usados pela fase casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	virtual CarenResult HSGetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (HSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	virtual CarenResult HSGetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (HSGetShader) - Obtém o Sombreador de Casco atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorCasco">Retorna uma interface para o Sombreador de Casco.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	virtual CarenResult HSGetShader(
		[Out] ICarenD3D11HullShader^% Param_Out_SombreadorCasco,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (HSGetShaderResources) - Obtém os recursos do sombreador de casco(Hull).
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	virtual CarenResult HSGetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (HSSetConstantBuffers) - Defina os constantes buffers usados pelo palco casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	virtual CarenResult HSSetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (HSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	virtual CarenResult HSSetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (HSSetShader) - Defina um sombreador de casco para o dispositivo.
	/// </summary>
	/// <param name="Param_SombreadorCasco">Ponteiro para um Sombreador de Casco(Hull). Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	virtual CarenResult HSSetShader(
		ICarenD3D11HullShader^ Param_SombreadorCasco,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (HSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	virtual CarenResult HSSetShaderResources(
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
	virtual CarenResult IAGetIndexBuffer(
		[Out] ICarenD3D11Buffer^% Param_Out_Buffer,
		[Out] Enumeracoes::CA_DXGI_FORMAT% Param_Out_Formato,
		[Out] UInt32% Param_Out_Deslocamento);

	/// <summary>
	/// (IAGetInputLayout) - Obter um ponteiro para o objeto de entrada-layout que está vinculado para o estágio de entrada-montador.
	/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
	/// necessários para vitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_Out_InputLayout">Reretorna um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
	virtual CarenResult IAGetInputLayout([Out] ICarenD3D11InputLayout^% Param_Out_InputLayout);

	/// <summary>
	/// (IAGetPrimitiveTopology) - Obter informações sobre o tipo primitivo e a ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
	/// </summary>
	/// <param name="Param_Out_TipoPrimitivo"></param>
	virtual CarenResult IAGetPrimitiveTopology([Out] Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY% Param_Out_TipoPrimitivo);

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
	virtual CarenResult IAGetVertexBuffers(
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
	virtual CarenResult IASetIndexBuffer(
		ICarenD3D11Buffer^ Param_Buffer,
		Enumeracoes::CA_DXGI_FORMAT Param_Formato,
		UInt32 Param_Deslocamento);

	/// <summary>
	/// (IASetInputLayout) - Vincule um objeto de layout de entrada para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_InputLayout">Um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
	virtual CarenResult IASetInputLayout(ICarenD3D11InputLayout^ Param_InputLayout);

	/// <summary>
	/// (IASetPrimitiveTopology) - Vincule informações sobre o tipo primitivo e ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
	/// </summary>
	/// <param name="Param_TipoPrimitivo">O tipo de primitivo e ordenação dos dados primitivos.</param>
	virtual CarenResult IASetPrimitiveTopology(Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY Param_TipoPrimitivo);

	/// <summary>
	/// (IASetVertexBuffers) - Ligar a uma matriz de buffers de vértice para o estágio de entrada-montador.
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
	virtual CarenResult IASetVertexBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizVertexBuffers,
		cli::array<UInt32>^ Param_MatrizStrides,
		cli::array<UInt32>^ Param_MatrizDeslocamentos);

	/// <summary>
	/// (Map) - Obtém um ponteiro para os dados contidos em um sub-recurso e nega o acesso GPU para aquele sub-recurso.
	/// Esse método também retorna DXGI_ERROR_WAS_STILL_DRAWING se MapFlags especifica D3D11_MAP_FLAG_DO_NOT_WAIT e a GPU ainda não está terminado com o recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para uma interface de ID3D11Resource .</param>
	/// <param name="Param_IndiceSubRecurso">O Indice para o sub-recruso.</param>
	/// <param name="Param_PermissõesAcessoRecurso">Um D3D11_MAP valor digitado que especifica a CPU ler e escrever permissões para um recurso.</param>
	/// <param name="Param_MapFlags">Sinalizador que especifica que a CPU faz quando a GPU está ocupado. Este sinalizador é opcional. Define como (CA_D3D11_MAP_FLAG::Zero) para deixar como opcional.</param>
	/// <param name="Param_Out_RecrusoMapeado">Uma estrutura de CA_D3D11_MAPPED_SUBRESOURCE para o sub-recurso mapeado. Essa estrutura pode ser NULA as vezes. Consulte a documentação.</param>
	virtual CarenResult Map(
		ICarenD3D11Resource^ Param_Recurso,
		UInt32 Param_IndiceSubRecurso,
		Enumeracoes::CA_D3D11_MAP Param_PermissõesAcessoRecurso,
		Enumeracoes::CA_D3D11_MAP_FLAG Param_MapFlags,
		[Out] Estruturas::CA_D3D11_MAPPED_SUBRESOURCE^% Param_Out_RecrusoMapeado);

	/// <summary>
	/// (OMGetBlendState) - Obter o estado de mistura da fase de saída-fusão.
	/// </summary>
	/// <param name="Param_Out_EstadoMitura">Retorna um ponteiro para a interface de estado de mistura.</param>
	/// <param name="Param_Out_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA.</param>
	/// <param name="Param_Out_SampleMask">Retorna um valor para uma máscara de amostra.</param>
	virtual CarenResult OMGetBlendState(
		[Out] ICarenD3D11BlendState^% Param_Out_EstadoMitura,
		[Out] cli::array<float>^% Param_Out_MatrizFatoresMistura,
		[Out] UInt32% Param_Out_SampleMask);

	/// <summary>
	/// (OMGetDepthStencilState) - Obtém o estado de profundidade-estêncil da fase de saída-fusão.
	/// </summary>
	/// <param name="Param_Out_DepthStencilState">Retorna um ponteiro para interface de estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
	/// <param name="Param_Out_StencilRef">Retorna um valor para um estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
	virtual CarenResult OMGetDepthStencilState(
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
	virtual CarenResult OMGetRenderTargets(
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
	/// <param name="Param_UAVStartSlot">ndice em uma matriz baseada em zero para começar a recuperar acesso não ordenada visualizações (varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - 1). 
	/// Para sombreamentos de pixel (Param_UAVStartSlot) deve ser igual ao número de pontos de vista de destino de processamento que estão vinculados.</param>
	/// <param name="Param_NumeroUAVs">Número de pontos de vista de acesso não-ordenados para retornar no ppUnorderedAccessViews. Este número varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - Param_UAVStartSlot.</param>
	/// <param name="Param_IgnorarUnorderedAccessView">Defina (TRUE) para esse parâmetro quando a recuperação de pontos de vista de acesso não-ordenados não é necessária.
	///  O parametro (Param_Out_MatrizUnorderedAccessViews) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_MatrizUnorderedAccessViews">Retorna uma matriz de ICarenD3D11UnorderedAccessViews, que representam vistas de acesso não ordenada que são recuperadas.</param>
	virtual CarenResult OMGetRenderTargetsAndUnorderedAccessViews(
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
	virtual CarenResult OMSetBlendState(
		ICarenD3D11BlendState^ Param_EstadoMitura,
		cli::array<float>^ Param_MatrizFatoresMistura,
		UInt32 Param_SampleMask);

	/// <summary>
	/// (OMSetDepthStencilState) - Define o estado de profundidade-estêncil da fase de saída-fusão.
	/// [Atenção] -> O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
	/// </summary>
	/// <param name="Param_DepthStencilState">Ponteiro para um estado de profundidade-estêncil interface para ligar o dispositivo. Defina NULO para usar o estado padrão listado em D3D11_DEPTH_STENCIL_DESC.</param>
	/// <param name="Param_StencilRef">Valor de referência para executar contra ao fazer um teste de profundidade-estêncil.</param>
	virtual CarenResult OMSetDepthStencilState(
		ICarenD3D11DepthStencilState^ Param_DepthStencilState,
		UInt32 Param_StencilRef);

	/// <summary>
	/// (OMSetRenderTargets) - Ligar um ou mais destinos de processamento atomicamente e a profundidade-estêncil buffer para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_NumeroViews">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas 
	/// na matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro.</param>
	/// <param name="Param_MatizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumViews é 0, não render destinos são vinculados.</param>
	/// <param name="Param_DepthStencilView">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
	virtual CarenResult OMSetRenderTargets(
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
	virtual CarenResult OMSetRenderTargetsAndUnorderedAccessViews(
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
	virtual CarenResult PSGetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (PSGetSamplers) - Obtém uma matriz de Estados amostrador desde a fase de gasoduto de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	virtual CarenResult PSGetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (PSGetShader) -  Obtém o sombreador de pixel atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorPixel">Retorna uma interface para o Sombreador de Pixel.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	virtual CarenResult PSGetShader(
		[Out] ICarenD3D11PixelShader^% Param_Out_SombreadorPixel,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (PSGetShaderResources) - Obter o pixel sombreador recursos.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	virtual CarenResult PSGetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (PSSetConstantBuffers) - Define os constantes buffers usados pela fase de gasoduto do sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param>
	virtual CarenResult PSSetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (PSSetSamplers) - Defina uma matriz de Estados amostrador à fase de gasoduto de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	virtual CarenResult PSSetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (PSSetShader) - Define um sombreador de pixel para o dispositivo.
	/// </summary>
	/// <param name="Param_ShaderPixel">Ponteiro para um Sombreador de Pixel. Passar NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	virtual CarenResult PSSetShader(
		ICarenD3D11PixelShader^ Param_ShaderPixel,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (PSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	virtual CarenResult PSSetShaderResources(
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
	virtual CarenResult ResolveSubresource(
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
	virtual CarenResult RSGetScissorRects(
		[Out] UInt32% Param_Out_NumeroRects,
		Boolean Param_ChecarQuantidade,
		[Out] cli::array<Estruturas::CA_RECT^>^% Param_Out_Rects);

	/// <summary>
	/// (RSGetState) - Obtém o estado do rasterizador do rasterizador estágio do pipeline.
	/// </summary>
	/// <param name="Param_Out_EstadoRasterizador">Um ponteiro para um estado de rasterizador interface para preencher com as informações do dispositivo.</param>
	virtual CarenResult RSGetState([Out] ICarenD3D11RasterizerState^% Param_Out_EstadoRasterizador);

	/// <summary>
	/// (RSGetViewports) - Obtém a matriz de viewports vinculadas à fase rasterizer.
	/// </summary>
	/// <param name="Param_ObterQuantidadeViewports">Define para (TRUE) para obter o número de viewports atualmente definidas. Se (TRUE), Param_Out_MatrizViewports retorna NULO.</param>
	/// <param name="Param_Ref_NumeroViewports">.Na entrada deve definir a quantidade de viewports que seram obtidas. Na saida, ela retorna a quantidade real de viewports retornadas pelo
	/// parametro (Param_Out_MatrizViewports).</param>
	/// <param name="Param_Out_MatrizViewports">Uma matriz de estruturas CA_D3D11_VIEWPORT para as viewports que estão vinculadas à fase do rasterizador.</param>
	virtual CarenResult RSGetViewports(
		Boolean Param_ObterQuantidadeViewports,
		UInt32% Param_Ref_NumeroViewports,
		[Out] cli::array<Estruturas::CA_D3D11_VIEWPORT^>^% Param_Out_MatrizViewports);

	/// <summary>
	/// (RSSetScissorRects) - Vincule uma matriz de retângulos de tesoura para o rasterizador de palco.
	/// </summary>
	/// <param name="Param_NumeroRects">Número de retângulos de tesoura para ligar.</param>
	/// <param name="Param_MatrizRects">Uma matriz de retângulos scissor.</param>
	virtual CarenResult RSSetScissorRects(
		UInt32 Param_NumeroRects,
		cli::array<Estruturas::CA_RECT^>^ Param_MatrizRects);

	/// <summary>
	/// (RSSetState) - Defina o estado do rasterizador para o rasterizador de estágio do pipeline.
	/// </summary>
	/// <param name="Param_EstadoRasterizador">Ponteiro para uma interface de estado rasterizador para vincular ao pipeline.</param>
	virtual CarenResult RSSetState(ICarenD3D11RasterizerState^ Param_EstadoRasterizador);

	/// <summary>
	/// (RSSetViewports) - Ligar a uma matriz de viewports para o rasterizador de estágio do pipeline.
	/// </summary>
	/// <param name="Param_NumeroViewports">Número de viewports para vincular.</param>
	/// <param name="Param_MatrizViewports">Uma matriz de estruturas D3D11_VIEWPORT para vincular ao dispositivo. Consulte a página de estrutura para obter detalhes sobre como o tamanho da viewport depende do nível de recurso do dispositivo que foi alterado 
	/// entre o Direct3D 11 e o Direct3D 10.</param>
	virtual CarenResult RSSetViewports(
		UInt32 Param_NumeroViewports,
		cli::array<Estruturas::CA_D3D11_VIEWPORT^>^ Param_MatrizViewports);

	/// <summary>
	/// (SetPredication) - Defina um predicado de renderização.
	/// </summary>
	/// <param name="Param_Predicate">Um ponteiro para a interface ICarenD3D11Predicate que representa o predicado de renderização. Um valor NULO indica predicação "não"; Nesse caso, o valor de 
	/// (Param_ValorPredicado) é irrelevante, mas será preservado para ICarenD3D11DeviceContext::GetPredication.</param>
	/// <param name="Param_ValorPredicado">Se TRUE, a renderização será afetada quando as condições do predicado forem cumpridas. Se FALSE, a renderização será afetada quando as condições não forem atendidas.</param>
	virtual CarenResult SetPredication(
		ICarenD3D11Predicate^ Param_Predicate,
		Boolean Param_ValorPredicado);

	/// <summary>
	/// (SetResourceMinLOD) - Define o mínimo nível-de-detalhe (LOD) para um recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para um ID3D11Resource que representa o recurso.</param>
	/// <param name="Param_MinLOD">O nível de detalhamento, que varia entre 0 e o número máximo de níveis de mipmap do recurso. Por exemplo, o número máximo de níveis mipmap de uma textura 1D é especificado na 
	/// MipLevels membro do D3D11_TEXTURE1D_DESC estrutura.</param>
	virtual CarenResult SetResourceMinLOD(
		ICarenD3D11Resource^ Param_Recurso,
		float Param_MinLOD);

	/// <summary>
	/// (SOGetTargets) - Obtém os amortecedores de saída alvo para a fase de saída de fluxo do gasoduto.
	/// </summary>
	/// <param name="Param_NumeroBuffers">O número de Buffers a serem obtidos.</param>
	/// <param name="Param_Out_MatrizBuffers">Recebe a matriz com os buffers de saida retornado do dispositivo.</param>
	virtual CarenResult SOGetTargets(
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
	virtual CarenResult SOSetTargets(
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_DeslocamentosBuffers);

	/// <summary>
	/// (unmap) - Invalida o ponteiro para um recurso e reabilita o acesso da GPU para esse recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para o recurso a ser invalido.</param>
	/// <param name="Param_SubrecursoInvalidado">O Id do subrecurso a ser (Desmapeado).</param>
	virtual CarenResult Unmap(
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
	virtual CarenResult UpdateSubresource(
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
	virtual CarenResult VSGetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (VSGetSamplers) - Obter uma matriz de Estados amostrador desde a fase de gasoduto de shader de vértice.
	/// </summary>
	/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	virtual CarenResult VSGetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (VSGetShader) - Obtém o vértice shader atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorVertice">Retorna uma interface para o sombreador de vertice.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	virtual CarenResult VSGetShader(
		[Out] ICarenD3D11VertexShader^% Param_Out_SombreadorVertice,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (VSGetShaderResources) - Obter o vértice shader recursos.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	virtual CarenResult VSGetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (VSSetConstantBuffers) - Define os constantes buffers usados pela fase vértice shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	virtual CarenResult VSSetConstantBuffers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (VSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline vértice shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	virtual CarenResult VSSetSamplers(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (VSSetShader) - Defina um sombreador de vértices para o dispositivo.
	/// </summary>
	/// <param name="Param_ShaderVertice">Ponteiro para um sombreador de vértice. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	virtual CarenResult VSSetShader(
		ICarenD3D11VertexShader^ Param_ShaderVertice,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (VSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de vértices.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	virtual CarenResult VSSetShaderResources(
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);



	//Métodos da interface ICarenD3D11DeviceChild
public:
	/// <summary>
	/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
	/// </summary>
	/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
	/// para transforma em sua interface original.</param>
 virtual CarenResult GetDevice(ICaren^ Param_Out_DispositivoD3D11);

	/// <summary>
	/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com os dados.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
	/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
	/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (GetPrivateData) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
	/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
	virtual CarenResult GetPrivateData(
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		[Out] UInt32% Param_Out_TamanhoBufferSaida,
		[Out] ICarenBuffer^% Param_Out_BufferDados);

	/// <summary>
	/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com os dados.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
	/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
	/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
	virtual CarenResult SetPrivateData(
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
	/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
	virtual CarenResult SetPrivateDataInterface(
		String^ Param_Guid,
		ICaren^ Param_Interface);
};