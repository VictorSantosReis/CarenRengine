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
#include "../SDK_Direct2D.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responável por descrever um passe de renderização de GPU em um vértice ou sombreador de pixels. É passado para ICarenD2D1DrawTransform.
/// </summary>
public ref class CarenD2D1DrawInfo : public ICarenD2D1DrawInfo
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1DrawInfo).
	ID2D1DrawInfo* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	CarenD2D1DrawInfo();
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	~CarenD2D1DrawInfo();

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
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenD2D1DrawInfo)
public:
	/// <summary>
	/// Defina as instruções do sombreador para esta transformação. 
	/// </summary>
	/// <param name="Param_ShaderId">O ID de recurso para o sombreador.</param>
	/// <param name="Param_PixelOptions">Informações adicionais fornecidas ao renderizador para indicar as operações que o sombreador de pixel faz.</param>
	virtual CarenResult SetPixelShader(
	String^ Param_ShaderId,
	CA_D2D1_PIXEL_OPTIONS Param_PixelOptions);

	/// <summary>
	/// Define o buffer constante para o sombreador de pixels desta transformação. 
	/// </summary>
	/// <param name="Param_Buffer">Os dados aplicados ao buffer constante.</param>
	/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante</param>
	virtual CarenResult SetPixelShaderConstantBuffer(
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Define a textura do recurso correspondente ao índice de textura do sombreador dado. 
	/// </summary>
	/// <param name="Param_IndexTextura">O índice da textura está ligado ao sombreador de pixels.</param>
	/// <param name="Param_ResourceTexture">A textura de recursos criado.</param>
	virtual CarenResult SetResourceTexture(
	UInt32 Param_IndexTextura,
	ICarenD2D1ResourceTexture^ Param_ResourceTexture);

	/// <summary>
	/// Define um buffer de vértice, um sombreador de vértice correspondente e opções para controlar como os vértices devem ser manuseados pelo contexto Direct2D. 
	/// Os sombreadores de vértice associados ao buffer de vértice através do sombreador de vértice GUID devem ter sido carregados através do método ICarenD2D1EffectContext::LoadVertexShader 
	/// antes que esta chamada seja feita.
	/// Se esta chamada falhar, a instância ICarenD2D1Effect correspondente será colocada em um estado de erro e falha ao desenhar.
	/// </summary>
	/// <param name="Param_VertexBuffer">O buffer de vértice, se isso for limpo, será usado o sombreador de vértice padrão e o mapeamento para os retângulos de transformação.</param>
	/// <param name="Param_VertexOptions">Opções que influenciam como o renderizador interagirá com o sombreador de vértice.</param>
	/// <param name="Param_DescricaoBlend">Como os vértices serão misturados com a textura de saída.</param>
	/// <param name="Param_VertexRange">O conjunto de vértices para usar a partir do buffer.</param>
	/// <param name="Param_GuidVertexShader">O GUID do sombreador de vértice.</param>
	virtual CarenResult SetVertexProcessing(
	ICarenD2D1VertexBuffer^ Param_VertexBuffer,
	CA_D2D1_VERTEX_OPTIONS Param_VertexOptions,
	CA_D2D1_BLEND_DESCRIPTION^ Param_DescricaoBlend,
	CA_D2D1_VERTEX_RANGE^ Param_VertexRange,
	String^ Param_GuidVertexShader);

	/// <summary>
	/// Define o buffer constante para o sombreador de vértice desta transformação. 
	/// </summary>
	/// <param name="Param_Buffer">Os dados aplicados ao buffer constante</param>
	/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante.</param>
	virtual CarenResult SetVertexShaderConstantBuffer(
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);


	//Métodos da interface(ICarenD2D1RenderInfo)
public:
	/// <summary>
	/// Especifica que a saída da transformação na qual as informações de renderização estão encapsuladas é ou não armazenada em cache. 
	/// </summary>
	/// <param name="Param_IsCached">TRUE se a saída da transformação for armazenada em cache; caso contrário, FALSO.</param>
	virtual void SetCached(Boolean Param_IsCached);

	/// <summary>
	/// Define como uma entrada específica para a transformação deve ser tratada pelo renderizador em termos de amostragem. 
	/// </summary>
	/// <param name="Param_InputIndex">O índice da entrada que terá a descrição de entrada aplicada.</param>
	/// <param name="Param_InputDescription">A descrição da entrada a ser aplicada à transformação.</param>
	virtual CarenResult SetInputDescription(
		UInt32 Param_InputIndex,
		CA_D2D1_INPUT_DESCRIPTION^ Param_InputDescription);

	/// <summary>
	/// Fornece uma sugestão estimada de custo de execução do sombreador para D2D. 
	/// A contagem de instruções pode ser definida de acordo com o número de instruções no sombreador. Essas informações são usadas como uma dica ao renderizar imagens extremamente grandes. Chamar esta API é opcional, 
	/// mas pode melhorar o desempenho se você fornecer um número preciso.
	/// [NOTA] As instruções que ocorrem em um loop devem ser contadas de acordo com o número de iterações em loop.
	/// </summary>
	/// <param name="Param_InstructionCount">Uma contagem aproximada de instruções do sombreador associado.</param>
	virtual void SetInstructionCountHint(UInt32 Param_InstructionCount);

	/// <summary>
	/// Permite que um chamador controle a precisão de saída e a profundidade do canal da transformação em que as informações de renderização são encapsuladas. 
	/// Se a precisão de saída da transformação não for especificada, ela será padrão para a precisão especificada no contexto do dispositivo Direct2D. O máximo de 16bpc UNORM e 16bpc FLOAT é 32bpc FLOAT.
	/// A profundidade do canal de saída corresponderá ao máximo das profundidades do canal de entrada se a profundidade do canal estiver D2D1_CHANNEL_DEPTH_DEFAULT.
	/// Não há profundidade de canal de saída global, isso é sempre deixado para o controle das transformações.
	/// </summary>
	/// <param name="Param_BufferPrecision">O tipo de buffer que deve ser usado como saída a partir desta transformação.</param>
	/// <param name="Param_ChannelDepth">O número de canais que serão usados no buffer de saída.</param>
	virtual CarenResult SetOutputBuffer(
		CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
		CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth);
};