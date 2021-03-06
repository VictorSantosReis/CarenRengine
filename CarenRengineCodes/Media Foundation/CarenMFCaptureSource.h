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
#include "../SDK_MediaFoundation.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenMFMediaType.h"
#include "CarenMFMediaSource.h"
#include "CarenMFActivate.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por controlar o objeto de origem de captura. A fonte de captura gerencia os dispositivos de captura de áudio e vídeo.
/// </summary>
public ref class CarenMFCaptureSource : public ICarenMFCaptureSource
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFCaptureSource).
	IMFCaptureSource* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFCaptureSource();
	
	~CarenMFCaptureSource();


	//Conversões implicitas
public:
	static operator CarenMFCaptureSource^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFCaptureSource^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFCaptureSource();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFCaptureSource*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFCaptureSource::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFCaptureSource)
public:
	/// <summary>
	/// Adiciona um efeito a um fluxo de captura.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_Efeito">Uma interface que contém o ponteiro para o efeito. Essa interface pode ser uma ICarenMFTransform ou ICarenActivate.</param>
	virtual CarenResult AddEffect(
	UInt32 Param_SourceStreamIndex,
	ICaren^ Param_Efeito);

	/// <summary>
	/// Obtém um formato que é suportado por um dos fluxos de captura.
	/// Para enumerar todos os formatos disponíveis em um fluxo, chame este método em um loop enquanto incrementa o (Param_MediaTypeIndex), até que o método retorne ER_MF_E_NO_MORE_TYPES.
	/// Algumas câmeras podem suportar uma série de taxas de quadros. As taxas mínimas e máximas de quadros são armazenadas nos atributos MF_MT_FRAME_RATE_RANGE_MIN e MF_MT_FRAME_RATE_RANGE_MAX no tipo de mídia.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_MediaTypeIndex">O índice baseado em zero do tipo de mídia para recuperar.</param>
	/// <param name="Param_Out_MediaType">Recebe um ponteiro para a interface IMFMediaType. O chamador deve liberar a interface.</param>
	virtual CarenResult GetAvailableDeviceMediaType(
	UInt32 Param_SourceStreamIndex,
	UInt32 Param_MediaTypeIndex,
	[Out] ICarenMFMediaType^% Param_Out_MediaType);

	/// <summary>
	/// Obtém o ponteiro para a interface ICarenMFActivate do dispositivo de captura atual.
	/// </summary>
	/// <param name="Param_CaptureDeviceType">O tipo de dispositivo do motor de captura.</param>
	/// <param name="Param_Out_Activate">Recebe a interface ICarenMFActivate que representa o dispositivo.</param>
	virtual CarenResult GetCaptureDeviceActivate(
	CA_MF_CAPTURE_ENGINE_DEVICE_TYPE Param_CaptureDeviceType,
	[Out] ICarenMFActivate^% Param_Out_Activate);

	/// <summary>
	/// Obtém o ponteiro para a interface ICarenMFMediaSource do dispositivo de captura atual
	/// </summary>
	/// <param name="Param_CaptureDeviceType">O tipo de dispositivo do motor de captura.</param>
	/// <param name="Param_Out_MediaSource">Recebe a interface ICarenMFMediaSource que representa o dispositivo.</param>
	virtual CarenResult GetCaptureDeviceSource(
	CA_MF_CAPTURE_ENGINE_DEVICE_TYPE Param_CaptureDeviceType,
	[Out] ICarenMFMediaSource^% Param_Out_MediaSource);

	/// <summary>
	/// Obtém o tipo de mídia atual para um fluxo de captura. 
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_Out_MediaType">Recebe a interface ICarenMFMediaType. O chamador deve liberar a interface.</param>
	virtual CarenResult GetCurrentDeviceMediaType(
	UInt32 Param_SourceStreamIndex,
	[Out] ICarenMFMediaType^% Param_Out_MediaType);

	/// <summary>
	/// Obtém a categoria de fluxo para o índice de fluxo de origem especificado. 
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_Out_StreamCategory">Recebe um valor da enumeração (CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY) do fluxo de origem especificado.</param>
	virtual CarenResult GetDeviceStreamCategory(
	UInt32 Param_SourceStreamIndex,
	[Out] CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY% Param_Out_StreamCategory);

	/// <summary>
	/// Obtém o número de fluxos de dispositivos. 
	/// </summary>
	/// <param name="Param_Out_StreamCount">Recebe o número de fluxos de dispositivos.</param>
	virtual CarenResult GetDeviceStreamCount([Out] UInt32% Param_Out_StreamCount);

	/// <summary>
	/// Obtém o estado de espelhamento atual da transmissão de visualização de vídeo. 
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo.</param>
	/// <param name="Param_Out_MirrorState">Recebe o valor TRUE se o espelhamento estiver ativado ou FALSE se o espelhamento for desativado.</param>
	virtual CarenResult GetMirrorState(
	UInt32 Param_StreamIndex,
	[Out] Boolean% Param_Out_MirrorState);

	/// <summary>
	/// Obtém um ponteiro para o objeto Source Reader(ICarenMFSourceReader) subjacente. 
	/// </summary>
	/// <param name="Param_GuidServico">Um identificador de serviço GUID. Atualmente, o valor deve ser IID_IMFSourceReader ou Nulo.</param>
	/// <param name="Param_RIIDInterface">O identificador de interface (IID) da interface que está sendo solicitada. O valor deve ser IID_IMFSourceReader. Se o valor não estiver definido para IID_IMFSourceReader,a chamada falhará e retornará ER_E_INVALIDARG.</param>
	/// <param name="Param_Ref_Interface">Recebe um ponteiro para a interface solicitada. O usuário é responsável por inicializar a interface.</param>
	virtual CarenResult GetService(
	String^ Param_GuidServico,
	String^ Param_RIID,
	ICaren^% Param_Ref_Interface);

	/// <summary>
	/// Obtém o índice de fluxo real do dispositivo traduzido de um nome de fluxo amigável. 
	/// </summary>
	/// <param name="Param_NomeAmigavel">O nome amigável. Esse valor pode ser os valores da enumeração (CA_MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou outros valores. Veja na documentação do método.</param>
	/// <param name="Param_Out_StreamIndexAtual">Recebe o valor do índice de fluxo que corresponde ao nome amigável.</param>
	virtual CarenResult GetStreamIndexFromFriendlyName(
	UInt32 Param_NomeAmigavel,
	[Out] UInt32% Param_Out_StreamIndexAtual);

	/// <summary>
	/// Remove todos os efeitos de um fluxo de captura.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	virtual CarenResult RemoveAllEffects(UInt32 Param_SourceStreamIndex);

	/// <summary>
	/// Remove um efeito de um fluxo de captura.
	/// Este método remove um efeito que foi adicionado anteriormente usando o método ICarenMFCaptureSource::AddEffect.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_Efeito">O ponteiro para a interface que contém o efeito a ser removido.</param>
	virtual CarenResult RemoveEffect(
	UInt32 Param_SourceStreamIndex,
	ICaren^ Param_Efeito);

	/// <summary>
	/// Define o formato de saída para um fluxo de captura.
	/// Este método define o tipo de saída nativa no dispositivo de captura. O dispositivo deve suportar o formato especificado. Para obter a lista de formatos disponíveis, ligue para o ICarenMFCaptureSource::GetAvailableDeviceMediaType.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType para o formato de saída para o fluxo de captura.</param>
	virtual CarenResult SetCurrentDeviceMediaType(
	UInt32 Param_SourceStreamIndex,
	ICarenMFMediaType^ Param_MediaType);

	/// <summary>
	/// Habilita ou desativa o espelhamento da transmissão de visualização de vídeo. 
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo.</param>
	/// <param name="Param_MirrorState">Se TRUE, o espelhamento estiver ativado; se FALSO, o espelhamento é desativado.</param>
	virtual CarenResult SetMirrorState(
	UInt32 Param_StreamIndex,
	Boolean Param_MirrorState);
};