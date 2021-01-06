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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsãvel por conter dados de midia. Os tipos podem ser Áudio ou Video.
/// </summary>
public ref class CarenMFMediaBuffer : public ICarenMFMediaBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaBuffer).
	IMFMediaBuffer* PonteiroTrabalho = NULL;



	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaBuffer();

	/// <summary>
	/// Inicializa a classe para gerenciar um buffer de mídia a parti de uma poção de memória alocada do sistema.
	/// </summary>
	/// <param name="Param_Lenght">O tamanho do buffer, em bytes. O valor é alocado da memória do sistema.</param>
	CarenMFMediaBuffer(UInt32 Param_Lenght);

	/// <summary>
	/// Inicializa a classe como um objeto de buffer de memória do sistema para armazenar dados de imagem 2D.
	/// </summary>
	/// <param name="Param_Width">Largura da imagem, em pixels.</param>
	/// <param name="Param_Height">Altura da imagem, em pixels.</param>
	/// <param name="Param_D3DFormat">Um valor CA_D3DFORMAT que especifica o formato de vídeo.</param>
	/// <param name="Param_BottomUp">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. 
	/// Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o DirectX.</param>
	CarenMFMediaBuffer(UInt32 Param_Width, UInt32 Param_Height, CA_D3DFORMAT Param_D3DFormat, Boolean Param_BottomUp);

	/// <summary>
	/// Inicializa a classe como um objeto de buffer de memória do sistema para armazenar dados de imagem 2D.
	/// </summary>
	/// <param name="Param_Width">Largura da imagem, em pixels.</param>
	/// <param name="Param_Height">Altura da imagem, em pixels.</param>
	/// <param name="Param_D3DFormat">Um código FOURCC que especifica o formato de vídeo. Se você tiver um subtipo de vídeo GUID, você pode usar o primeiro DWORD do subtipo.</param>
	/// <param name="Param_BottomUp">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. 
	/// Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o DirectX.</param>
	CarenMFMediaBuffer(UInt32 Param_Width, UInt32 Param_Height, UInt32 Param_FourCC, Boolean Param_BottomUp);

	/// <summary>
	/// Inicializa a classe do buffer de mídia que envolve um buffer de mídia existente. O novo buffer de mídia aponta para a mesma memória do buffer de mídia original, ou para um deslocamento desde o início da memória.
	/// </summary>
	/// <param name="Param_Buffer">Uma interface ICarenMFMediaBuffer do buffer de mídia original.</param>
	/// <param name="Param_Offset">O início do novo buffer, como um offset em bytes do início do buffer original.</param>
	/// <param name="Param_Lenght">O tamanho do novo buffer. O valor de Param_Offset + Param_Lenght deve ser menor ou igual ao tamanho dos dados válidos do buffer original. (O tamanho dos dados válidos é retornado pelo método ICarenMFMediaBuffer::GetCurrentLength.)</param>
	CarenMFMediaBuffer(ICarenMFMediaBuffer^ Param_Buffer, UInt32 Param_Offset, UInt32 Param_Lenght);

	~CarenMFMediaBuffer();


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
			System::Console::WriteLine(String::Concat(ICarenMFMediaBuffer::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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





	//Métodos da interface ICarenMidiabuffer
public:
	/// <summary>
	/// Recupera o comprimento dos dados válidos no buffer.
	/// </summary>
	/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos, em bytes. Se o buffer não contiver nenhum dado válido, o valor será zero.</param>
	virtual CarenResult GetCurrentLength([Out] UInt32% Param_Out_LarguraAtual);


	/// <summary>
	/// Recupera o Dimensionar alocado do buffer. Esse o valor da largura total
	/// de dados que podem ser adicioandos. Se o buffer conter dados, a largura dos dados
	/// podem ser menor que a lagrura máxima. Consulte (GetCurrentLength) para obter o 
	/// valor real da largura dos dados neste Buffer.
	/// </summary>
	/// <param name="Param_Out_LarguraMaxima">Recebe a largura total de dados que esse buffer pode conter.</param>
	virtual CarenResult GetMaxLength([Out] UInt32% Param_Out_LarguraMaxima);


	/// <summary>
	/// Force acesso aos dados que estão presentes neste buffer, para leitura ou gravação.
	/// Esse método fornece o acesso do chamador para o buffer inteiro, até o tamanho máximo retornado no Param_LarguraMaximaEscrita parâmetro. O valor retornado em Param_LarguraAtual 
	/// é o tamanho de todos os dados válidos já no buffer, que pode ser menor do que o tamanho do buffer total.
	/// </summary>
	/// <param name="Param_Out_BufferMidia">Recebe a interface responsável por gerenciar o buffer preso(Lock). Você poder: Write e Read para o buffer.</param>
	/// <param name="Param_Out_LarguraMaximaEscrita">Recebe a quantidade máxima de dados que podem ser gravados para o buffer. Este parâmetro pode ser (NULO).</param>
	/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos no buffer, em bytes. Este parâmetro pode ser (NULO).</param>
	virtual CarenResult Lock([Out] ICarenBuffer^% Param_Out_BufferMidia, [Out] UInt32% Param_Out_LarguraMaximaEscrita, [Out] UInt32% Param_Out_LarguraAtual);


	/// <summary>
	/// Desbloqueia um buffer que foi bloqueado anteriormente. Chame esse método uma vez para cada chamada no método (Lock).
	/// É um erro chamar Unlock se você não chamar Lock anteriormente. Depois de chamar esse método, (Não Use) a interface 
	/// retornada pelo Lock método. Não é mais garantido que o buffer que contenha nela seja valido.
	/// </summary>
	virtual CarenResult Unlock();


	/// <summary>
	/// Define o comprimento dos dados válidos no buffer.
	/// ATENCAO: Chame esse método se você gravar dados no buffer.
	/// </summary>
	/// <param name="Param_LarguraAtual">Comprimento dos dados válidos, em bytes. Esse valor não pode ser maior do que o tamanho alocado do buffer,
	/// que é retornado pelo método (GetMaxLength).</param>
	virtual CarenResult SetCurrentLength(UInt32 Param_LarguraAtual);

};

