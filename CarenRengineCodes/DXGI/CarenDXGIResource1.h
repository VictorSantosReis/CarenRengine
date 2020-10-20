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
#include "..\SDK_DXGI.h"
#include "..\SDK_Caren.h"
#include "..\SDK_Utilidades.h"

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
/// (Concluido - Fase de Testes) - Classe responsável por estender a interface ICarenDXGIResource adicionando suporte para criar um objeto de 
/// superfície de subrecurso e para criar uma Handle para um recurso compartilhado.
/// </summary>
public ref class CarenDXGIResource1 : public ICarenDXGIResource1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIResource1).
	IDXGIResource1* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenDXGIResource1();


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
	/// <param name="Param_Out_CarenDXGIResource1">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenDXGIResource1^% Param_Out_CarenDXGIResource1)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenDXGIResource1 = gcnew CarenDXGIResource1();

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


	//Métodos da interface(ICarenDXGIResource1)
public:
	/// <summary>
	/// (CreateSharedHandle) - Cria uma Handle para um recurso compartilhado. Em seguida, você pode usar a Handle devolvida com vários dispositivos Direct3D.
	/// </summary>
	/// <param name="Param_Atributos">Uma estrutura CA_ATRIBUTOS_SEGURANCA que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e 
	/// um valor booleano que determina se os processos crianças podem herdar a Handle devolvida.
	/// Defina esse parâmetro para NULO se desejar que os processos filhos que o aplicativo possa criar não herdem a Handle retornado por CriarHandleCompartilhada e se 
	/// desejar que o recurso associado ao identificador retornado obtenha um descritor de segurança padrão.</param>
	/// <param name="Param_Acesso">Os direitos de acesso solicitados ao recurso. Você pode realizar um bitwise entre as enumerações CA_ACCESS_RIGHTS e CA_DXGI_SHARED_RESOURCE_RW 
	/// para definir esse parametro.</param>
	/// <param name="Param_Nome">O nome do recurso para compartilhar. O nome se limita a constante MAX_PATH. A comparação de nomes é sensível ao caso(CaseSensitive).
	/// Você precisará do nome de recurso se ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhadoPorNome para acessar o recurso compartilhado pelo nome. Se você, 
	/// em vez disso, ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhado1 para acessar o recurso compartilhado por cabo, defina este parâmetro para NULO.</param>
	/// <param name="Param_Out_Handle">Recebe o ponteiro para uma variável que recebe o valor NT HANDLE para o recurso para compartilhar. Você pode usar esta Handle em 
	/// chamadas para acessar o recurso.</param>
	virtual CarenResult CriarHandleCompartilhada(
		CA_ATRIBUTOS_SEGURANCA^ Param_Atributos,
		UInt64 Param_Acesso,
		String^ Param_Nome,
		[Out] IntPtr% Param_Out_Handle);

	/// <summary>
	/// (CreateSubresourceSurface) - Cria um objeto de superfície subrecurso.
	/// </summary>
	/// <param name="Param_Index">O índice do objeto de superfície do subrecurso a ser enumerado.</param>
	/// <param name="Param_Out_DXGISurface2">Recebe um ponteiro para uma interface ICarenDXGISurface2 que representa o objeto de superfície do subrecurso criado na posição 
	/// especificada pelo parâmetro (Param_Index).  O usuário deve inicializar a interface antes de chamar este método. </param>
	virtual CarenResult CriarSuperficeSubrecurso(UInt32 Param_Index, ICaren^ Param_Out_DXGISurface2);



	//Métodos da interface(ICarenDXGIResource)
public:
	/// <summary>
	/// (GetEvictionPriority) - Obtenha a prioridade de despejo.
	/// </summary>
	/// <param name="Param_Out_PrioridadeDespejo">Recebe valores da enumeração CA_DXGI_RESOURCE_PRIORITY, que determinam quando o recurso pode ser despejado.</param>
	virtual CarenResult ObterPrioridadeDespejo([Out] CA_DXGI_RESOURCE_PRIORITY% Param_Out_PrioridadeDespejo);

	/// <summary>
	/// (GetSharedHandle) - Obtém a Handle para um recurso compartilhado.
	/// [A partir do Direct3D 11.1, recomendamos não usar o (ObterHandleCompartilhada) mais para recuperar a alça a um recurso compartilhado. Em vez disso, use o 
	/// ICarenDXGIResource1::CriarHandleCompartilhada para obter uma Handle para compartilhar. Para usar o ICarenDXGIResource1::CriarHandleCompartilhada deve especificar 
	/// que ele usa Handle NT (ou seja, você define a bandeira CA_D3D11_RESOURCE_MISC_SHARED_NTHANDLE). Também recomendamos que você crie recursos compartilhados que 
	/// usam Handles NT para que você possa usar CloseHandle, DuplicateHandle, e assim por diante esses recursos compartilhados.]
	/// </summary>
	/// <param name="Param_Out_SharedHandle">Retorna um ponteiro para a Handle compartilhada.</param>
	virtual CarenResult ObterHandleCompartilhada([Out] IntPtr% Param_Out_SharedHandle);

	/// <summary>
	/// (GetUsage) - Obtenha o uso esperado de recursos.
	/// </summary>
	/// <param name="Param_Out_Usage">Recebe uma bandeira de uso(DXGI_USAGE). Para direct3D 10, uma superfície pode ser usada como entrada sombreadora ou uma saída de 
	/// destino renderizado.</param>
	virtual CarenResult ObterUso([Out] CA_DXGI_USAGE% Param_Out_Usage);

	/// <summary>
	/// (SetEvictionPriority) - Defina a prioridade para despejar o recurso da memória.
	/// </summary>
	/// <param name="Param_PrioridadeDespejo">Um valor da enumeração CA_DXGI_RESOURCE_PRIORITY que define a prioridade do despejo.</param>
	virtual CarenResult DefinirPrioridadeDespejo(CA_DXGI_RESOURCE_PRIORITY Param_PrioridadeDespejo);


	//Métodos da interface(ICarenDXGIDeviceSubObject)
public:
	/// <summary>
	/// (GetDevice) - Recupera o dispositivo.
	/// </summary>
	/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
	/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterDispositivo(String^ Param_RIIDInterface, ICaren^ Param_Out_Objeto);


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