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
#include "../SDK_Windows.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Windows;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Enumeracoes;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// Classe responsável por fornecer acesso sequencial simplificado a objetos de fluxo. ICarenStream deriva seus métodos de leitura e escrita desta classe/interface.
/// </summary>
public ref class CarenSequentialStream : public ICarenSequentialStream
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ISequentialStream).
	ISequentialStream* PonteiroTrabalho = NULL;


	//Contrutor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenSequentialStream();
	
	~CarenSequentialStream();


	//Conversões implicitas
public:
	static operator CarenSequentialStream^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenSequentialStream^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenSequentialStream();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ISequentialStream*>(Param_Pointer.ToPointer());

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
				System::Console::WriteLine(String::Concat(ICarenSequentialStream::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenSequentialStream)
public:
	/// <summary>
	/// Lê um número especificado de bytes do objeto de fluxo para a memória, começando pelo ponteiro de busca atual.
	/// Este método lê bytes deste objeto de fluxo para a memória. O objeto de fluxo deve ser aberto no modo STGM_READ. Este método ajusta o ponteiro de busca pelo número real de bytes lidos.
	/// </summary>
	/// <param name="Param_Out_BufferDest">Uma interface ICarenBuffer que contém o ponteiro de destino dos dados a serem lidos. O usuário é responsável por criar esse buffer.</param>
	/// <param name="Param_CountRead">O número de bytes de dados para ler a partir do objeto de fluxo.</param>
	/// <param name="Param_Ref_TotalReadBytes">Na saída retorna o valor que representa a quantidade de bytes realmente lidos aparti do fluxo.
	/// O número real de bytes lidos pode ser menor do que o número de bytes solicitados se ocorrer um erro ou se o final do fluxo for atingido durante a operação de leitura.</param>
	/// <returns></returns>
	virtual CarenResult Read(ICarenBuffer^ Param_Out_BufferDest, UInt64 Param_CountRead, UInt64% Param_Ref_TotalReadBytes);

	/// <summary>
	/// Grava um número especificado de bytes no objeto de fluxo começando no ponteiro de busca atual.
	/// Write grava os dados especificados em um objeto de fluxo. O ponteiro de busca é ajustado para o número de bytes realmente escritos. O número de bytes realmente escritos é devolvido 
	/// no parâmetro (Param_Ref_TotalWrittenBytes). Se a contagem de bytes é zero bytes, a operação de gravação não tem efeito.
	/// </summary>
	/// <param name="Param_BufferWrite">Uma interface ICarenBuffer que contém um ponteiro para os dados a serem escritos no buffer atual.</param>
	/// <param name="Param_CountWrite">O número de bytes de dados para tentar escrever no fluxo. Esse valor pode ser zero.</param>
	/// <param name="Param_Ref_TotalWrittenBytes">Na saída retorna o valor que representa a quantiade de bytes realmente escritas no fluxo. O parâmetro pode retornar um valor mesmo se ocorrer um erro.</param>
	/// <returns></returns>
	virtual CarenResult Write(ICarenBuffer^ Param_BufferWrite, UInt64 Param_CountWrite, UInt64% Param_Ref_TotalWrittenBytes);
};