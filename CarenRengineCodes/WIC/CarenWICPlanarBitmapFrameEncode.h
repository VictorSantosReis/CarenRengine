﻿/*
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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por permitir que pixels de imagem de componente planar sejam gravados em um codificador.
/// </summary>
public ref class CarenWICPlanarBitmapFrameEncode : public ICarenWICPlanarBitmapFrameEncode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICPlanarBitmapFrameEncode).
	IWICPlanarBitmapFrameEncode* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICPlanarBitmapFrameEncode();
	
	~CarenWICPlanarBitmapFrameEncode();


	//Conversões implicitas
public:
	static operator CarenWICPlanarBitmapFrameEncode^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICPlanarBitmapFrameEncode^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICPlanarBitmapFrameEncode();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICPlanarBitmapFrameEncode*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenWICPlanarBitmapFrameEncode::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICPlanarBitmapFrameEncode)
public:
	/// <summary>
	/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
	/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
	/// As chamadas WritePixels sucessivas são assumidas adicionando linhas de varredura sequencialmente à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
	/// e ICarenWICBitmapFrameEncode::SetPixelFormat devem ser chamados antes deste método ou ele falhará.
	/// O formato de pixel intercalado definido via ICarenWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
	/// </summary>
	/// <param name="Param_LineCount">O número de linhas para codificar. Consulte a seção Observações para restrições específicas de contagem de linhas do WIC Jpeg.</param>
	/// <param name="Param_Planes">Especifica os buffers de origem para cada plano componente codificado.</param>
	/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_Planes).</param>
	virtual CarenResult WritePixels(
	UInt32 Param_LineCount,
	cli::array<CA_WICBitmapPlane^>^ Param_Planes,
	UInt32 Param_QuantidadePlanes);

	/// <summary>
	/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
	/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
	/// Sucessivas chamadas WriteSource são assumidas sequencialmente adicionando linhas de varredura à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
	/// e ICarenWICBitmapFrameEncode::SetPixelFormat deve ser chamado antes deste método ou ele falhará.
	/// O formato de pixel intercalado definido via IWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
	/// </summary>
	/// <param name="Param_ArrayPlanes">Especifica uma matriz de interface (ICarenWICBitmapSource) que representam planos de imagem.</param>
	/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_ArrayPlanes).</param>
	/// <param name="Param_RetanguloOrigem">O retângulo de origem de pixels para codificar a partir dos planos ICarenWICBitmapSource. Nulo indica toda a fonte. A largura de retificada de origem 
	/// deve corresponder à largura definida através do SetSize. Chamadas repetidas do WriteSource podem ser feitas desde que a altura total acumulada do retifice seja a mesma definida através do SetSize.</param>
	virtual CarenResult WriteSource(
	cli::array<ICarenWICBitmapSource^>^ Param_ArrayPlanes,
	UInt32 Param_QuantidadePlanes,
	CA_WICRect^ Param_RetanguloOrigem);
};