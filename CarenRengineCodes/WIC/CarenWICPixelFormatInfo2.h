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
#include "CarenWICColorContext.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por estender ICarenWICPixelFormatInfo, fornecendo informações adicionais sobre um formato de pixel. 
/// </summary>
public ref class CarenWICPixelFormatInfo2 : public ICarenWICPixelFormatInfo2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICPixelFormatInfo2).
	IWICPixelFormatInfo2* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICPixelFormatInfo2();
	
	~CarenWICPixelFormatInfo2();


	//Conversões implicitas
public:
	static operator CarenWICPixelFormatInfo2^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICPixelFormatInfo2^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICPixelFormatInfo2();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICPixelFormatInfo2*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenWICPixelFormatInfo2::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICPixelFormatInfo2)
public:
	/// <summary>
	/// Recupera o WICPixelFormatNumericRepresentation do formato de pixel.
	/// </summary>
	/// <param name="Param_Out_RepresentacaoNumerica">Retorna um valor da enumeração(CA_WICPixelFormatNumericRepresentation) que define a representação númerica do formato de pixel.</param>
	virtual CarenResult GetNumericRepresentation([Out] CA_WICPixelFormatNumericRepresentation% Param_Out_RepresentacaoNumerica);

	/// <summary>
	/// Retorna se o formato suporta pixels transparentes. 
	/// </summary>
	/// <param name="Param_Out_SuporteTransparencia">Retornos TRUE se o formato pixel suportar transparência; caso contrário, FALSE.</param>
	virtual CarenResult SupportsTransparency([Out] Boolean% Param_Out_SuporteTransparencia);


	//Métodos da interface(ICarenWICPixelFormatInfo)
public:
	/// <summary>
	/// Obtém os bits por pixel (BPP) do formato pixel. 
	/// </summary>
	/// <param name="Param_Out_BitsPerPixel">Retorna o o BPP do formato pixel.</param>
	virtual CarenResult GetBitsPerPixel([Out] UInt32% Param_Out_BitsPerPixel);

	/// <summary>
	/// Obtém o número de canais que o formato pixel contém. 
	/// </summary>
	/// <param name="Param_Out_ChannelCount">Retorna o número de canais.</param>
	virtual CarenResult GetChannelCount([Out] UInt32% Param_Out_ChannelCount);

	/// <summary>
	/// Recebe a máscara de canal do formato pixel. 
	/// Se 0 e NULO forem passados ​​para Param_SizeMaskBuffer e Param_Ref_MaskBuffer, respectivamente, o tamanho do buffer necessário será retornado por meio de (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_ChannelIndex">O índice da máscara do canal para recuperar.</param>
	/// <param name="Param_SizeMaskBuffer">O tamanho do buffer (Param_Ref_MaskBuffer).</param>
	/// <param name="Param_Ref_MaskBuffer">Uma interface(ICarenBuffer) que vai receber o Buffer da máscara do canal.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para obter a máscara de canal.</param>
	virtual CarenResult GetChannelMask(
		UInt32 Param_ChannelIndex,
		UInt32 Param_SizeMaskBuffer,
		ICarenBuffer^% Param_Ref_MaskBuffer,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Obtém o ICarenWICColorContext do formato pixel. 
	/// O contexto de cores retornado é o espaço de cor padrão para o formato pixel. No entanto, se um ICarenWICBitmapSource especificar seu próprio contexto de cores, o contexto da fonte 
	/// deve ser preferido em relação ao padrão do formato pixel.
	/// </summary>
	/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenWICColorContext) que contém um ponteiro para o contexto de cores do formato do pixel.</param>
	virtual CarenResult GetColorContext([Out] ICarenWICColorContext^% Param_Out_ColorContext);

	/// <summary>
	/// Obtém o GUID do formato de pixel. 
	/// </summary>
	/// <param name="Param_Out_Formato">Retorna o GUID para o formato do pixel.</param>
	virtual CarenResult GetFormatGUID([Out] String^% Param_Out_Formato);

	//Métodos da interface(ICarenWICComponentInfo)
public:
	/// <summary>
	/// Recupera o nome do autor do componente. Se (Param_SizeAutorString) for 0 e (Param_Ref_Autor) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeAutorString">O tamanho da String (Param_Ref_Autor).</param>
	/// <param name="Param_Ref_Autor">Recebe o nome do autor do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da instalação.
	///  Para componentes embutidos, essas Strings estão sempre em inglês.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome dos autores do componente. O nome do autor é opcional; se um nome autor não for especificado pelo componente,
	///  o comprimento devolvido será 0.</param>
	virtual CarenResult GetAuthor(
		UInt32 Param_SizeAutorString,
		String^% Param_Ref_Autor,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o identificador de classe do componente (CLSID) 
	/// </summary>
	/// <param name="Param_Out_CLSID">Recebe o CLSID do componente.</param>
	virtual CarenResult GetCLSID([Out] String^% Param_Out_CLSID);

	/// <summary>
	/// Recupera o CA_WICComponentType do componente. 
	/// </summary>
	/// <param name="Param_Out_Type">Recebe um enum CA_WICComponentType que define o tipo do componente.</param>
	virtual CarenResult GetComponentType([Out] CA_WICComponentType% Param_Out_Type);

	/// <summary>
	/// Recupera o nome amigável do componente, que é um nome de exibição legível por humanos para o componente.
	/// Se (Param_SizeNomeString) for 0 e (Param_Ref_NomeAmigavel) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeNomeString">O tamanho da String em (Param_Ref_NomeAmigavel).</param>
	/// <param name="Param_Ref_NomeAmigavel">Recebe o nome amigável do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da 
	/// instalação. Para componentes embutidos, essas cordas 
	/// estão sempre em inglês.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome amigável do componente.</param>
	virtual CarenResult GetFriendlyName(
		UInt32 Param_SizeNomeString,
		String^% Param_Ref_NomeAmigavel,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o status de assinatura do componente. A assinatura não é usada pelo WIC. Portanto, todos os componentes WICComponentSigned. Esta função pode ser usada para 
	/// determinar se um componente não possui nenhum componente 
	/// binário ou foi adicionado à lista de componentes desabilitados no registro.
	/// </summary>
	/// <param name="Param_Out_Status">Retorna um enum que recebe o status do componente.</param>
	virtual CarenResult GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status);

	/// <summary>
	/// Recupera a versão de especificação do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão spec.
	/// Se (Param_SizeSpecString) for 0 e (Param_Ref_SpecVersion) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeSpecString">O tamanho da String em (Param_Ref_SpecVersion).</param>
	/// <param name="Param_Ref_SpecVersion">Retorna uma string que contém uma sequência de cultura invariente da versão de especificação do componente. O formulário de versão 
	/// é NN.NN.NN.NN.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão de especificação do componente. A versão de especificação é opcional; se um valor não for especificado
	///  pelo componente, o comprimento devolvido será 0.</param>
	virtual CarenResult GetSpecVersion(
		UInt32 Param_SizeSpecString,
		String^% Param_Ref_SpecVersion,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o fornecedor GUID. 
	/// </summary>
	/// <param name="Param_Out_GuidVendor">Recebe o guid do fornecedor do componente.</param>
	virtual CarenResult GetVendorGUID([Out] String^% Param_Out_GuidVendor);

	/// <summary>
	/// Recupera a versão do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão.
	/// Se (Param_SizeVersionString) for 0 e (Param_Ref_Version) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeVersionString">O tamanho da String em (Param_Ref_Version).</param>
	/// <param name="Param_Ref_Version">Recebe uma sequência de cultura invariante da versão do componente.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão do componente. A versão é opcional; se um valor não for especificado pelo componente, o comprimento
	///  devolvido será 0.</param>
	virtual CarenResult GetVersion(
		UInt32 Param_SizeVersionString,
		String^% Param_Ref_Version,
		[Out] UInt32% Param_Out_SizeAtual);
};