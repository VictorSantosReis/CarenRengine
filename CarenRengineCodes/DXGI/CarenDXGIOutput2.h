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
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenDXGIOutputDuplication.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar uma saída de adaptador (como um monitor). A classe adiciona um método em relação 
/// a CarenDXGIOutput1 para verificar se há suporte de sobreposição multiplano no adaptador de saída primária.
/// </summary>
public ref class CarenDXGIOutput2 : public ICarenDXGIOutput2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIOutput2).
	IDXGIOutput2* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenDXGIOutput2();

	~CarenDXGIOutput2();


	//Conversões implicitas
public:
	static operator CarenDXGIOutput2^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenDXGIOutput2^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenDXGIOutput2();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IDXGIOutput2*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenDXGIOutput2::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenDXGIOutput2)
public:
	/// <summary>
	/// (SupportsOverlays) - Consulta uma saída de adaptador para suporte de sobreposição multiplano.
	/// </summary>
	/// <param name="Param_Out_Suporte">Recebe TRUE se o adaptador de saída é o adaptador primário e suporta sobreposições multiplanárias, caso 
	/// contrário retorna FALSE.</param>
	virtual CarenResult SupportsOverlays([Out] Boolean Param_Out_Suporte);


	//Métodos da interface(ICarenDXGIOutput1)
public:
	/// <summary>
	/// (DuplicateOutput) - Cria uma interface de duplicação de desktop a partir da interface ICarenDXGIOutput1 que representa uma saída de 
	/// adaptador.
	/// </summary>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída está conectada.</param>
	/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
	virtual CarenResult DuplicateOutput(ICaren^ Param_Dispositivo3D, [Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada);

	/// <summary>
	/// (FindClosestMatchingMode1) - Encontra o modo de exibição que mais combina com o modo de exibição solicitado.
	/// </summary>
	/// <param name="Param_DescCombine">Uma estrutura CA_DXGI_MODE_DESC1 que descreve o modo de exibição para combinar. Os membros da CA_DXGI_MODE_DESC1 
	/// podem ser não especificados, o que indica que não há preferência por esse membro. Um valor de 0 para Largura ou Altura indica que o valor
	/// não está especificado. Se largura ou altura for 0, ambos devem ser 0. Um numerador e denominador de 0 no RefreshRate indicam que ele não 
	/// está especificado. Outros membros do CA_DXGI_MODE_DESC1 possuem valores de enumeração que indicam que o membro não está especificado. 
	/// Se o (Param_Dispositivo3D) for NULO, o membro (Formato) em CA_DXGI_MODE_DESC1 não pode ser CA_DXGI_FORMAT_UNKNOWN.</param>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro for NULO, o (FindClosestMatchingMode1) 
	/// retorna apenas modos cujo formato corresponde ao do Param_DescCombine; caso contrário, o (FindClosestMatchingMode1) retorna apenas 
	/// aos formatos suportados para escaneamento pelo dispositivo.</param>
	/// <param name="Param_Out_DescCorrespondente"> Recebe uma estrutura CA_DXGI_MODE_DESC1 que contém uma descrição do modo de exibição que 
	/// mais corresponde ao modo de exibição descrito no Param_DescCombine.</param>
	virtual CarenResult FindClosestMatchingMode1(
		CA_DXGI_MODE_DESC1^ Param_DescCombine,
		ICaren^ Param_Dispositivo3D,
		[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente);

	/// <summary>
	/// (GetDisplayModeList1) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
	/// </summary>
	/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
	/// <param name="Param_Flags">Uma combinação de valores CA_DXGI_ENUM_MODES digitados que são combinados usando uma operação ou bitwise. O valor 
	/// resultante especifica opções para modos de exibição para incluir. Você deve especificar CA_DXGI_ENUM_MODES_SCALING para expor os modos 
	/// de exibição que requerem dimensionamento. Os modos centrados que não requerem escala e correspondem diretamente à saída do display são 
	/// enumerados por padrão.</param>
	/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
	/// <param name="Param_Ref_QuantidadeModos">Recebe o número de modos de exibição que o (GetDisplayModeList1) retorna no bloco de memória
	/// para o qual o (Param_Out_MatrizDecModos) aponta. Defina (Param_Out_MatrizDecModos) para NULO para que o (Param_Ref_QuantidadeModos) 
	/// retorne o número de modos de exibição que correspondam ao formato e às opções. Caso contrário, o (Param_Ref_QuantidadeModos) retorna o 
	/// número de modos de exibição devolvidos no (Param_Out_MatrizDecModos).</param>
	/// <param name="Param_Out_MatrizDecModos">Recebe uma lista de modos de exibição.</param>
	virtual CarenResult GetDisplayModeList1(
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_ENUM_MODES Param_Flags,
		Boolean Param_RecuperaQuantidadeModos,
		UInt32% Param_Ref_QuantidadeModos,
		[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDecModos);

	/// <summary>
	/// (GetDisplaySurfaceData1) - Copia a superfície do display(buffer frontal) para um recurso fornecido pelo usuário.
	/// </summary>
	/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
	/// (GetDisplaySurfaceData1) copia a superfície do display. A interface não pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
	virtual CarenResult GetDisplaySurfaceData1(ICarenDXGIResource^ Param_SuperficeDestino);



	//Métodos da interface(ICarenDXGIOutput)
public:
	/// <summary>
	/// (FindClosestMatchingMode) - Encontra o modo de exibição que mais se corresponde ao modo de exibição solicitado.
	/// </summary>
	/// <param name="Param_ModoDesc">O modo de exibição desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC não podem ser especificados indicando nenhuma preferência por esse membro. Um valor de 0 para largura ou altura indica 
	/// que o valor não é especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que não é especificado. Outros membros da DXGI_MODE_DESC têm valores de enumeração indicando 
	/// que o membro não é especificado. Se (Param_Dispositivo3D) é NULO, formatonão pode ser DXGI_FORMAT_UNKNOWN.</param>
	/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro é NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) serão devolvidos; caso contrário, apenas os formatos que 
	/// são suportados para digitalização pelo dispositivo são devolvidos.</param>
	virtual CarenResult FindClosestMatchingMode(CA_DXGI_MODE_DESC^ Param_ModoDesc, [Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, ICaren^ Param_Dispositivo3D);

	/// <summary>
	/// (GetDesc) - Obter uma descrição da saída.
	/// </summary>
	/// <param name="Param_Out_DescSaida">Retorna uma estrutura que contém a descrição da saida.</param>
	virtual CarenResult GetDesc([Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida);

	/// <summary>
	/// (GetDisplayModeList) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
	/// </summary>
	/// <param name="Param_Formato">O formato de cor.</param>
	/// <param name="Param_Flags">Opções para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibição que exigem escala. Os modos centrados, que não exigem escala e correspondentes diretamente à 
	/// saída da tela, são enumerados por padrão.</param>
	/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDescModos). Na saida contém a quantidade de dados de (Param_Out_MatrizDescModos).</param>
	/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
	/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibição.</param>
	virtual CarenResult GetDisplayModeList(
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_ENUM_MODES Param_Flags,
		Boolean Param_RecuperaQuantidadeModos,
		UInt32% Param_Ref_QuantidadeModos,
		[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos);

	/// <summary>
	/// (GetDisplaySurfaceData) - Obtém uma cópia da superfície de exibição atual.
	/// O método só pode ser chamado quando uma saída está no modo de tela cheia. Se o método for bem-sucedido, a DXGI preenche a superfície do destino.
	/// </summary>
	/// <param name="Param_SuperficeDestino">Um ponteiro para uma superfície de destino que vai receber a superfice.</param>
	virtual CarenResult GetDisplaySurfaceData(ICarenDXGISurface^% Param_SuperficeDestino);

	/// <summary>
	/// (GetFrameStatistics) - Obtém estatísticas sobre quadros recentemente renderizados.
	/// </summary>
	/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informações.</param>
	virtual CarenResult GetFrameStatistics([Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame);

	/// <summary>
	/// (GetGammaControl) - Obtém as configurações de controle gama.
	/// </summary>
	/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que contém as informações do controle gamma.</param>
	virtual CarenResult GetGammaControl([Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma);

	/// <summary>
	/// (GetGammaControlCapabilities) - Obtém uma descrição das capacidades de controle gama.
	/// </summary>
	/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que contém as descrições das capcidades do controle Gamma.</param>
	virtual CarenResult GetGammaControlCapabilities([Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps);

	/// <summary>
	/// (ReleaseOwnership) - Libera a propriedade da saída.
	/// </summary>
	virtual CarenResult ReleaseOwnership();

	/// <summary>
	/// (SetDisplaySurface) - Altera o modo de exibição.
	/// </summary>
	/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
	virtual CarenResult SetDisplaySurface(ICarenDXGISurface^% Param_Superfice);

	/// <summary>
	/// (SetGammaControl) - Define os controles gama.
	/// </summary>
	/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
	virtual CarenResult SetGammaControl(CA_DXGI_GAMMA_CONTROL^ Param_ControleGama);

	/// <summary>
	/// (TakeOwnership) - Toma posse de uma saída. Quando você terminar com a saída, chame o método ICarenDXGIOutput::ReleaseOwnership().
	/// Este método não deve ser chamado diretamente por aplicativos, uma vez que os resultados serão imprevisíveis. É chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transições em tela cheia, e não deve ser usado como 
	/// um substituto para métodos de cadeia de swap.
	/// </summary>
	/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
	/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros tópicos ou aplicativos para assumir a propriedade do dispositivo; caso contrário, definido como FALSE.</param>
	virtual CarenResult TakeOwnership(ICaren^ Param_DispositivoD3D, Boolean Param_Exclusivo);

	/// <summary>
	/// (WaitForVBlank ) - Pare um Thread até que o próximo espaço em branco vertical ocorra.
	/// </summary>
	virtual CarenResult WaitForVBlank();



	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// Define uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};