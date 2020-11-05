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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por expor métodos que produzem uma versão cortada do bitmap de entrada para uma região retangular especificada de interesse.
/// </summary>
public ref class CarenWICBitmapClipper : public ICarenWICBitmapClipper
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapClipper).
	IWICBitmapClipper* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapClipper();
	
	~CarenWICBitmapClipper();

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


	//Métodos da interface(ICarenWICBitmapClipper)
public:
	/// <summary>
	/// Inicializa o clipper de bitmap com os parâmetros fornecidos.
	/// </summary>
	/// <param name="Param_Source">A fonte de bitmap de entrada.</param>
	/// <param name="Param_RectClip">O retângulo da fonte bitmap para cortar.</param>
	virtual CarenResult Initialize(
	ICarenWICBitmapSource^ Param_Source,
	CA_WICRect^ Param_RectClip);

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