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
public ref class CarenMFCapturePreviewSink : public ICarenMFCapturePreviewSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFCapturePreviewSink).
	IMFCapturePreviewSink* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFCapturePreviewSink();
	
	~CarenMFCapturePreviewSink();

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


	//Métodos da interface(ICarenMFCapturePreviewSink)
public:
	/// <summary>
	/// Obtém o estado de espelhamento atual da transmissão de visualização de vídeo.
	/// </summary>
	/// <param name="Param_Out_MirrorState">Recebe o valor TRUE se o espelhamento estiver ativado ou FALSE se o espelhamento for desativado.</param>
	/// <returns></returns>
	virtual CarenResult GetMirrorState(OutParam Boolean% Param_Out_MirrorState);

	/// <summary>
	/// Obtém a rotação do fluxo de visualização de vídeo.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_Out_RotacaoValue">Recebe a rotação da imagem, em graus.</param>
	/// <returns></returns>
	virtual CarenResult GetRotation(
	UInt32 Param_StreamIndex,
	OutParam UInt32% Param_Out_RotacaoValue);

	/// <summary>
	/// Define um sink de mídia personalizada para visualização.
	/// </summary>
	/// <param name="Param_MediaSink">Uma interface ICarenMFMediaSink com o ponteiro para o sink de mídia</param>
	/// <returns></returns>
	virtual CarenResult SetCustomSink(ICarenMFMediaSink^ Param_MediaSink);

	/// <summary>
	/// Habilita ou desativa o espelhamento da transmissão de visualização de vídeo.
	/// </summary>
	/// <param name="Param_MirrorState">Se TRUE, o espelhamento está ativado. Se FALSE, o espelho está desativado.</param>
	/// <returns></returns>
	virtual CarenResult SetMirrorState(Boolean Param_MirrorState);

	/// <summary>
	/// Especifica uma Window(Handle) para visualização.
	/// </summar
	/// <param name="Param_HandleWindow">Uma Handle para a janela. O Sink de visualização desenha os quadros de vídeo dy>entro desta janela.</param>
	/// <returns></returns>
	virtual CarenResult SetRenderHandle(IntPtr Param_HandleWindow);

	/// <summary>
	/// Especifica um visual Microsoft DirectComposition para visualização.
	/// </summary>
	/// <param name="Param_Surface">Uma interface ICaren que contém um ponteiro para um Visual DirectComposition que implementa a interface (IDCompositionVisual).</param>
	/// <returns></returns>
	virtual CarenResult SetRenderSurface(ICaren^ Param_Surface);

	/// <summary>
	/// Rotaciona o fluxo de visualização de vídeo.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo para girar. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_RotacaoValue">O valor para girar o vídeo, em graus. Os valores válidos são 0, 90, 180 e 270. O valor zero restaura o vídeo à sua orientação original.</param>
	/// <returns></returns>
	virtual CarenResult SetRotation(
	UInt32 Param_StreamIndex,
	UInt32 Param_RotacaoValue);

	/// <summary>
	/// Define um retorno de chamada para receber os dados de visualização de um fluxo.
	/// Chamar este método substitui qualquer chamada anterior ao ICarenMFCapturePreviewSink::SetRenderHandle.
	/// </summary>
	/// <param name="Param_StreamSinkIndex">O índice baseado em zero do fluxo. O índice é devolvido no parâmetro (Param_Out_StreamSinkIndex) do método ICarenMFCaptureSink::AddStream.</param>
	/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnSampleCallback que contém o ponteiro para o callback. O usuário deve implementar esta interface.</param>
	/// <returns></returns>
	virtual CarenResult SetSampleCallback(
	UInt32 Param_StreamSinkIndex,
	ICarenMFCaptureEngineOnSampleCallback^ Param_Callback);

	/// <summary>
	/// Atualiza o quadro de vídeo. Ligue para este método quando a janela de visualização receber uma mensagem WM_PAINT ou WM_SIZE.
	/// </summary>
	/// <param name="Param_RectOrigem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem. O retângulo de origem define a área do quadro de vídeo que é exibido. Se este parâmetro for Nulo, todo o quadro de vídeo será exibido.</param>
	/// <param name="Param_RectDestino">Uma estrutura CA_RECT que especifica o retângulo de destino. O retângulo de destino define a área da janela ou visual directcomposition onde o vídeo é desenhado.</param>
	/// <param name="Param_CorBorda">A cor da borda a ser definida. </param>
	/// <returns></returns>
	virtual CarenResult UpdateVideo(
CA_MFVideoNormalizedRect^ Param_RectOrigem,
	CA_RECT^ Param_RectDestino,
	CA_MFARGB^ Param_CorBorda);
};