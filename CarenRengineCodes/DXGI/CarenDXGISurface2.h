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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de testes) - Classe responsável por estender a interface CarenDXGISurface1 adicionando suporte para superfícies de 
/// subrecursos e obtendo uma alça a um recurso compartilhado. Qualquer objeto que suporte o CarenDXGISurface também suporta 
/// CarenDXGISurface2. 
/// </summary>
public ref class CarenDXGISurface2 : public ICarenDXGISurface2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGISurface2).
	IDXGISurface2* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenDXGISurface2();

	~CarenDXGISurface2();


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
			System::Console::WriteLine(String::Concat(ICarenDXGISurface2::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenDXGISurface2)
public:
	/// <summary>
	/// (GetResource) - Obtém o índice de recursos parentais e subrecursos que suportam uma superfície de subrecursos.
	/// Os objetos atuais que implementam o IDXGISurface são recursos ou visualizações. GetResource para esses objetos retorna "this" ou o 
	/// recurso que suporta a exibição, respectivamente. Nesta situação, o índice de subrecursos é 0.
	/// </summary>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do tipo de interface solicitado.</param>
	/// <param name="Param_Out_ObjetoRecurso">Recebe um ponteiro para um buffer que recebe um ponteiro para o objeto de recurso pai para a superfície do subrecurso.  O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <param name="Param_Ref_IndexSubrecurso">Recebe o índice da superfície do subrecurso.</param>
	virtual CarenResult GetResource(String^ Param_RIID, ICaren^ Param_Out_ObjetoRecurso, UInt32% Param_Ref_IndexSubrecurso);



	//Métodos da interface(ICarenDXGISurface1)
public:
	/// <summary>
	/// (GetDC) - Retorna um contexto de dispositivo (DC) que permite que você se torne uma superfície de Infraestrutura Gráfica Microsoft DirectX (DXGI) usando a Interface do Dispositivo Gráfico windows (GDI).
	/// </summary>
	/// <param name="Param_Descartar">Um valor booleano que especifica se deve preservar o conteúdo Direct3D no GDI DC. 
	/// TRUE direciona o tempo de execução para não preservar o conteúdo Direct3D no GDI DC; ou seja, o tempo de execução 
	/// descarta o conteúdo Direct3D. False garante que o conteúdo Direct3D esteja disponível no GDI DC.</param>
	/// <param name="Param_Out_HDCHandle">Recebe um ponteiro para uma Handle(Alça) HDC que representa o contexto atual do dispositivo para renderização GDI.</param>
	virtual CarenResult GetDC(Boolean Param_Descartar, [Out] IntPtr% Param_Out_HDCHandle);

	/// <summary>
	/// (ReleaseDC) - Libera o contexto do dispositivo GDI (DC) que está associado à superfície atual e permite que você use o Direct3D para renderizar.
	/// </summary>
	/// <param name="Param_Regiao">Um ponteiro para uma estrutura rect que identifica a região suja da superfície. Uma região suja é qualquer 
	/// parte da superfície que você usou para renderização GDI e que você quer preservar.Esta área é usada como uma dica de desempenho para 
	/// subsistema gráfico em certos cenários.Não utilize este parâmetro para restringir a renderização à região retangular especificada. 
	/// Se você passar NULO, ReleaseDC considera toda a superfície como suja. Caso contrário, o (ReleaseDC) usa a área especificada pelo CA_RECT
	/// como uma dica de desempenho para indicar quais áreas foram manipuladas pela renderização GDI. Você pode passar um ponteiro para uma 
	/// estrutura rect vazia(um retângulo sem posição ou área) se você não alterar qualquer conteúdo.</param>
	virtual CarenResult ReleaseDC(CA_RECT^ Param_Regiao);




	//Métodos da interface(ICarenDXGISurface)
public:
	/// <summary>
	/// (GetDesc) - Método responsável por obter uma descrição da superfície.
	/// </summary>
	/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
	virtual CarenResult GetDesc([Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice);

	/// <summary>
	/// (Map) - Método responsável por obter um ponteiro para os dados contidos na superfície e negue o acesso da GPU à superfície.
	/// </summary>
	/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
	/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que contém os dados mapeados da superfice.</param>
	virtual CarenResult Map(CA_DXGI_MAP_FLAGS Param_Flags, [Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado);

	/// <summary>
	/// (Unmap) - Método responsável por invalidar o ponteiro para a superfície recuperada pelo ICarenDXGISurface::Map e 
	/// reativar o acesso GPU ao recurso.
	/// </summary>
	virtual CarenResult Unmap();



	//Métodos da interface(ICarenDXGIDeviceSubObject)
public:
	/// <summary>
	/// Recupera o dispositivo.
	/// </summary>
	/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
	/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetDevice(String^ Param_RIIDInterface, ICaren^ Param_Out_Objeto);


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