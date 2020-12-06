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
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Em desenvolvimento) - 
/// </summary>
public ref class CarenMFCaptureRecordSink : public ICarenMFCaptureRecordSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFCaptureRecordSink).
	IMFCaptureRecordSink* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFCaptureRecordSink();
	
	~CarenMFCaptureRecordSink();

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
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenMFCaptureRecordSink)
public:
	/// <summary>
	/// Obtém a rotação que está sendo aplicada ao fluxo de vídeo gravado.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_Out_RotationValue">Recebe a rotação da imagem, em graus.</param>
ResultCode GetRotation(
	UInt32 Param_StreamIndex,
	[Out] UInt32% Param_Out_RotationValue);

	/// <summary>
	/// Define um sink de mídia personalizada para gravação.
	/// Este método substitui a seleção padrão do sink de mídia para gravação.
	/// </summary>
	/// <param name="Param_MediaSink">Uma interface ICarenMFMediaSink para o sink da mídia.</param>
ResultCode SetCustomSink(ICarenMFMediaSink^ Param_MediaSink);

	/// <summary>
	/// Especifica um fluxo de byte que receberá os dados para a gravação.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputFileName ou ICarenMFCaptureRecordSink::SetSampleCallback.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O fluxo de byte deve suportar escrita.</param>
	/// <param name="Param_GuidContainer">Um GUID que especifica o tipo de recipiente de arquivo. Os valores possíveis estão documentados no atributo MF_TRANSCODE_CONTAINERTYPE.</param>
ResultCode SetOutputByteStream(
	ICarenMFByteStream^ Param_ByteStream,
	String^ Param_GuidContainer);

	/// <summary>
	/// Especifica o nome do arquivo de saída para a gravação.
	/// O mecanismo de captura usa a extensão do nome do arquivo para selecionar o tipo de contêiner para o arquivo de saída. Por exemplo, se a extensão do nome do arquivo for ." mp4", o mecanismo de captura cria um arquivo MP4.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetSampleCallback.
	/// </summary>
	/// <param name="Param_Url">Uma String que contém a URL do arquivo de saída.</param>
ResultCode SetOutputFileName(String^ Param_Url);

	/// <summary>
	/// Rotaciona o fluxo de vídeo gravado.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo para girar. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_RotationValue">A quantidade para girar o vídeo, em graus. Os valores válidos são 0, 90, 180 e 270. O valor zero restaura o vídeo à sua orientação original.</param>
ResultCode SetRotation(
	UInt32 Param_StreamIndex,
	UInt32 Param_RotationValue);

	/// <summary>
	/// Define um Callback para receber os dados de gravação de um fluxo.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetOutputFileName.
	/// </summary>
	/// <param name="Param_StreamSinkIndex">O índice baseado em zero do fluxo. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
	/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnSampleCallback. O usuário deve implementar esta interface.</param>
ResultCode SetSampleCallback(
	UInt32 Param_StreamSinkIndex,
	ICarenMFCaptureEngineOnSampleCallback^ Param_Callback);
};