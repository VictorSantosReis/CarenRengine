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
#include "CarenD2D1Image.h"
#include "CarenD2D1Properties.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por representar um construtor básico de processamento de imagem no Direct2D.
/// </summary>
public ref class CarenD2D1Effect : public ICarenD2D1Effect
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Effect).
	ID2D1Effect* PonteiroTrabalho = NULL;


	//Contrutor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1Effect();
	
	~CarenD2D1Effect();


	//Conversões implicitas
public:
	static operator CarenD2D1Effect^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1Effect^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1Effect();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1Effect*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;


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
			System::Console::WriteLine(String::Concat(ICarenD2D1Effect::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1Effect)
public:
	/// <summary>
	/// Obtém a imagem de entrada dada por índice. 
	/// </summary>
	/// <param name="Param_Index">O índice da imagem para recuperar.</param>
	/// <param name="Param_Out_Entrada">Quando este método retorna, contém o endereço de um ponteiro para a imagem identificada pelo (Param_Index).</param>
	virtual void GetInput(
	UInt32 Param_Index,
	[Out] ICarenD2D1Image^% Param_Out_Entrada);

	/// <summary>
	/// Obtém o número de entradas para o efeito. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de entradas ao efeito.</param>
	virtual void GetInputCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtém a imagem de saída do efeito. 
	/// A imagem de saída pode ser definida como uma entrada para outro efeito, ou pode ser transmitida diretamente para o ICarenD2D1DeviceContext, a fim de tornar o efeito.
	/// Também é possível usar o (ICaren::ConsultarInterface) para recuperar a mesma imagem de saída.
	/// </summary>
	/// <param name="Param_Out_SaidaImagem">Quando este método retorna, contém o endereço de um ponteiro para a imagem de saída para o efeito.</param>
	virtual void GetOutput([Out] ICarenD2D1Image^% Param_Out_SaidaImagem);

	/// <summary>
	/// Define a imagem de entrada dada por índice. 
	/// Se o índice de entrada estiver fora de alcance, a imagem de entrada será ignorada.
	/// </summary>
	/// <param name="Param_Index">O índice da imagem a definir.</param>
	/// <param name="Param_Entrada">A imagem de entrada a ser definida.</param>
	/// <param name="Param_Invalidar">Se invalidar o gráfico na localização da entrada de efeito</param>
	virtual void SetInput(
	UInt32 Param_Index,
	ICarenD2D1Image^ Param_Entrada,
	Boolean Param_Invalidar);

	/// <summary>
	/// Permite que o aplicativo altere o número de entradas para um efeito. 
	/// A maioria dos efeitos não suporta um número variável de entradas. Use ICarenD2D1Properties::GetValue com os valores D2D1_PROPERTY_MIN_INPUTS e D2D1_PROPERTY_MAX_INPUTS
	/// para determinar o número de entradas suportadas por um efeito.
	/// Se o método falhar, a contagem de entrada e entrada existente permanecerá inalterada.
	/// </summary>
	/// <param name="Param_Quantidade">O número de entradas para o efeito.</param>
	virtual CarenResult SetInputCount(UInt32 Param_Quantidade);

	/// <summary>
	/// Define o efeito de entrada dado por índice. 
	/// Este método obtém a saída do efeito dado e, em seguida, passa a imagem de saída para o método SetInput.
	/// </summary>
	/// <param name="Param_Index">O índice da entrada para definir.</param>
	/// <param name="Param_EfeitoEntrada">O efeito de entrada a ser definido.</param>
	/// <param name="Param_Invalidar">Se invalidar o gráfico na localização da entrada de efeito</param>
	virtual void SetInputEffect(
	UInt32 Param_Index,
	ICarenD2D1Effect^ Param_EfeitoEntrada,
	Boolean Param_Invalidar);



	//Métodos da interface(ICarenD2D1Properties)
public:
	/// <summary>
	/// Obtém o número de propriedades de alto nível. 
	/// </summary>
	/// <param name="Param_Out_Quantidade"> retorna o número de propriedades personalizadas (não-sistema) que podem ser acessadas pelo objeto.</param>
	virtual void GetPropertyCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtém o índice correspondente ao nome da propriedade dada.
	/// Se a propriedade não existe, então esse método retorna D2D1_INVALID_PROPERTY_INDEX. Esse valor reservado nunca irá mapear para um índice válido, e fará com 
	/// que os valores NULO ou sentinela sejam devolvidos 
	/// de outras partes da interface da propriedade.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para recuperar.</param>
	/// <param name="Param_Out_Index">Retorna o índice do nome da propriedade correspondente.</param>
	virtual void GetPropertyIndex(
		String^ Param_NomePropriedade,
		[Out] UInt32% Param_Out_Index);

	/// <summary>
	/// Obtém o nome da propriedade que corresponde ao índice dado.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para a qual o nome está sendo devolvido.</param>
	/// <param name="Param_Out_Nome">Quando este método retorna, contém o nome que está sendo recuperado.</param>
	/// <param name="Param_SizeNome">O número de caracteres no (Param_Out_Nome).</param>
	virtual CarenResult GetPropertyName(
		UInt32 Param_Index,
		[Out] String^% Param_Out_Nome,
		UInt32 Param_SizeNome);

	/// <summary>
	/// Obtém o número de caracteres para o nome da propriedade dado. 
	/// </summary>
	/// <param name="Param_Index">O índice do nome da propriedade para recuperar.</param>
	/// <param name="Param_Out_SizeNome">Retorna o tamanho em caracteres do nome correspondente ao índice de propriedade dado, ou zero se o índice de propriedade não existir.</param>
	virtual void GetPropertyNameLength(
		UInt32 Param_Index,
		[Out] UInt32% Param_Out_SizeNome);

	/// <summary>
	/// Obtém as sub propriedades da propriedade fornecida por índice. 
	/// </summary>
	/// <param name="Param_Index">O índice das sub propriedades a serem recuperadas.</param>
	/// <param name="Param_Out_SubPropriedades">Quando este método retorna, contém um ponteiro para as subpropriedades na interface (ICarenD2D1Properties).</param>
	virtual CarenResult GetSubProperties(
		UInt32 Param_Index,
		[Out] ICarenD2D1Properties^% Param_Out_SubPropriedades);

	/// <summary>
	/// Obtém a D2D1_PROPERTY_TYPE da propriedade selecionada. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para o qual o tipo será recuperado.</param>
	/// <param name="Param_Out_Tipo">Retorna um enum(CA_D2D1_PROPERTY_TYPE) para o tipo da propriedade.</param>
	virtual void GetType(
		UInt32 Param_Index,
		[Out] CA_D2D1_PROPERTY_TYPE% Param_Out_Tipo);

	/// <summary>
	/// Obtém o valor da propriedade especificada por índice. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValue(
		UInt32 Param_Index,
		CA_D2D1_PROPERTY_TYPE Param_Tipo,
		[Out] ICarenBuffer^% Param_Out_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade especificada por índice.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValue(
		UInt32 Param_Index,
		[Out] ICarenBuffer^% Param_Out_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade pelo nome.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValueByName(
		String^ Param_NomePropriedade,
		CA_D2D1_PROPERTY_TYPE Param_Tipo,
		[Out] ICarenBuffer^% Param_Out_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade pelo nome.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValueByName(
		String^ Param_NomePropriedade,
		[Out] ICarenBuffer^% Param_Out_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o tamanho do valor da propriedade em bytes, usando o índice de propriedade. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade.</param>
	/// <param name="Param_Out_Size">Retorna o tamanho do valor em bytes, usando o índice de propriedade</param>
	virtual void GetValueSize(
		UInt32 Param_Index,
		[Out] UInt32% Param_Out_Size);

	/// <summary>
	/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
	/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para definir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValue(
		UInt32 Param_Index,
		CA_D2D1_PROPERTY_TYPE Param_Tipo,
		ICarenBuffer^ Param_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
	/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para definir.</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValue(
		UInt32 Param_Index,
		ICarenBuffer^ Param_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade nomeada ao valor dado. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValueByName(
		String^ Param_NomePropriedade,
		CA_D2D1_PROPERTY_TYPE Param_Tipo,
		ICarenBuffer^ Param_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade nomeada ao valor dado. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValueByName(
		String^ Param_NomePropriedade,
		ICarenBuffer^ Param_Buffer,
		UInt32 Param_BufferSize);

	/// <summary>
	/// (Templete - SetValueByName(PCWSTR,T)) - Define a propriedade nomeada ao valor dado. Esta é uma sobrecarga de modelo. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Valor">Os dados a serem definidos. Como o método converte os dados para um BYTE*, não a necessidade de um ICaren.</param>
	virtual CarenResult SetValueByName(
		String^ Param_NomePropriedade,
		ICarenBuffer^ Param_Valor);
};