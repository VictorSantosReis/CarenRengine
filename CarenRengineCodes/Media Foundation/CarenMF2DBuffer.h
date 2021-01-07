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
#include "../Caren/CarenBuffer.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// Representa um buffer que contém uma superfície bidimensional, como um quadro de vídeo.
/// </summary>
public ref class CarenMF2DBuffer : public ICarenMF2DBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMF2DBuffer).
	IMF2DBuffer* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMF2DBuffer();

	~CarenMF2DBuffer();


	//Conversões implicitas
public:
	static operator CarenMF2DBuffer^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMF2DBuffer^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMF2DBuffer();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMF2DBuffer*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMF2DBuffer::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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




	//Métodos da interface(ICarenMF2DBuffer)
public:
	/// <summary>
	/// (ContiguousCopyFrom) - Copia dados para esse buffer de um buffer que tem um formato contíguo(Único).
	/// </summary>
	/// <param name="Param_BufferContiguo">A interface que contém um buffer com os dados contiguou a serem copiados.</param>
	/// <param name="Param_LarguraBuffer">A largura do buffer a ser copiado.</param>
	virtual CarenResult ContiguousCopyFrom(ICarenBuffer^ Param_BufferContiguo, UInt32 Param_LarguraBuffer);

	/// <summary>
	/// (ContiguousCopyTo) - Copia esse buffer no buffer do chamador, convertendo os dados em formato contíguo(Único).
	/// </summary>
	/// <param name="Param_DestinoBufferContiguou">A interface que vai receber o buffer de dados do objeto atual.</param>
	/// <param name="Param_LarguraBufferDestino">O tamanho do buffer de destino. Obtenha esse valor chamando o método (GetContiguousLength).</param>
	virtual CarenResult ContiguousCopyTo(ICarenBuffer^% Param_DestinoBufferContiguou, UInt32 Param_LarguraBufferDestino);

	/// <summary>
	/// (GetContiguousLength) - Recupera o número de bytes necessários para armazenar os dados do buffer 
	/// em formato contíguo.
	/// </summary>
	/// <param name="Param_Out_LarguraBufferContiguou">Recebe a largura do Buffer Contiguou.</param>
	virtual CarenResult GetContiguousLength([Out] UInt32% Param_Out_LarguraBufferContiguou);

	/// <summary>
	/// (GetScanline0AndPitch) - Recupera um ponteiro para a memória de buffer e o Stride da superfície do quadro de vídeo.
	/// Antes de chamar esse método, você deve bloquear o buffer chamando (Lock2D). O valor retornado em (Param_Out_Stride) 
	/// é válido somente enquanto o buffer permanece bloqueado.
	/// </summary>
	/// <param name="Param_Out_ByteBufferPrimeiraLinha">Recebe uma Interface de buffer para o primeiro byte da linha superior de pixels na imagem..</param>
	/// <param name="Param_Out_Stride">Recebe o stride, em bytes.</param>
	virtual CarenResult GetScanline0AndPitch([Out] ICarenBuffer^% Param_Out_ByteBufferPrimeiraLinha, [Out] Int64% Param_Out_Stride);

	/// <summary>
	/// (IsContiguousFormat) - Consulta se o buffer é contíguo em seu (formato nativo).
	/// </summary>
	/// <param name="Param_Out_BufferContiguou">Retorna true se o formato nativo deste buffer é: Contiguou.</param>
	virtual CarenResult IsContiguousFormat([Out] Boolean% Param_Out_BufferContiguou);

	/// <summary>
	/// (Lock2D) - Fornece o acesso do chamador para a memória no buffer.
	/// </summary>
	/// <param name="Param_Out_Buffer">Recebe a interface com o buffer para o primeiro byte da linha superior de pixels na imagem. A linha superior é definida como a 
	/// linha superior quando a imagem é apresentada ao visualizador e pode não ser a primeira linha na memória.</param>
	/// <param name="Param_Out_Stride">Recebe a passada de superfície, em bytes. O passo pode ser negativo, indicando que a 
	/// imagem é orientada de baixo para cima na memória.</param>
	virtual CarenResult Lock2D([Out] ICarenBuffer^% Param_Out_Buffer, [Out] Int64% Param_Out_Stride);

	/// <summary>
	/// (Unlock2D) - Desbloqueia um buffer que foi bloqueado anteriormente. 
	/// Chame esse método uma vez para cada chamada para o método Lock2D.
	/// </summary>
	virtual CarenResult Unlock2D();
};

