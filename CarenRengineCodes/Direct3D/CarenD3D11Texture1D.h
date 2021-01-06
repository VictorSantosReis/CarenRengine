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
#include "../Caren/Caren.h"
#include "../Caren/CarenBuffer.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces do Microsoft Direct 3D.
using namespace CarenRengine::Direct3D11;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por acessar dados de Textura 1D, que são de memória estruturada.
/// </summary>
public ref class CarenD3D11Texture1D :public ICarenD3D11Texture1D
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID3D11Texture1D).
	ID3D11Texture1D* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD3D11Texture1D();

	~CarenD3D11Texture1D();


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


	//Cria uma instância da classe
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenD3D11Texture1D">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD3D11Texture1D^% Param_Out_CarenD3D11Texture1D)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenD3D11Texture1D = gcnew CarenD3D11Texture1D();

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
			System::Console::WriteLine(String::Concat(ICarenD3D11Texture1D::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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





	//Métodos da interface proprietaria.
public:
	/// <summary>
	/// (GetDesc) - Obtem as propriedades do recurso de textura.
	/// </summary>
	/// <param name="Param_Out_PropsTextura1D">Retorna uma estrutura com as descrições do recuso.</param>
	virtual CarenResult GetDesc([Out] Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_Out_PropsTextura1D);



	 //Métodos da interface ICarenD3D11Resource
public:
	/// <summary>
	/// (GetEvictionPriority) - Obtém a prioridade de despejo de um recurso.
	/// </summary>
	/// <param name="Param_Out_Prioridade">Retorna a prioridade do recurso que está sendo usado.</param>
	virtual CarenResult GetEvictionPriority([Out] Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO% Param_Out_Prioridade);

	/// <summary>
	/// (GetType) - Obtém o tipo de recurso.
	/// </summary>
	/// <param name="Param_Out_TipoRecurso">Retorna o tipo do recurso usado.</param>
	virtual CarenResult GetType([Out] Enumeracoes::CA_D3D11_TIPO_RECURSO% Param_Out_TipoRecurso);

	/// <summary>
	/// (SetEvictionPriority) - Define a prioridade de despejo de um recurso.
	/// Prioridades de recursos determinam qual recurso despejo de memória de vídeo quando o sistema ficou sem memória de vídeo. O recurso não será perdido; será removido da memória de vídeo e colocado na 
	/// memória do sistema ou possivelmente colocado no disco rígido. O recurso será carregado volta na memória de vídeo quando for necessário.
	/// </summary>
	/// <param name="Param_PrioridadeRecurso">Define o tipo do recurso sendo usado.</param>
	virtual CarenResult SetEvictionPriority(Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO Param_PrioridadeRecurso);





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

