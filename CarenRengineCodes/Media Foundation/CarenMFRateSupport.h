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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de testes) - Classe responsável por consultar o intervalo de taxas de reprodução que são suportadas, incluindo a reprodução inversa.
/// pela biblioteca.
/// </summary>
public ref class CarenMFRateSupport :public ICarenMFRateSupport
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFRateSupport).
	IMFRateSupport* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenMFRateSupport();


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
	/// <param name="Param_Out_RateSuporte">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMFRateSupport^% Param_Out_RateSuporte)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_RateSuporte = gcnew CarenMFRateSupport();

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



	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// (GetFastestRate) - Obtém a taxa de reprodução mais rápida suportada pelo objeto.
	/// </summary>
	/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução de encaminhamento mais rápida ou a taxa de reprodução inversa.</param>
	/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução mais rápida diluído. Caso contrário, o método recupera o mais rápido não-diluído taxa de reprodução. 
	/// Para alguns formatos (como ASF), desbaste significa descartar todos os quadros que não são I-frames. Se um componente produz dados de fluxo, como uma fonte de mídia ou um 
	/// demultiplexer, ele deve prestar atenção para o (Param_Thin) parâmetro e retornar MF_E_THINNING_UNSUPPORTED se ele não é possível Thin o fluxo.</param>
	/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais rápida que o objeto oferece suporte.</param>
	virtual CarenResult GetFastestRate(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao);

	/// <summary>
	/// (GetSlowestRate) - Recupera a taxa de reprodução mais lenta suportada pelo objeto.
	/// </summary>
	/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução direta mais lenta ou a taxa de reprodução inversa.</param>
	/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução diluído mais lenta. Caso contrário, o método recupera a taxa de reprodução mais lenta não Diluível. 
	/// O valor retornado em Plfrate representa um limite inferior. A reprodução a esta taxa não é garantida. Chame ICarenMFRateSupport::SuporteTaxa para verificar se a taxa de limite 
	/// é suportado. Por exemplo, um componente que ofereça suporte a taxas arbitrariamente lentas retornará zero em (Param_Out_TaxaReproducao), e os aplicativos devem chamar 
	/// (SuporteTaxa) separadamente para determinar se o componente oferece suporte à taxa 0.</param>
	/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais lenta que o objeto oferece suporte.</param>
	virtual CarenResult GetSlowestRate(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao);

	/// <summary>
	/// (IsRateSupported) - Consulta se o objeto oferece suporte a uma taxa de reprodução especificada.
	/// </summary>
	/// <param name="Param_Thin">Se true, o método consulta se o objeto oferece suporte a taxa de reprodução com desbaste. Caso contrário, o método consultará se o objeto suporta a taxa de 
	/// reprodução sem desbaste.</param>
	/// <param name="Param_Taxa">A taxa de reprodução para consulta.</param>
	/// <param name="Param_Out_TaxaSuportada">Se o objeto não suportar a taxa de reprodução fornecida em (Param_Taxa), esse parâmetro receberá a taxa de reprodução suportada mais próxima. 
	/// Se o método retorna SS_OK, esse parâmetro recebe o valor fornecido em (Param_Taxa).</param>
	virtual CarenResult IsRateSupported(Boolean Param_Thin, float Param_Taxa, [Out] float% Param_Out_TaxaSuportada);
};

