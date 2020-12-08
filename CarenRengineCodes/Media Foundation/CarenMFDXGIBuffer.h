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
#include "../Caren/Caren.h"
#include "CarenMFMediaBuffer.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por conter um buffer de mídia para gerenciar uma superfície de infraestrutura gráfica DirectX(DXGI) da Microsoft.
/// </summary>
public ref class CarenMFDXGIBuffer :public ICarenMFDXGIBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFDXGIBuffer).
	IMFDXGIBuffer* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFDXGIBuffer();


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


	//Cria uma instância da classe
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenMFDXGIBuffer">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMFDXGIBuffer^% Param_Out_CarenMFDXGIBuffer)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenMFDXGIBuffer = gcnew CarenMFDXGIBuffer();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar um buffer de mídia para gerenciar uma superfície de infraestrutura gráfica DirectX(DXGI).
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície DXGI. Este valor deve ser IID_ID3D11Texture2D.</param>
	/// <param name="Param_SuperficeDXGI">Um ponteiro para a interface IUnknown da superfície DXGI.</param>
	/// <param name="Param_IndexSubrecurso">Um índice baseado em Zero do subrecurso da superfície. O objeto de Buffer de mídia está associado a esse subrecurso.</param>
	/// <param name="Param_BottomUpQuandoLinear">Se TRUE, ICarenMF2DBuffer:ContiguousCopyTo copia o buffer em um formato bottom-up(De baixo para cima). O formato de baixo para cima é compatível com GDI para imagens RGB não compactas. 
	/// Se este parâmetro for FALSE,o método ContiguousCopyTo copia o buffer em um formato Top-Down(de cima para baixo), que é compatível com o Direct3D.</param>
	/// <param name="Param_Out_CarenMFDXGIBuffer">Retorna a interface do Buffer DXGI. O chamado é responsável por liberar a interface.</param>
	static CarenResult CriarInstancia(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_IndexSubrecurso, Boolean Param_BottomUpQuandoLinear, [Out] ICarenMFDXGIBuffer^% Param_Out_CarenMFDXGIBuffer)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Resultado COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis
		Utilidades Util;
		IMFMediaBuffer* pGlobalMFMediaBuffer = NULL;
		IMFDXGIBuffer* pDxgiBuffer = NULL;
		GUID RiidInterface = GUID_NULL;
		IUnknown* pSuperficeDXGI = NULL;

		//Cria o Guid.
		RiidInterface = Util.CreateGuidFromString(Param_RIID);

		//Obtém o ponteiro para a superfice do DXGI
		Resultado = Param_SuperficeDXGI->RecuperarPonteiro((LPVOID*)&pSuperficeDXGI);

		//Verifica o resultado
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//A operção falhou.
			
			//Sai do método
			goto Done;
		}

		//Chama o método que vai criar o Buffer DXGI.
		Hr = MFCreateDXGISurfaceBuffer(RiidInterface, pSuperficeDXGI, Param_IndexSubrecurso, Param_BottomUpQuandoLinear? TRUE: FALSE, &pGlobalMFMediaBuffer);

		//Verifica se obteve sucesso
		if(Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Falhou ao Criar a superfice do buffer.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Obtém o DXGI buffer a parti do Media buffer.
		Hr = pGlobalMFMediaBuffer->QueryInterface(IID_IMFDXGIBuffer, (void**)&pDxgiBuffer);

		//Verifica se obteve com sucesso
		if(Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//A operação falhou.
			Resultado.AdicionarCodigo(ResultCode::ER_E_NOINTERFACE, false);

			//Libera a interface do buffer criada.
			pGlobalMFMediaBuffer->Release();
			pGlobalMFMediaBuffer = NULL;

			//Sai do método
			goto Done;
		}

		//Libera o ponteiro do buffer global.
		pGlobalMFMediaBuffer->Release();
		pGlobalMFMediaBuffer = NULL;

		//Cria a interface que será retornado no parametro.
		Param_Out_CarenMFDXGIBuffer = gcnew CarenMFDXGIBuffer();

		//Define o ponteiro de trabalho
		Param_Out_CarenMFDXGIBuffer->AdicionarPonteiro(pDxgiBuffer);

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	///  Método responsável por criar um buffer de mídia para gerenciar uma superfície de infraestrutura gráfica DirectX(DXGI).
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície DXGI. Este valor deve ser IID_ID3D11Texture2D.</param>
	/// <param name="Param_SuperficeDXGI">Um ponteiro para a interface IUnknown da superfície DXGI.</param>
	/// <param name="Param_IndexSubrecurso">Um índice baseado em Zero do subrecurso da superfície. O objeto de Buffer de mídia está associado a esse subrecurso.</param>
	/// <param name="Param_BottomUpQuandoLinear">Se TRUE, ICarenMF2DBuffer:ContiguousCopyTo copia o buffer em um formato bottom-up(De baixo para cima). O formato de baixo para cima é compatível com GDI para imagens RGB não compactas. 
	/// Se este parâmetro for FALSE,o método ContiguousCopyTo copia o buffer em um formato Top-Down(de cima para baixo), que é compatível com o Direct3D.</param>
	/// <param name="Param_Out_CarenMidiaBuffer">Retorna a interface de buffer. A interface retornada suporta as seguintes interfaces: ICarenMFMedia2DBuffer, ICarenMFMedia2DBuffer2 e ICarenMFDXGIBuffer. 
	/// O chamador é responsável por liberar a interface.</param>
	static CarenResult CriarInstancia(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_IndexSubrecurso, Boolean Param_BottomUpQuandoLinear, [Out] ICarenMFMediaBuffer^% Param_Out_CarenMidiaBuffer)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Resultado COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis
		Utilidades Util;
		IMFMediaBuffer* pGlobalMFMediaBuffer = NULL;
		GUID RiidInterface = GUID_NULL;
		IUnknown* pSuperficeDXGI = NULL;

		//Cria o Guid.
		RiidInterface = Util.CreateGuidFromString(Param_RIID);

		//Obtém o ponteiro para a superfice do DXGI
		Resultado = Param_SuperficeDXGI->RecuperarPonteiro((LPVOID*)&pSuperficeDXGI);

		//Verifica o resultado
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//A operção falhou.

			//Sai do método
			goto Done;
		}

		//Chama o método que vai criar o Buffer DXGI.
		Hr = MFCreateDXGISurfaceBuffer(RiidInterface, pSuperficeDXGI, Param_IndexSubrecurso, Param_BottomUpQuandoLinear ? TRUE : FALSE, &pGlobalMFMediaBuffer);

		//Verifica se obteve sucesso
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Falhou ao Criar a superfice do buffer.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que será retornado no parametro.
		Param_Out_CarenMidiaBuffer = gcnew CarenMFMediaBuffer();

		//Define o ponteiro de trabalho
		Param_Out_CarenMidiaBuffer->AdicionarPonteiro(pGlobalMFMediaBuffer);

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
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


	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// Consulta a superfície do Microsoft DirectX Graphics infra-estrutura (DXGI) para uma interface.
	/// Você pode usar esse método para obter um ponteiro para a interface de ID3D11Texture2D da superfície. Se o buffer estiver bloqueado, o método retorna ER_MF_REQUISICAO_INVALIDA.
	/// </summary>
	/// <param name="Param_Guid">O identificador de interface (IID) da interface requisitada.</param>
	/// <param name="Param_Out_InterfaceRecurso">Recebe um ponteiro para a interface. O chamador deve liberar a interface. O Usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetResource(String^ Param_Guid, ICaren^ Param_Out_InterfaceRecurso);

	/// <summary>
	/// Obtém o índice do sub-recurso que está associado com esse buffer de mídia.
	/// </summary>
	/// <param name="Param_Out_SubResourceId">Recebe o índice baseado em zero do sub-recurso.</param>
	virtual CarenResult GetSubresourceIndex([Out] UInt32% Param_Out_SubResourceId);

	/// <summary>
	/// Obtém um ponteiro IUnknown que anteriormente foi armazenado no objeto de reserva de meios de comunicação.
	/// </summary>
	/// <param name="Param_GuidInterface">O identificador do ponteiro IUnknown.</param>
	/// <param name="Param_IID">O identificador de interface (IID) da interface requisitada.</param>
	/// <param name="Param_Ref_InterfaceRequisitada">Recebe um ponteiro para o objeto anteriormente definido. O chamador é responsável por criar e liberar a interface.param>
	virtual CarenResult GetUnknown(String^ Param_GuidInterface, String^ Param_IID, ICaren^ Param_Ref_InterfaceRequisitada);

	/// <summary>
	/// Armazena um ponteiro IUnknown arbitrário em objeto de reserva de meios de comunicação.  
	/// </summary>
	/// <param name="Param_GuidInterface">O identificador para o ponteiro IUnknown. Esse identificador é usado como uma chave para recuperar o valor. Pode ser qualquer valor GUID.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface IUnknown. Defina este parâmetro como NULL para limpar um ponteiro que foi previamente definido.</param>
	virtual CarenResult SetUnknown(String^ Param_GuidInterface, ICaren^ Param_Interface);
};

