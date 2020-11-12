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
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos para gravar dados de digitalização JPEG compactados diretamente no fluxo de saída do codificador WIC.
/// Também fornece acesso as tabelas de Huffman e quantização.
/// </summary>
public ref class CarenWICJpegFrameEncode : public ICarenWICJpegFrameEncode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICJpegFrameEncode).
	IWICJpegFrameEncode* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICJpegFrameEncode();
	
	~CarenWICJpegFrameEncode();

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


	//Métodos da interface(ICarenWICJpegFrameEncode)
public:
	/// <summary>
	/// Recupera uma cópia da tabela AC Huffman para o scan e a tabela especificadas.
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar.</param>
	/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetAcHuffmanTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_AC_HUFFMAN_TABLE^% Param_Out_ACHuffmanTable);

	/// <summary>
	/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas.
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar.</param>
	/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetDcHuffmanTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_DC_HUFFMAN_TABLE^% Param_Out_DCHuffmanTable);

	/// <summary>
	/// Recupera uma cópia da tabela de quantização.
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar.</param>
	/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetQuantizationTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_QUANTIZATION_TABLE^% Param_Out_QuantizationTable);

	/// <summary>
	/// Grava dados de varredura em um frame JPEG. 
	/// WriteScan pode ser chamado várias vezes. Cada chamada anexa os dados de varredura especificados a quaisquer dados de varredura anteriores. Complete a varredura chamando 
	/// ICarenWICBitmapFrameEncode::Commit.
	/// </summary>
	/// <param name="Param_SizeBuffer">O tamanho do Buffer no parâmetro (Param_BufferScanData).</param>
	/// <param name="Param_BufferScanData">Os dados do scan para escrever.</param>
	virtual CarenResult WriteScan(
	UInt32 Param_SizeBuffer,
	ICarenBuffer^ Param_BufferScanData);
};