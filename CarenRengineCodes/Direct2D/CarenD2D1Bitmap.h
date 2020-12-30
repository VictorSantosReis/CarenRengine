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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por representar um bitmap que foi vinculado a um ICarenD2D1RenderTarget. 
/// </summary>
public ref class CarenD2D1Bitmap : public ICarenD2D1Bitmap
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Bitmap).
	ID2D1Bitmap* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.	/// </summary>
	CarenD2D1Bitmap();

	~CarenD2D1Bitmap();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenD2D1Bitmap">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1Bitmap^% Param_Out_CarenD2D1Bitmap)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1Bitmap = gcnew CarenD2D1Bitmap();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
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


	//Métodos da interface(ICarenD2D1Bitmap)
public:
	/// <summary>
	/// Copia a região especificada do bitmap especificado no bitmap atual.
	/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, observe que este método não executa a conversão de formato, 
	/// e falhará se os formatos bitmap não coincidirem.
	/// </summary>
	/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
	/// <param name="Param_Bitmap">O bitmap para copiar.</param>
	/// <param name="Param_SourceRect">A área de bitmap para copiar.</param>
	virtual CarenResult CopyFromBitmap(
	CA_D2D1_POINT_2U^ Param_PointDestino,
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_RECT_U^ Param_SourceRect);

	/// <summary>
	/// Copie a região especificada da memória para o bitmap atual.
	/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, note que este método não realiza conversão de formato; os dois 
	/// formatos bitmap devem coincidir.
	/// </summary>
	/// <param name="Param_DestinoRect">No bitmap atual, o retângulo para o qual a região especificada pelo (Param_SourceData) é copiada.</param>
	/// <param name="Param_SourceData">Os dados para copiar.</param>
	/// <param name="Param_Pitch">O passo, ou arremesso, do bitmap de origem armazenado em srcData. O passo é a contagem de byte de uma linha de varredura (uma linha de pixels na memória). O passo pode ser computado a partir 
	/// da seguinte fórmula: largura de pixel * bytes por pixel + preenchimento de memória.</param>
	virtual CarenResult CopyFromMemory(
	CA_D2D1_RECT_U^ Param_DestinoRect,
	ICarenBuffer^ Param_SourceData,
	UInt32 Param_Pitch);

	/// <summary>
	/// Copia a região especificada do alvo de renderização especificado no bitmap atual.
	/// </summary>
	/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
	/// <param name="Param_D2D1RenderTarget">O alvo de renderização que contém a região para copiar.</param>
	/// <param name="Param_SourceRect">A área do (Param_D2D1RenderTarget) para copiar.</param>
	virtual CarenResult CopyFromRenderTarget(
	CA_D2D1_POINT_2U^ Param_PointDestino,
	ICaren^ Param_D2D1RenderTarget,
	CA_D2D1_RECT_U^ Param_SourceRect);

	/// <summary>
	/// Retorne os pontos por polegada (DPI) do bitmap.
	/// </summary>
	/// <param name="Param_Out_DpiX">Retorna o DPI horizontal da imagem.</param>
	/// <param name="Param_Out_DpiY">Retorna o DPI vertical da imagem.</param>
	virtual void GetDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY);

	/// <summary>
	/// Recupera o formato de pixel e o modo alfa do bitmap.
	/// </summary>
	/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do bitmap.</param>
	virtual void GetPixelFormat(
	[Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat);

	/// <summary>
	/// Retorna o tamanho, em unidades dependentes de dispositivos (pixels), do bitmap.
	/// </summary>
	/// <param name="Param_Out_PixelSize">Retorna o tamanho, em pixels, do bitmap.</param>
	virtual void GetPixelSize(
	[Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize);

	/// <summary>
	/// Retorna o tamanho, em pixels independentes do dispositivo (DIPs), do bitmap.
	/// Um DIP é de 1/96 de polegada. Para recuperar o tamanho dos pixels do dispositivo, use o método ICarenD2D1Bitmap::GetPixelSize.
	/// </summary>
	/// <param name="Param_Out_Size">Retorna o tamanho, em DIPs, do bitmap.</param>
	virtual void GetSize(
	[Out] CA_D2D1_SIZE_F^% Param_Out_Size);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};