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
#include "CarenMFSample.h"
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
/// Classe responsável pelo alocamentos de amostras de vídeo utilizadas pelo EVR para o processamento.
/// </summary>
public ref class CarenMFVideoSampleAllocator : public ICarenMFVideoSampleAllocator
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFVideoSampleAllocator).
	IMFVideoSampleAllocatorEx* PonteiroTrabalho = NULL;

	//Construtor e Destruidor.
public:
	~CarenMFVideoSampleAllocator();

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


public:
	/// <summary>
	/// Método responsável por criar uma instância do alocador de amostras de vídeo compativeis do D3D9.
	/// </summary>
	/// <param name="Param_Out_Alocador">Recebe o ponteiro da instância do alocador de amostras de video.</param>
	static CarenResult CriarInstanciaAlocadorD3D9([Out] ICarenMFVideoSampleAllocator^% Param_Out_Alocador)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;
	
		//Variaveis Utilizadas
		LPVOID pInterface = NULL;
		ICarenMFVideoSampleAllocator^ InterfaceSolictada = nullptr;

		//Chama o método que vai criar o alocador.
		Hr = MFCreateVideoSampleAllocator(IID_IMFVideoSampleAllocator, &pInterface);
	
		//Verifica o resultado da operação
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define falha na operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método.
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro
		InterfaceSolictada = gcnew CarenMFVideoSampleAllocator();

		//Chama o método para definir o ponteiro
		InterfaceSolictada->AdicionarPonteiro(pInterface);

		//Define a interface criada no parametro de saida.
		Param_Out_Alocador = InterfaceSolictada;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar uma instância do alocador de amostras de vídeo compativeis do D3D11.
	/// </summary>
	/// <param name="Param_Out_Alocador">Recebe o ponteiro da instância do alocador de amostras de video.</param>
	static CarenResult CriarInstanciaAlocadorD3D11([Out] ICarenMFVideoSampleAllocator^% Param_Out_Alocador)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis Utilizadas
		LPVOID pInterface = NULL;
		ICarenMFVideoSampleAllocator^ InterfaceSolictada = nullptr;

		//Chama o método que vai criar o alocador de amostras do D3D11
		Hr = MFCreateVideoSampleAllocatorEx(IID_IMFVideoSampleAllocatorEx, &pInterface);

		//Verifica o resultado da operação
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define falha na operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método.
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro
		InterfaceSolictada = gcnew CarenMFVideoSampleAllocator();

		//Chama o método para definir o ponteiro
		InterfaceSolictada->AdicionarPonteiro(pInterface);

		//Define a interface criada no parametro de saida.
		Param_Out_Alocador = InterfaceSolictada;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
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





	//Métodos da Interface Proprietaria.
public:
	/// <summary>
	/// (AllocateSample) - Obtém uma amostra de vídeo do alocador.
	/// </summary>
	/// <param name="Param_Out_AmostraVideo">Recebe a interface que contém a amostra de vídeo. O chamado deve liberar a interface.</param>
	virtual CarenResult AllocateSample([Out] ICarenMFSample^% Param_Out_AmostraVideo);

	/// <summary>
	/// (InitializeSampleAllocator) - Inicializa o alocador informando a quantidade de amostras para alocar e o tipo de mídia
	/// para cada amostra.
	/// As amostras alocadas devem ser compativeis com o IDirect3DDeviceManager9 - (D3D9).
	/// </summary>
	/// <param name="Param_CountAmostra">A quantidade de amostas para alocar.</param>
	/// <param name="Param_TipoAmostraVideo">Uma interface que contém o Tipo de mídia de vídeo que será alocada.</param>
	virtual CarenResult InitializeSampleAllocator(UInt32 Param_CountAmostra, ICarenMFMediaType^ Param_TipoAmostraVideo);

	/// <summary>
	/// (InitializeSampleAllocatorEx) - Inicializa o alocador informando a quantidade de amostras para alocar e o tipo de mídia
	/// para cada amostra.
	/// As amostras alocadas devem ser compativeis com o DXGI - (D3D11).
	/// </summary>
	/// <param name="Param_CountAmostra">A quantidade de amostas para alocar.</param>
	/// <param name="Param_TipoAmostraVideo">Uma interface que contém o Tipo de mídia de vídeo que será alocada.</param>
	virtual CarenResult InitializeSampleAllocatorEx(UInt32 Param_CountAmostra, ICarenMFMediaType^ Param_TipoAmostraVideo);

	/// <summary>
	/// (SetDirectXManager) - Especifica o dispositivo do gerenciamento do Direct3D para o coletor de mídia de vídeo utilizar.
	/// O coletor de mídia usa o Gerenciador de dispositivos Direct3D para obter um ponteiro para o dispositivo Direct3D, que ele usa para alocar superfícies Direct3D. O Gerenciador de dispositivos 
	/// habilita vários objetos no pipeline (como um processador de vídeo e um decodificador de vídeo) para compartilhar o mesmo dispositivo Direct3D.
	/// </summary>
	/// <param name="Param_Interface">A interface que o gerenciador do Direct3D a ser usado.</param>
	virtual CarenResult SetDirectXManager(ICaren^ Param_Interface);

	/// <summary>
	/// (UninitializeSampleAllocator) - Libera Todas as amostras de vídeo que tenham sido alocadas.
	/// </summary>
	virtual CarenResult UninitializeSampleAllocator();

};

