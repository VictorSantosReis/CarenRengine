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
/// (Concluido - Fase de Testes) - Classe responsável por fornecer acesso a um único quadro de dados de imagem DDS no formato DXGI_FORMAT nativo, além de informações sobre os 
/// dados da imagem.
/// </summary>
public ref class CarenWICDdsFrameDecode : public ICarenWICDdsFrameDecode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICDdsFrameDecode).
	IWICDdsFrameDecode* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICDdsFrameDecode();
	
	~CarenWICDdsFrameDecode();

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


	//Métodos da interface(ICarenWICDdsFrameDecode)
public:
	/// <summary>
	/// Solicita dados de pixel, pois são armazenados nativamente no arquivo DDS. Se a textura não usar um DXGI_FORMAT compactado por bloco, este método se comporta de forma semelhante 
	/// ao IWICBitmapFonte::CopyPixels. No entanto, ele não executa qualquer conversão de formato de pixel e, em vez disso, produz os dados brutos do arquivo DDS.
	/// </summary>
	/// <param name="Param_RetanguloCopy">O retângulo para copiar da fonte. Um valor NULO especifica toda a textura. Se a textura usar um DXGI_FORMAT comprimido de bloco, todos os valores 
	/// do retângulo são expressos em número de blocos, não pixels.</param>
	/// <param name="Param_Stride">O Stride, em bytes, do Buffer de destino. Isso representa o número de bytes do Buffer para a próxima linha de dados. Se a textura usar uma DXGI_FORMAT
	///  compactada por bloco, uma "linha de dados" será definida como uma linha de blocos que contém várias linhas de varredura de pixels.</param>
	/// <param name="Param_BufferSize">O tamanho, em bytes, do buffer de destino.</param>
	/// <param name="Param_BufferDestino">Uma interface (ICarenBuffer) para o buffer de destino.</param>
	virtual CarenResult CopyBlocks(
	CA_WICRect^ Param_RetanguloCopy,
	UInt32 Param_Stride,
	UInt32 Param_BufferSize,
	ICarenBuffer^ Param_BufferDestino);

	/// <summary>
	/// Obtém informações sobre o formato em que a imagem DDS é armazenada.
	/// Essas informações podem ser usadas para alocar memória ou construir recursos Direct3D ou Direct2D, por exemplo, usando ICarenD3D11Device::CreateTexture2D ou ICarenD2D1DeviceContext::CreateBitmap.
	/// </summary>
	/// <param name="Param_Out_FormatInfo">Retorna uma estrutura que contém as informações sobre o formato DDS.</param>
	virtual CarenResult GetFormatInfo([Out] CA_WICDdsFormatInfo^% Param_Out_FormatInfo);

	/// <summary>
	/// Obtém a largura e a altura, em blocos, da imagem DDS.
	/// Para texturas compactadas de bloco, os valores de largura e altura retornados não definem completamente o tamanho da textura porque a imagem é acolchoada para se adequar 
	/// ao tamanho de bloco inteiro mais próximo.
	/// Se a textura não usar um DXGI_FORMAT comprimido de bloco, este método retorna o tamanho da textura em pixels; para esses formatos o tamanho do bloco devolvido pelo 
	/// ICarenWICDdsFrameDecoder::GetFormatInfo é 1x1.
	/// </summary>
	/// <param name="Param_Out_WidthInBlocks">Retorna a largura da imagem DDS em blocos.</param>
	/// <param name="Param_Out_HeightInBlocks">Retorna a altura da imagem DDS em blocos.</param>
	virtual CarenResult GetSizeInBlocks(
	[Out] UInt32% Param_Out_WidthInBlocks,
	[Out] UInt32% Param_Out_HeightInBlocks);
};