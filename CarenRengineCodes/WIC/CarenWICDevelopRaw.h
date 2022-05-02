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
#include "CarenWICBitmapSource.h"
#include "CarenWICMetadataQueryReader.h"
#include "../Windows/CarenPropertyBag2.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que fornecem acesso aos recursos de um formato de codec bruto.
/// </summary>
public ref class CarenWICDevelopRaw : public ICarenWICDevelopRaw
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICDevelopRaw).
	IWICDevelopRaw* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICDevelopRaw();
	
	~CarenWICDevelopRaw();


	//Conversões implicitas
public:
	static operator CarenWICDevelopRaw^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICDevelopRaw^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICDevelopRaw();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICDevelopRaw*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenWICDevelopRaw::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICDevelopRaw)
public:
	/// <summary>
	/// Obtém o valor de contraste da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Contraste">Retorna o valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. 
	/// O limite inferior de 0,0 não representa nenhum contraste aplicado à imagem, 
	/// enquanto o limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
	virtual CarenResult GetContrast([Out] double% Param_Out_Contraste);

	/// <summary>
	/// Obtém o conjunto atual de parâmetros.
	/// </summary>
	/// <param name="Param_Out_ParametrosAtuais">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a bag que contém o conjunto atual de parametros.</param>
	virtual CarenResult GetCurrentParameterSet([Out] ICarenPropertyBag2^% Param_Out_ParametrosAtuais);

	/// <summary>
	/// Obtém a compensação de exposição parar o valor da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_EV">Retorna o valor de parada de compensação de exposição. O padrão é a configuração "as-shot".</param>
	virtual CarenResult GetExposureCompensation([Out] double% Param_Out_EV);

	/// <summary>
	/// Obtém a configuração gama atual da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Gamma">Retorna o valor da configuração gama atual.</param>
	virtual CarenResult GetGamma([Out] double% Param_Out_Gamma);

	/// <summary>
	/// Obtém a informação sobre a atual gama Kelvin da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_MinKelvinTemp">Retorna a temperatura mínima de Kelvin.</param>
	/// <param name="Param_Out_MaxKelvinTemp">Retorna a temperatura máxima de Kelvin.</param>
	/// <param name="Param_Out_KelvinTempStepValue">Retorna a temperatura do Kelvin Step.</param>
	virtual CarenResult GetKelvinRangeInfo(
	[Out] UInt32% Param_Out_MinKelvinTemp,
	[Out] UInt32% Param_Out_MaxKelvinTemp,
	[Out] UInt32% Param_Out_KelvinTempStepValue);

	/// <summary>
	/// Obtém o ponto branco da imagem bruta. Se os pontos brancos nomeados não forem suportados pela imagem bruta ou o arquivo bruto contiver pontos brancos nomeados que não 
	/// são suportados por esta API, o implementador codec ainda deve marcar essa capacidade como suportada. Se os pontos brancos nomeados não forem suportados pela imagem bruta, 
	/// um esforço melhor deve ser feito para ajustar a imagem ao ponto branco nomeado, mesmo quando não é um ponto branco pré-definido do arquivo bruto.
	/// Se o arquivo bruto contiver pontos brancos nomeados não suportados por esta API, o implementador codec deverá suportar os pontos brancos nomeados no CA_WICNamedWhitePoint.
	/// </summary>
	/// <param name="Param_Out_WhitePoint">Retorna a combinação bitwise dos valores de enumeração.</param>
	virtual CarenResult GetNamedWhitePoint([Out] CA_WICNamedWhitePoint% Param_Out_WhitePoint);

	/// <summary>
	/// Obtém o valor de redução de ruído da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Noise">Retorna o valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para 
	/// redução de ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa 
	/// redução de ruído aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
	virtual CarenResult GetNoiseReduction([Out] double% Param_Out_Noise);

	/// <summary>
	/// Obtém o CA_WICRawRenderMode atual. 
	/// </summary>
	/// <param name="Param_Out_ModoRender">Recebe uma enumeração que define o modo de renderização atual.</param>
	virtual CarenResult GetRenderMode([Out] CA_WICRawRenderMode% Param_Out_ModoRender);

	/// <summary>
	/// Obtém o ângulo de rotação atual. 
	/// </summary>
	/// <param name="Param_Out_Rotacao">Retorna o ângulo de rotação atual.</param>
	virtual CarenResult GetRotation([Out] double% Param_Out_Rotacao);

	/// <summary>
	/// Obtém o valor de saturação da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Saturacao">Retorna o valor de saturação da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para saturação é de 0,0 a 1,0. 
	/// Um valor de 0.0 representa uma imagem com uma imagem totalmente desaturada, 
	/// enquanto um valor de 1.0 representa a maior quantidade de saturação que pode ser aplicada.</param>
	virtual CarenResult GetSaturation([Out] double% Param_Out_Saturacao);

	/// <summary>
	/// Obtém o valor de nitidez da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Shapness">Retorna o valor de nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0.
	///  O limite inferior de 0,0 não representa nenhum nitidez aplicado à imagem, enquanto 
	/// o limite superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
	virtual CarenResult GetSharpness([Out] double% Param_Out_Shapness);

	/// <summary>
	/// Obtém o valor da tonalidade da imagem bruta. 
	/// </summary>
	/// <param name="Param_Out_Tint">Retorna o valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez 
	/// é de -1,0 a +1,0. O limite inferior de -1,0 representa um viés verde completo 
	/// para a imagem, enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
	virtual CarenResult GetTint([Out] double% Param_Out_Tint);

	/// <summary>
	/// Obtém a curva de tom da imagem bruta. 
	/// </summary>
	/// <param name="Param_ToneCurveBufferSize">O tamanho da estrutura (Param_Ref_ToneCurve).</param>
	/// <param name="Param_Ref_ToneCurve">Retorna uma estrutura (CA_WICRawToneCurve) da imagem bruta. Define esse valor para NULO para obter o tamanho necessário para (Param_ToneCurveBufferSize).</param>
	/// <param name="Param_Out_ToneCurveBufferSizeAtual">Retorna o tamanho necessário para retornar a estrutura (Param_Ref_ToneCurve).</param>
	virtual CarenResult GetToneCurve(
	UInt32 Param_ToneCurveBufferSize,
	CA_WICRawToneCurve^% Param_Ref_ToneCurve,
	[Out] UInt32% Param_Out_ToneCurveBufferSizeAtual);

	/// <summary>
	/// Obtém a temperatura Kelvin do ponto branco da imagem bruta.
	/// </summary>
	/// <param name="Param_Out_WhitePointKelvin">Retorna o valor da temperatura Kelvin do ponto branco da imagem bruta. O padrão é o valor de configuração "as-shot".</param>
	virtual CarenResult GetWhitePointKelvin([Out] UInt32% Param_Out_WhitePointKelvin);

	/// <summary>
	/// Obtém os valores RGB do ponto branco. 
	/// </summary>
	/// <param name="Param_Out_Red">Retorna o valor do ponto branco vermelho.</param>
	/// <param name="Param_Out_Green">Retorna o valor do ponto branco verde.</param>
	/// <param name="Param_Out_Blue">Retorna o valor do ponto branco azul.</param>
	virtual CarenResult GetWhitePointRGB(
	[Out] UInt32% Param_Out_Red,
	[Out] UInt32% Param_Out_Green,
	[Out] UInt32% Param_Out_Blue);

	/// <summary>
	/// Define a opção CA_WICRawParameterSet desejada. 
	/// </summary>
	/// <param name="Param_Parametros">Uma valor da opção(CA_WICRawParameterSet) a ser definido.</param>
	virtual CarenResult LoadParameterSet(CA_WICRawParameterSet Param_Parametros);

	/// <summary>
	/// Recupera informações sobre quais recursos são suportados para uma imagem bruta. 
	/// Recomenda-se que um codec informe que uma capacidade é suportada mesmo que os resultados nos limites de alcance externo não sejam de perfeita qualidade.
	/// </summary>
	/// <param name="Param_Out_Info">Retorna uma estrutura (CA_WICRawCapabilitiesInfo) que fornece os recursos suportados pela imagem bruta.</param>
	virtual CarenResult QueryRawCapabilitiesInfo([Out] CA_WICRawCapabilitiesInfo^% Param_Out_Info);

	/// <summary>
	/// Define o valor de contraste da imagem bruta. O implementador codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
	/// rotinas de processamento de imagem.
	/// </summary>
	/// <param name="Param_Contraste">O valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. O limite 
	/// inferior de 0,0 não representa nenhum contraste aplicado à imagem, enquanto o 
	/// limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
	virtual CarenResult SetContrast(double Param_Contraste);

	/// <summary>
	/// Define o contexto de cores do destino. 
	/// </summary>
	/// <param name="Param_ColorContext">O contexto de cores do destino.</param>
	virtual CarenResult SetDestinationColorContext(ICarenWICColorContext^ Param_ColorContext);

	/// <summary>
	/// Define o valor de parada da compensação de exposição. Recomenda - se que um codec informe que esse método é compatível, mesmo se os resultados nos limites da faixa externa 
	/// não forem de qualidade perfeita.
	/// </summary>
	/// <param name="Param_EV">O valor de compensação da exposição.O intervalo de valores para compensação de exposição é de - 5, 0 a + 5, 0, o que equivale a 10 pontos finais.</param>
	virtual CarenResult SetExposureCompensation(double Param_EV);

	/// <summary>
	/// Define o valor gama desejado. 
	/// </summary>
	/// <param name="Param_Gamma">O valor gama desejado.</param>
	virtual CarenResult SetGamma(double Param_Gamma);

	/// <summary>
	/// Define o ponto branco nomeado do arquivo bruto. 
	/// </summary>
	/// <param name="Param_WhitePoint">Uma combinação bitwise dos valores de enumeração.</param>
	virtual CarenResult SetNamedWhitePoint(CA_WICNamedWhitePoint Param_WhitePoint);

	/// <summary>
	/// Define o valor de redução de ruído da imagem bruta. O implementador do codec deve determinar o que o valor do intervalo superior representa e deve determinar como mapear o 
	/// valor para suas rotinas de processamento de imagem.
	/// </summary>
	/// <param name="Param_Noise">O valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para redução de
	///  ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa redução de ruído 
	/// aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
	virtual CarenResult SetNoiseReduction(double Param_Noise);

	/// <summary>
	/// Define o método de retorno de chamada de notificação. 
	/// </summary>
	/// <param name="Param_NotificationCallback">Uma interface de callback que vai receber as notificações.</param>
	virtual CarenResult SetNotificationCallback(ICarenWICDevelopRawNotificationCallback^ Param_NotificationCallback);

	/// <summary>
	/// Define o WICRawRenderMode atual. 
	/// </summary>
	/// <param name="Param_ModoRender">O modo renderização a ser usado.</param>
	virtual CarenResult SetRenderMode(CA_WICRawRenderMode Param_ModoRender);

	/// <summary>
	/// Define o ângulo de rotação desejado. 
	/// </summary>
	/// <param name="Param_Rotacao">O ângulo de rotação desejado.</param>
	virtual CarenResult SetRotation(double Param_Rotacao);

	/// <summary>
	/// Define o valor de saturação da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor 
	/// para suas rotinas de processamento de imagem.
	/// </summary>
	/// <param name="Param_Saturacao">O valor de saturação da imagem bruta. A faixa de valor para saturação é de 0,0 a 1,0. Um valor de 0.0 representa uma imagem com uma imagem 
	/// totalmente desaturada, enquanto um valor de 1.0 representa a maior quantidade 
	/// de saturação que pode ser aplicada.</param>
	virtual CarenResult SetSaturation(double Param_Saturacao);

	/// <summary>
	/// Define o valor de nitidez da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
	/// rotinas de processamento de imagem.
	/// </summary>
	/// <param name="Param_Sharpness">O valor da nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0. O limite inferior de 
	/// 0,0 não representa nenhum nitidez aplicado à imagem, enquanto o limite 
	/// superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
	virtual CarenResult SetSharpness(double Param_Sharpness);

	/// <summary>
	/// Define o valor da tonalidade da imagem bruta. O implementador do codec deve determinar quais são os valores de alcance externo e deve determinar como mapear os valores para suas 
	/// rotinas de processamento de imagem.
	/// </summary>
	/// <param name="Param_Tint">O valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez é de -1,0 a +1,0. 
	/// O limite inferior de -1,0 representa um viés verde completo para a imagem, 
	/// enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
	virtual CarenResult SetTint(double Param_Tint);

	/// <summary>
	/// Define a curva de tom para a imagem bruta. 
	/// </summary>
	/// <param name="Param_ToneCurveSizeStruct">O tamanho da estrutura (Param_ToneCurve).</param>
	/// <param name="Param_ToneCurve">A curva de tom desejada.</param>
	virtual CarenResult SetToneCurve(
	UInt32 Param_ToneCurveSizeStruct,
	CA_WICRawToneCurve^ Param_ToneCurve);

	/// <summary>
	/// Define o valor do ponto branco kelvin. Os implementadores de codec devem ajustar fielmente a temperatura de cor dentro da faixa suportada nativamente pela imagem bruta. Para valores 
	/// fora da faixa de suporte nativa, o implementador codec deve fornecer uma representação de melhor esforço da imagem a essa temperatura de cor.
	/// Os implementadores de codec devem retornar WINCODEC_ERR_VALUEOUTOFRANGE se o valor estiver fora do intervalo aceitável definido.
	/// </summary>
	/// <param name="Param_WhitePointKelvin">O valor do ponto branco kelvin. Os valores aceitáveis de Kelvin são de 1.500 a 30.000.</param>
	virtual CarenResult SetWhitePointKelvin(UInt32 Param_WhitePointKelvin);

	/// <summary>
	/// Define os valores RGB de ponto branco. Devido a outros métodos de configuração de ponto branco(por exemplo, SetWhitePointKelvin), deve - se tomar cuidado pelos implementadores 
	/// de codec para garantir a interoperabilidade adequada.Por exemplo, se o chamador define por meio de um ponto branco nomeado, o implementador do codec pode desabilitar a leitura 
	/// da temperatura Kelvin correspondente.Em casos específicos em que o implementador do codec deseja negar uma determinada ação por causa de chamadas anteriores, 
	/// WINCODEC_ERR_WRONGSTATE deve ser retornado.
	/// </summary>
	/// <param name="Param_Red">O valor do ponto branco vermelho.</param>
	/// <param name="Param_Green">O valor verde do ponto branco.</param>
	/// <param name="Param_Blue">O valor do ponto branco azul.</param>
	virtual CarenResult SetWhitePointRGB(
	UInt32 Param_Red,
	UInt32 Param_Green,
	UInt32 Param_Blue);


	//Métodos da interface(ICarenWICBitmapFrameDecode)
public:
	/// <summary>
	/// Recupera o ICarenWICColorContext associado ao frame de imagem.
	/// Se NULO for definido para (Param_Ref_ColorContexts), e 0 for para (Param_Quantidade), este método retornará o número total de contextos de cores na imagem no (Param_Out_TamanhoArrayAtual).
	/// </summary>
	/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
	/// <param name="Param_Ref_ColorContexts">Uma matriz que recebe ponteiros para a interface(ICarenWICColorContext).</param>
	/// <param name="Param_Out_TamanhoArrayAtual">Recebe o número de contextos de cores retornados na matriz (Param_Ref_ColorContexts).</param>
	virtual CarenResult GetColorContexts(
		UInt32 Param_Quantidade,
		cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
		[Out] UInt32% Param_Out_TamanhoArrayAtual);

	/// <summary>
	/// Recupera um leitor de consulta de metadados para o frame.
	/// Para formatos de imagem com um frame (JPG, PNG, JPEG-XR), o leitor de consulta de nível de frame do primeiro frame é usado para acessar todos os metadados de imagem, 
	/// e o leitor de consulta de nível de decodificador não é usado. Para formatos com mais de um frames (GIF, TIFF), o leitor de consulta de nível de frame para um determinado 
	/// frame é usado para acessar metadados específicos desse frame, e no caso de GIF um leitor de metadados de nível de decodificador estará presente. Se o decodificador não suportar 
	/// metadados (BMP, ICO), isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
	/// </summary>
	/// <param name="Param_Out_MetadataReader">Retorna a interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o leitor de consulta de metadados do frame.</param>
	virtual CarenResult GetMetadataQueryReader(
		[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataReader);

	/// <summary>
	/// Recupera uma pequena visualização do frame, se suportado pelo codec.
	/// </summary>
	/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) que contém um ponteiro para o objeto miniatura.</param>
	virtual CarenResult GetThumbnail(
		[Out] ICarenWICBitmapSource^% Param_Out_Thumbnail);


	//Métodos da interface(ICarenWICBitmapSource)
public:
	/// <summary>
	/// Recupera a tabela de cores para formatos de pixel indexados. 
	/// </summary>
	/// <param name="Param_Palette">Uma ICarenWICPalette. Uma paleta pode ser criada usando o método ICarenWICImagingFactory::CreatePalette.</param>
	virtual CarenResult CopyPalette(ICaren^ Param_Palette);

	/// <summary>
	/// Instrui o objeto a produzir pixels. CopyPixels é uma das duas principais rotinas de processamento de imagens(a outra é Lock), acionando o processamento real.Ele instrui o 
	/// objeto a produzir pixels de acordo com seu algoritmo - isso pode envolver a decodificação de uma parte de um JPEG armazenado em disco, a cópia de um bloco de memória ou a 
	/// computação analítica de um gradiente complexo.O algoritmo é completamente dependente do objeto que implementa a interface.
	/// </summary>
	/// <param name="Param_RetanguloCopy">O retângulo para copiar. Um valor NULO especifica todo o bitmap.</param>
	/// <param name="Param_Stride">O Stride do bitmap</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer.</param>
	/// <param name="Param_Buffer">Um ponteiro para o buffer.</param>
	virtual CarenResult CopyPixels(
		CA_WICRect^ Param_RetanguloCopy,
		UInt32 Param_Stride,
		UInt32 Param_TamanhoBuffer,
		ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// Recupera o formato de pixel da fonte bitmap. O formato de pixel retornado por este método não é necessariamente o formato de pixel que a imagem é armazenada como. O codec pode 
	/// executar uma conversão de formato do formato pixel de armazenamento para um formato de pixel de saída.
	/// </summary>
	/// <param name="Param_Out_FormatoPixel">Recebe o GUID do formato de pixel em que o bitmap está armazenado.</param>
	virtual CarenResult GetPixelFormat([Out] String^% Param_Out_FormatoPixel);

	/// <summary>
	/// Recupera a taxa de amostragem entre pixels e medições do mundo físico. 
	/// Alguns formatos, como GIF e ICO, não possuem suporte completo ao DPI. Para GIF, este método calcula os valores de DPI a partir da proporção, utilizando um DPI base de (96,0, 96,0).
	///  O formato ICO não suporta DPI em tudo, e o método sempre retorna (96.0.96.0) para imagens de ICO. Além disso, o próprio WIC não transforma imagens com base nos valores de DPI em uma 
	/// imagem. Cabe ao interlocutor transformar uma imagem baseada na resolução devolvida.
	/// </summary>
	/// <param name="Param_Out_DpiX">Recebe a resolução dpi do eixo X.</param>
	/// <param name="Param_Out_DpiY">Recebe a resolução dpi do eixo Y.</param>
	virtual CarenResult GetResolution(
		[Out] double% Param_Out_DpiX,
		[Out] double% Param_Out_DpiY);

	/// <summary>
	/// Recupera a largura e a altura do bitmap. 
	/// </summary>
	/// <param name="Param_Out_PixelWidthBitmap">Recebe a Largura do pixel do bitmap.</param>
	/// <param name="Param_Out_PixelHeightBitmap">Recebe a Altura do pixel do bitmap.</param>
	virtual CarenResult GetSize(
		[Out] UInt32% Param_Out_PixelWidthBitmap,
		[Out] UInt32% Param_Out_PixelHeightBitmap);
};