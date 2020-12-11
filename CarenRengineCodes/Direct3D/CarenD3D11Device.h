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
#include "../SDK_Direct3D11.h"
#include "../SDK_DXGI.h"
#include "../SDK_Utilidades.h"
#include "../Caren/Caren.h"
#include "../Caren/CarenBuffer.h"
#include "CarenD3D11DeviceContext.h"
#include "CarenD3D11Texture1D.h"
#include "CarenD3D11Texture2D.h"
#include "CarenD3D11Texture3D.h"
#include "CarenD3D11BlendState.h"
#include "CarenD3D11Buffer.h"
#include "CarenD3D11ClassLinkage.h"
#include "CarenD3D11ClassInstance.h"
#include "CarenD3D11Counter.h"
#include "CarenD3D11Predicate.h"
#include "CarenD3D11Query.h"
#include "CarenD3D11RasterizerState.h"
#include "CarenD3D11RenderTargetView.h"
#include "CarenD3D11SamplerState.h"
#include "CarenD3D11UnorderedAccessView.h"
#include "CarenD3D11ShaderResourceView.h"
#include "CarenD3D11VertexShader.h"
#include "CarenD3D11ComputeShader.h"
#include "CarenD3D11HullShader.h"
#include "CarenD3D11DomainShader.h"
#include "CarenD3D11GeometryShader.h"
#include "CarenD3D11PixelShader.h"
#include "CarenD3D11InputLayout.h"
#include "CarenD3D11DepthStencilState.h"
#include "CarenD3D11DepthStencilView.h"
#include "../DXGI\CarenDXGISwapChain.h"

//Importa o namespace que contém as interfaces do Microsoft Direct 3D.
using namespace CarenRengine::Direct3D11;

//Enumeração de retorno de função.


//DXGI namespace
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um adaptador virtual; é usado para criar recursos.
/// </summary>
public ref class CarenD3D11Device : public ICarenD3D11Device
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID3D11Device).
	ID3D11Device* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenD3D11Device();


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
	/// <param name="Param_Out_CarenD3D11Device">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD3D11Device^% Param_Out_CarenD3D11Device)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenD3D11Device = gcnew CarenD3D11Device();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Cria a instância de um dispositivo do Direct3D11.
	/// </summary>
	/// <param name="Param_Adaptador">Um ponteiro para o adaptador de vídeo para usar ao criar um dispositivo. Passe NULO para usar o adaptador padrão, que é o primeiro adaptador que é enumerado por ICarenDXGIFactory1::EnumerarAdaptadores.</param>
	/// <param name="Param_NiveisRecurso">Um array com os niveis de recurso que seram suportados pelo dispositivo.</param>
	/// <param name="Param_TipoDriver">O tipo do driver do dispositivo a ser criado.</param>
	/// <param name="Param_FlagsCreateDevice">Os flags utilizados para criar o dispositivo D3D 11.</param>
	/// <param name="Param_Out_NivelRecursoAceito">Recebe a enumeração que define o Nivel de recurso utilizado para criar o dispositivo.</param>
	/// <param name="Param_Out_Interface">Recebe a interface solicitada.</param>
	static CarenResult CriarInstancia(
		ICarenDXGIAdapter^ Param_Adaptador,
		cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso, 
		CA_D3D_TIPO_DRIVER Param_TipoDriver, 
		CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS Param_FlagsCreateDevice, 
		[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoAceito,
		[Out] ICarenD3D11Device^% Param_Out_Interface)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variveis utilizadas no método.
		Utilidades Util;
		IDXGIAdapter* pAdaptador = NULL;
		ID3D11Device* pInterfaceD3D = NULL;
		int TotalFlagsCreateDevice = (int)Param_FlagsCreateDevice;
		D3D11_CREATE_DEVICE_FLAG FlagCreateDevice = (D3D11_CREATE_DEVICE_FLAG)TotalFlagsCreateDevice;
		D3D_DRIVER_TYPE TipoDriver = (D3D_DRIVER_TYPE)Param_TipoDriver;
		int CountNiveisRecurso = Param_NiveisRecurso->Length;
		D3D_FEATURE_LEVEL* pNiveisRecurso = NULL;
		D3D_FEATURE_LEVEL NivelRecursoAceito;

		//Verifica se forneceu um adpatador de video.
		if (ObjetoGerenciadoValido(Param_Adaptador))
		{
			//Chama o método para recupera o ponteiro.
			Param_Adaptador->RecuperarPonteiro((LPVOID*)&pAdaptador);
		}

		//Verifica se forneceu os niveis de recurso.
		if (ObjetoGerenciadoValido(Param_NiveisRecurso))
		{
			//Obtém a quantidade de itens no array
			CountNiveisRecurso = Param_NiveisRecurso->Length;

			//Cria o array de niveis de recurso.
			pNiveisRecurso = CriarMatrizEstruturas<D3D_FEATURE_LEVEL>(CountNiveisRecurso);

			//Copia os dados para a matriz.
			Util.CopiarItensTo_ArrayNativo<D3D_FEATURE_LEVEL>(&pNiveisRecurso, Param_NiveisRecurso, CountNiveisRecurso);
		}

		//Chama o método que vai criar o dispositivo D3D 11
		ResultadoCOM Hr = D3D11CreateDevice(pAdaptador ? pAdaptador : NULL, TipoDriver, NULL, FlagCreateDevice, pNiveisRecurso? pNiveisRecurso: NULL, CountNiveisRecurso, D3D11_SDK_VERSION, &pInterfaceD3D, &NivelRecursoAceito, NULL);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}

		//Cria a interface que vai conter o ponteiro
		Param_Out_Interface = gcnew CarenD3D11Device();

		//Chama o método para definir o ponteiro
		Param_Out_Interface->AdicionarPonteiro(pInterfaceD3D);

		//Define o nivel de recurso que foi utilizado para criar o dispositivo.
		Param_Out_NivelRecursoAceito = static_cast<CA_D3D_NIVEL_RECURSO>(NivelRecursoAceito);

	Done:;
		//Deleta o array com os niveis de recurso.
		

		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Cria a instância de um dispositivo do Direct3D11 e fornece a possibilidade de retorna o seu Contexto Imediato.
	/// </summary>
	/// <param name="Param_Adaptador">Um ponteiro para o adaptador de vídeo para usar ao criar um dispositivo. Passe NULO para usar o adaptador padrão, que é o primeiro adaptador que é enumerado por ICarenDXGIFactory1::EnumerarAdaptadores.</param>
	/// <param name="Param_NiveisRecurso">Um array com os niveis de recurso que seram suportados pelo dispositivo.</param>
	/// <param name="Param_TipoDriver">O tipo do driver do dispositivo a ser criado.</param>
	/// <param name="Param_FlagsCreateDevice">Os flags utilizados para criar o dispositivo D3D 11.</param>
	/// <param name="Param_Out_NivelRecursoAceito">Recebe a enumeração que define o Nivel de recurso utilizado para criar o dispositivo.</param>
	/// <param name="Param_Out_ContextoDispositivo">Recebe a interface de contexto imediato do dispositivo criado.</param>
	/// <param name="Param_Out_Dispositivo">Recebe a interface solicitada.</param>
	static CarenResult CriarInstancia(
		ICarenDXGIAdapter^ Param_Adaptador,
		cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso, 
		CA_D3D_TIPO_DRIVER Param_TipoDriver, 
		CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS Param_FlagsCreateDevice, 
		[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoAceito,
		[Out] ICarenD3D11DeviceContext^% Param_Out_ContextoDispositivo, 
		[Out] ICarenD3D11Device^% Param_Out_Dispositivo)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variveis utilizadas no método.
		Utilidades Util;
		IDXGIAdapter* pAdaptador = NULL;
		ID3D11Device* pInterfaceD3D = NULL;
		ID3D11DeviceContext* pDeviceContext = NULL;
		int TotalFlagsCreateDevice = (int)Param_FlagsCreateDevice;
		D3D11_CREATE_DEVICE_FLAG FlagCreateDevice = (D3D11_CREATE_DEVICE_FLAG)TotalFlagsCreateDevice;
		D3D_DRIVER_TYPE TipoDriver = (D3D_DRIVER_TYPE)Param_TipoDriver;
		int CountNiveisRecurso = Param_NiveisRecurso->Length;
		D3D_FEATURE_LEVEL* pNiveisRecurso = NULL;
		D3D_FEATURE_LEVEL NivelRecursoAceito;

		//Verifica se forneceu um adpatador de video.
		if (ObjetoGerenciadoValido(Param_Adaptador))
		{
			//Chama o método para recupera o ponteiro.
			Param_Adaptador->RecuperarPonteiro((LPVOID*)&pAdaptador);
		}

		//Verifica se forneceu os niveis de recurso.
		if (ObjetoGerenciadoValido(Param_NiveisRecurso))
		{
			//Obtém a quantidade de itens no array
			CountNiveisRecurso = Param_NiveisRecurso->Length;

			//Cria o array de niveis de recurso.
			pNiveisRecurso = CriarMatrizEstruturas<D3D_FEATURE_LEVEL>(CountNiveisRecurso);

			//Copia os dados para a matriz.
			Util.CopiarItensTo_ArrayNativo<D3D_FEATURE_LEVEL>(&pNiveisRecurso, Param_NiveisRecurso, CountNiveisRecurso);
		}

		//Chama o método que vai criar o dispositivo D3D 11
		ResultadoCOM Hr = D3D11CreateDevice(pAdaptador ? pAdaptador : NULL, TipoDriver, NULL, FlagCreateDevice, pNiveisRecurso ? pNiveisRecurso : NULL, CountNiveisRecurso, D3D11_SDK_VERSION, &pInterfaceD3D, &NivelRecursoAceito, &pDeviceContext);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}

		//Cria as interfaces a serem retornadas.
		Param_Out_Dispositivo = gcnew CarenD3D11Device();
		Param_Out_ContextoDispositivo = gcnew CarenD3D11DeviceContext();

		//Define os ponteiros de trabalho.
		Param_Out_Dispositivo->AdicionarPonteiro(pInterfaceD3D);
		Param_Out_ContextoDispositivo->AdicionarPonteiro(pDeviceContext);

		//Define o nivel de recurso utilizado para criar com sucesso o dispositivo.
		Param_Out_NivelRecursoAceito = static_cast<CA_D3D_NIVEL_RECURSO>(NivelRecursoAceito);

	Done:;
		//Libera a memoria para o array de recursos.
		DeletarMatrizEstruturasSafe(&pNiveisRecurso);

		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Cria a instância de um dispositivo do D3D11 e fornece as interfaces: Cadeia de troca(SwapChain) e o Contexto Imediato(DeviceContext).
	/// </summary>
	/// <param name="Param_Adaptador">Um ponteiro para o adaptador de vídeo para usar ao criar um dispositivo. Passe NULO para usar o adaptador padrão, que é o primeiro adaptador que é enumerado por ICarenDXGIFactory1::EnumerarAdaptadores.</param>
	/// <param name="Param_NiveisRecurso">Um array com os niveis de recurso que seram suportados pelo dispositivo.</param>
	/// <param name="Param_TipoDriver">O tipo do driver do dispositivo a ser criado.</param>
	/// <param name="Param_FlagsCreateDevice">Os flags utilizados para criar o dispositivo D3D 11.</param>
	/// <param name="Param_Out_NivelRecursoAceito">Recebe a enumeração que define o Nivel de recurso utilizado para criar o dispositivo.</param>
	/// <param name="Param_Out_ContextoDispositivo">Recebe a interface de contexto imediato do dispositivo criado.</param>
	/// <param name="Param_Out_Dispositivo">Recebe a interface solicitada.</param>
	static CarenResult CriarInstanciaDispotivoESwapChain(
		ICarenDXGIAdapter^ Param_Adaptador,
		cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso,
		CA_D3D_TIPO_DRIVER Param_TipoDriver,
		CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS Param_FlagsCreateDevice,
		CA_DXGI_SWAP_CHAIN_DESC^ Param_DescSwapChain,
		[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoAceito,
		[Out] ICarenDXGISwapChain^% Param_Out_SwapChain,
		[Out] ICarenD3D11DeviceContext^% Param_Out_ContextoDispositivo,
		[Out] ICarenD3D11Device^% Param_Out_Dispositivo)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variveis utilizadas no método.
		Utilidades Util;
		IDXGIAdapter* pAdaptador = NULL; //Pode ser NULO.
		ID3D11Device* pInterfaceD3D = NULL;
		ID3D11DeviceContext* pDeviceContext = NULL;
		IDXGISwapChain* pSwapChain = NULL;
		DXGI_SWAP_CHAIN_DESC* pDescSwapChain = NULL;
		int TotalFlagsCreateDevice = (int)Param_FlagsCreateDevice;
		D3D11_CREATE_DEVICE_FLAG FlagCreateDevice = (D3D11_CREATE_DEVICE_FLAG)TotalFlagsCreateDevice;
		D3D_DRIVER_TYPE TipoDriver = (D3D_DRIVER_TYPE)Param_TipoDriver;
		int CountNiveisRecurso = 0;
		D3D_FEATURE_LEVEL* pNiveisRecurso = NULL; //Pode ser NULO.
		D3D_FEATURE_LEVEL NivelRecursoAceito;

		//Verifica se forneceu um adpatador de video.
		if (ObjetoGerenciadoValido(Param_Adaptador))
		{
			//Chama o método para recupera o ponteiro.
			Param_Adaptador->RecuperarPonteiro((LPVOID*)&pAdaptador);
		}

		//Verifica se forneceu os niveis de recurso.
		if(ObjetoGerenciadoValido(Param_NiveisRecurso))
		{
			//Obtém a quantidade de itens no array
			CountNiveisRecurso = Param_NiveisRecurso->Length;

			//Cria o array de niveis de recurso.
			pNiveisRecurso = CriarMatrizEstruturas<D3D_FEATURE_LEVEL>(CountNiveisRecurso);

			//Copia os dados para a matriz.
			Util.CopiarItensTo_ArrayNativo<D3D_FEATURE_LEVEL>(&pNiveisRecurso, Param_NiveisRecurso, CountNiveisRecurso);
		}

		//Converte a estrutura do SwapChain.
		pDescSwapChain = Util.ConverterDXGI_SWAP_CHAIN_DESCManaged_ToUnManaged(Param_DescSwapChain);

		//Chama o método que vai criar o dispositivo e a interface de cadeia de troca.
		ResultadoCOM Hr = D3D11CreateDeviceAndSwapChain(pAdaptador? pAdaptador: NULL, 
			TipoDriver, 
			NULL, 
			FlagCreateDevice, 
			pNiveisRecurso? pNiveisRecurso: NULL, 
			CountNiveisRecurso, 
			D3D11_SDK_VERSION, 
			pDescSwapChain, 
			&pSwapChain, &pInterfaceD3D, &NivelRecursoAceito, &pDeviceContext);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}

		//Cria as interfaces a serem retornadas.
		Param_Out_Dispositivo = gcnew CarenD3D11Device();
		Param_Out_ContextoDispositivo = gcnew CarenD3D11DeviceContext();
		Param_Out_SwapChain = gcnew CarenDXGISwapChain();

		//Define os ponteiros de trabalho.
		Param_Out_Dispositivo->AdicionarPonteiro(pInterfaceD3D);
		Param_Out_ContextoDispositivo->AdicionarPonteiro(pDeviceContext);
		Param_Out_SwapChain->AdicionarPonteiro(pSwapChain);

		//Define o nivel de recurso utilizado para criar com sucesso o dispositivo.
		Param_Out_NivelRecursoAceito = static_cast<CA_D3D_NIVEL_RECURSO>(NivelRecursoAceito);

	Done:;
		//Libera a memoria para o array de recursos.
		DeletarMatrizEstruturasSafe(&pNiveisRecurso);
		DeletarEstruturaSafe(&pDescSwapChain);

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




	//Métodos da interface(ICarenD3D11Device)
public:
	/// <summary>
	/// (CheckCounter) - Obter o tipo, nome, unidades de medida e uma descrição de um contador existente.
	/// </summary>
	/// <param name="Param_DescContador">Ponteiro para uma descrição do contador (CA_D3D11_DESC_CONTADOR). Especifica qual contador informação é para ser obtida sobre.</param>
	/// <param name="Param_Out_TipoDadoContador">Ponteiro para o tipo de dados de um contador (CA_D3D11_TIPO_DADO_CONTADOR). Especifica o tipo de dados do contador de ser obtido.</param>
	/// <param name="Param_Out_NumeroContadores">Ponteiro para o número de contadores de hardware que são necessários para esse tipo de contador ser criado. Todas as instâncias do mesmo tipo contador usam os contadores de hardware mesmo.</param>
	/// <param name="Param_Out_NomeContador">Sequência a ser preenchido com um nome breve para o contador. Pode ser NULL se o aplicativo não está interessado em nome do balcão.</param>
	/// <param name="Param_Out_LarguraNomeContador">Comprimento da sequência de caracteres retornada para Param_Out_NomeContador. Pode ser nulo.</param>
	/// <param name="Param_Out_NomeUnidadeMedidas">Nome das unidades de medidas um contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
	/// <param name="Param_Out_LarguraNomeUnidade">Comprimento da sequência de caracteres retornado para o Param_Out_NomeUnidadeMedidas. Pode ser nulo.</param>
	/// <param name="Param_Out_DescContador">Uma descrição do contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
	/// <param name="Param_Out_LarguraDescContador">Comprimento da sequência de caracteres retornada para Param_Out_DescContador. Pode ser nulo.</param>
	virtual CarenResult CheckCounter(
					Estruturas::CA_D3D11_DESC_CONTADOR^ Param_DescContador,
					[Out] Enumeracoes::CA_D3D11_TIPO_DADO_CONTADOR% Param_Out_TipoDadoContador, 
					[Out] UInt32% Param_Out_NumeroContadores,
					[Out] String^% Param_Out_NomeContador,
					[Out] UInt32% Param_Out_LarguraNomeContador,
					[Out] String^% Param_Out_NomeUnidadeMedidas,
					[Out] UInt32% Param_Out_LarguraNomeUnidade,
					[Out] String^% Param_Out_DescContador,
					[Out] UInt32% Param_Out_LarguraDescContador
				);

	/// <summary>
	/// (CheckCounterInfo) - Obter informações de um contador.
	/// </summary>
	/// <param name="Param_Out_InfoContador">Recebe uma estrutura com as informações do contador.</param>
	virtual CarenResult CheckCounterInfo([Out] Estruturas::CA_D3D11_INFO_CONTADOR^% Param_Out_InfoContador);

	/// <summary>
	/// (CheckFeatureSupport) - Obtém informações sobre os recursos que são suportados pelo driver de gráficos atuais.
	/// </summary>
	/// <param name="Param_RecursoPesquisa">Um membro do CA_D3D11_RECURSO tipo enumerado que descreve qual recurso de consulta para apoio.</param>
	/// <param name="Param_Out_SuporteRecurso">Após a conclusão do método, a passado estrutura é preenchida com dados que descreve o suporte para o recurso.</param>
	/// <param name="Param_Out_TamanhoEstrutura">O tamanho da estrutura passado para o parâmetro Param_Out_SuporteRecurso.</param>
	virtual CarenResult CheckFeatureSupport(
					Enumeracoes::CA_D3D11_RECURSO Param_RecursoPesquisa, 
					[Out] Estruturas::CA_D3D11_FEATURE_DATA_THREADING^% Param_Out_SuporteRecurso, 
					[Out] UInt32% Param_Out_TamanhoEstrutura
				);

	/// <summary>
	/// (CheckFormatSupport) - Obter o apoio de um determinado formato do dispositivo de vídeo instalado.
	/// </summary>
	/// <param name="Param_Formato">Uma enumeração de CA_DXGI_FORMAT que descreve um formato para o qual deseja verificar se há suporte.</param>
	/// <param name="Param_Out_RecursosSuportados">Um campo de bits de D3D11_FORMAT_SUPPORT valores de enumeração que descreve como o formato especificado 
	/// é suportado no dispositivo instalado. Os valores são ORed juntos.</param>
	virtual CarenResult CheckFormatSupport(
					Enumeracoes::CA_DXGI_FORMAT Param_Formato,
					[Out] Enumeracoes::CA_D3D11_FORMATO_SUPORTE% Param_Out_RecursosSuportados);

	/// <summary>
	/// (CheckMultisampleQualityLevels) - Obter o número de níveis de qualidade disponíveis durante multisampling completo.
	/// Quando multisampling uma textura, o número de níveis de qualidade disponíveis para um adaptador é dependente do formato de textura usado e o número de amostras 
	/// solicitadas. O número máximo de níveis de qualidade é definido pelo D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT em D3D11.h. Se esse método retorna 0, a combinação de 
	/// contagem de formato e amostra não tem suporte para o adaptador instalado.
	/// </summary>
	/// <param name="Param_Formato">O formato de textura. Consulte CA_DXGI_FORMAT.</param>
	/// <param name="Param_NumeroAmostras">O número de amostras durante multisampling completo.</param>
	/// <param name="Param_Out_NumeroNiveisQualidade">Recebe o número de níveis de qualidade suportada pelo adaptador.</param>
	virtual CarenResult CheckMultisampleQualityLevels(
					Enumeracoes::CA_DXGI_FORMAT Param_Formato, 
					UInt32 Param_NumeroAmostras, [Out] UInt32% Param_Out_NumeroNiveisQualidade);

	/// <summary>
	/// (CreateBlendState) - Crie um objeto de mistura-estado que encapsules o estado de combinação para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_DescMistura">Uma descrição do estado de mistura.</param>
	/// <param name="Param_Out_BlendState">Recebe uma interface para o objeto de estado de mistura criado.</param>
	virtual CarenResult CreateBlendState(
					Estruturas::CA_D3D11_BLEND_DESC^% Param_DescMistura, 
					[Out] ICarenD3D11BlendState^% Param_Out_BlendState);

	/// <summary>
	/// (CreateBuffer) - Cria um buffer (buffer de vértice, buffer de índice ou constante de sombreador buffer).
	/// </summary>
	/// <param name="Param_DescBuffer">Uma estrutura(CA_D3D11_BUFFER_DESC) que descreve o buffer.</param>
	/// <param name="Param_DescDadosInit">uma estrutura(CA_D3D11_SUBRESOURCE_DATA) que descreve os dados de inicialização; Use NULL para alocar espaço só(com a exceção que não pode ser NULL se o sinalizador de 
	/// uso é D3D11_USAGE_IMMUTABLE). Se você não passar nada para este paramêtro, o conteúdo inicial da memória para o buffer é indefinido. Neste caso, você precisa escrever o conteúdo do buffer de outra 
	/// maneira, antes que o recurso é lido.</param>
	/// <param name="Param_ValidarPametros">Defina como TRUE para validar os paramêtros de entrada do método. Se TRUE, Param_Out_InterfaceBuffer retorna NULO.</param>
	/// <param name="Param_Out_InterfaceBuffer">Recebe a interface ICarenD3D11Buffer para o objeto de buffer criado.</param>
	virtual CarenResult CreateBuffer(
					Estruturas::CA_D3D11_BUFFER_DESC^% Param_DescBuffer, 
					Estruturas::CA_D3D11_SUBRESOURCE_DATA^% Param_DescDadosInit, 
					Boolean Param_ValidarPametros,
					[Out] ICarenD3D11Buffer^% Param_Out_InterfaceBuffer);

	/// <summary>
	/// (CreateClassLinkage) - Cria bibliotecas de enlace de classe para permitir a ligação de sombreador dinâmico.
	/// </summary>
	/// <param name="Param_Out_ClassLinkage">Recebe a interface(ICarenD3D11ClassLinkage) de ligação de classe.</param>
	virtual CarenResult CreateClassLinkage([Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkage);

	/// <summary>
	/// (CreateComputeShader) - Crie um sombreador de computação.
	/// </summary>
	/// <param name="Param_SombreadorCompilado">Um ponteiro para um objeto que contém um sombreador compilado. Geralmente se obtém esse ponteiro através do método (ICarenD3D10Blod::ObterPonteiroBuffer)</param>
	/// <param name="Param_TamanhoSombreador">O Tamanho do sombreador no paramêtro(Param_SombreadorCompilado). Se está compilado com o ICarenD3D10Blod, utilize o método (ObterTamanhoBuffer) para recuperar esse valor.</param>
	/// <param name="Param_ClasseLigação">Um ponteiro para um ICarenD3D11ClassLinkage, que representa a interface de ligação de classe; o valor pode ser NULO.</param>
	/// <param name="Param_ValidarParametros">Se TRUE, o método vai validar os paramêtros de entrada. Se for validado com sucesso, o método retorna SS_FALSE em vez de S_OK.</param>
	/// <param name="Param_Out_ComputeShader">Recebe a interface(ICarenD3D11ComputeShader). Se (Param_ValidarPametros) for TRUE, esse parametro retorna um objeto NULO.</param>
	virtual CarenResult CreateComputeShader(
					ICaren^ Param_SombreadorCompilado, 
					UInt64 Param_TamanhoSombreador, 
					ICarenD3D11ClassLinkage^ Param_ClasseLigação, 
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader);

	/// <summary>
	/// (CreateCounter) - Crie um objeto de contador para medir o desempenho de GPU.
	/// </summary>
	/// <param name="Param_DescContador">Uma estrutura que contém a descrição do contador a ser criado.</param>
	/// <param name="Param_Out_ContadorGPU">Recebe a interface que contem uma descrição do contador.</param>
	virtual CarenResult CreateCounter(
					Estruturas::CA_D3D11_DESC_CONTADOR^% Param_DescContador, 
					[Out] ICarenD3D11Counter^% Param_Out_ContadorGPU);

	/// <summary>
	/// (CreateDeferredContext) - Cria um contexto diferido, que pode gravar listas de comando.
	/// </summary>
	/// <param name="Param_FlagsContexto">Reservado. Use 0.</param>
	/// <param name="Param_Out_D3D11Contexto">Recebe a interface ICarenD3D11DeviceContext.</param>
	virtual CarenResult CreateDeferredContext(
					UInt32 Param_FlagsContexto, 
					[Out] ICarenD3D11DeviceContext^% Param_Out_D3D11Contexto);

	/// <summary>
	/// (CreateDepthStencilState) - Crie um objeto de estado de profundidade-estêncil que encapsula as informações de teste de profundidade-estêncil para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_DepthStencil">Uma estrutura(CA_D3D11_DEPTH_STENCIL_DESC) que descreve o estado de profundidade do Stencil.</param>
	/// <param name="Param_Out_InterfaceStencil">Recebe a interface (ICarenD3D11DepthStencilState) de estado de profundidade do Stencil.</param>
	virtual CarenResult CreateDepthStencilState(
					Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_DepthStencil, 
					[Out] ICarenD3D11DepthStencilState^% Param_Out_InterfaceStencil);

	/// <summary>
	/// (CreateDepthStencilView) - Crie uma exibição de profundidade-estêncil para acessar dados de recurso.
	/// </summary>
	/// <param name="Param_Resource">Ponteiro para o recurso que irá servir como a profundidade-superfície estêncil. Este recurso deve ter sido criado com o sinalizador (D3D11_BIND_DEPTH_STENCIL).</param>
	/// <param name="Param_DepthStencilView">Ponteiro para uma descrição de profundidade-estêncil-vista. Defina este parâmetro como NULL para criar uma exibição que acessa o mipmap nível 0 do recurso 
	/// inteiro (usando o recurso foi criado com o formato).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_InterfaceStencilView retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_InterfaceStencilView">Recebe a interface do Depth Stencil View do D3D11.</param>
	virtual CarenResult CreateDepthStencilView(
					ICarenD3D11Resource^ Param_Resource, 
					Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_DepthStencilView, 
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11DepthStencilView^% Param_Out_InterfaceStencilView
				);

	/// <summary>
	/// (CreateDomainShader) - Crie um sombreador de domínio.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_DomainShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_DomainShader">Recebe a interface do Domain Shader.</param>
	virtual CarenResult CreateDomainShader(
		            ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode,
					ICarenD3D11ClassLinkage^ Param_Linkage, 
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11DomainShader^% Param_Out_DomainShader);

	/// <summary>
	/// (CreateGeometryShader) - Crie um sombreador de geometria.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
	virtual CarenResult CreateGeometryShader(
					ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode,
					ICarenD3D11ClassLinkage^ Param_Linkage,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader);

	/// <summary>
	/// (CreateGeometryShaderWithStreamOutput) - Cria um sombreador de geometria que pode gravar em streaming de buffers de saída.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_SODeclarationArray">Uma matriz de CA_D3D11_SO_DECLARATION_ENTRY. Não pode ser NULO se Param_NumeroEntradas > 0.</param>
	/// <param name="Param_NumeroEntradas">O número de entradas no fluxo de saída declaração (varia de 0 a D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT).</param>
	/// <param name="Param_BufferStrideArray">Uma matriz de passos de reserva; cada passo é do tamanho de um elemento para o buffer.</param>
	/// <param name="Param_NumeroStrides">O número de passos (ou buffers) em Param_BufferStrideArray (varia de 0 a D3D11_SO_BUFFER_SLOT_COUNT).</param>
	/// <param name="Param_NumeroIndicesFluxo">O número de índice do fluxo a ser enviado para o palco do rasterizador (varia de 0 a D3D11_SO_STREAM_COUNT - 1). Conjunto para D3D11_SO_NO_RASTERIZED_STREAM se nenhum fluxo for ser rasterizada.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
	virtual CarenResult CreateGeometryShaderWithStreamOutput
				(
					ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode,
					cli::array<Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^>^ Param_SODeclarationArray,
					UInt32 Param_NumeroEntradas,
					cli::array<UInt32>^ Param_BufferStrideArray,
					UInt32 Param_NumeroStrides,
					UInt32 Param_NumeroIndicesFluxo,
					ICarenD3D11ClassLinkage^ Param_Linkage,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader
				);

	/// <summary>
	/// (CreateHullShader) - Crie um sombreador de casco.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_Out_HullShader">Recebe a interface do Hull Shader.</param>
	virtual CarenResult CreateHullShader(
					ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode, 
					ICarenD3D11ClassLinkage^ Param_Linkage,
					[Out] ICarenD3D11HullShader^% Param_Out_HullShader
					);

	/// <summary>
	/// (CreateInputLayout) - Crie um objeto de entrada-layout para descrever os dados do buffer de entrada para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_ArrayTiposDadosEntrada">Uma matriz de tipos de dados de entrada do estágio de entrada-montador; cada tipo é descrito por uma descrição do elemento</param>
	/// <param name="Param_CountElementos">O número de tipos de dados de entrada na matriz de elementos de entrada.</param>
	/// <param name="Param_ShaderByteCode">Um ponteiro para o shader compilado. O código compilado de sombreador contém uma assinatura de entrada que é validada contra a matriz de elementos.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Out_InputLayout">Recebe a interface do Input Layout.</param>
	virtual CarenResult CreateInputLayout(
					cli::array<Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^>^ Param_ArrayTiposDadosEntrada, 
					UInt32 Param_CountElementos, 
					ICaren^ Param_ShaderByteCode, 
					UInt64 Param_TamanhoByteCode,
					[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout
				);

	/// <summary>
	/// (CreatePixelShader) - Crie um sombreador de pixel.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_PixelShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_PixelShader">Recebe a interface do Hull Shader.</param>
	virtual CarenResult CreatePixelShader(
					ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode,
					ICarenD3D11ClassLinkage^ Param_Linkage,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11PixelShader^% Param_Out_PixelShader);

	/// <summary>
	/// (CreatePredicate) - Cria um predicado.
	/// </summary>
	/// <param name="Param_DescPredicado">Ponteiro para uma descrição de consulta onde o tipo de consulta deve ser uma D3D11_QUERY_SO_OVERFLOW_PREDICATE ou D3D11_QUERY_OCCLUSION_PREDICATE</param>
	/// <param name="Param_Out_Predicado">Recebe a interface do Predicado criado.</param>
	virtual CarenResult CriarPredicado(
					Estruturas::CA_D3D11_QUERY_DESC^% Param_DescPredicado, 
					[Out] ICarenD3D11Predicate^% Param_Out_Predicado);

	/// <summary>
	/// (CreateQuery) - Essa interface encapsula métodos para consultar informações da GPU.
	/// </summary>
	/// <param name="Param_DescQuery">Uma descrição da interface de consulta a ser criada.</param>
	/// <param name="Param_Out_Query">Recebe a interface de consulta criada.</param>
	virtual CarenResult CreateQuery(
					Estruturas::CA_D3D11_QUERY_DESC^% Param_DescQuery, 
					[Out] ICarenD3D11Query^% Param_Out_Query);

	/// <summary>
	/// (CreateRasterizerState) - Crie um objeto de estado rasterizador que informa o rasterizador de palco como se comportar.
	/// </summary>
	/// <param name="Param_DescRasterizador">Uma estrutura com a descrição do estado do rasterizador.</param>
	/// <param name="Param_Out_Rasterizador">Recebe a interface de Rasterização criada.</param>
	virtual CarenResult CreateRasterizerState(
					Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_DescRasterizador, 
					[Out] ICarenD3D11RasterizerState^% Param_Out_Rasterizador);

	/// <summary>
	/// (CreateRenderTargetView) - Cria uma exibição de destino de processamento para acesso a dados de recurso.
	/// </summary>
	/// <param name="Param_Resource">Um ponteiro para interface ID3D11Resource que representa um destino de processamento. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_RENDER_TARGET .</param>
	/// <param name="Param_DescRender">Uma estrutura D3D11_RENDER_TARGET_VIEW_DESC que representa uma descrição do modo de exibição render-alvo. Defina este parâmetro como NULL para criar uma exibição 
	/// que acessa todos os sub-recursos mipmap nível 0.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ViewRender retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_ViewRender">Recebe a interface do visualizador de render.</param>
	virtual CarenResult CreateRenderTargetView(
					ICarenD3D11Resource^ Param_Resource, 
					Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11RenderTargetView^% Param_Out_ViewRender);

	/// <summary>
	/// (CreateSamplerState) - Crie um objeto de sampler-estado que encapsula as informações de amostragem para uma textura.
	/// </summary>
	/// <param name="Param_DescSampler">Uma descrição do estado do amostrador</param>
	/// <param name="Param_Out_SamplerState">Recebe a interface do Sampler Sate.</param>
	virtual CarenResult CreateSamplerState(
					Estruturas::CA_D3D11_SAMPLER_DESC^% Param_DescSampler, 
					[Out] ICarenD3D11SamplerState^% Param_Out_SamplerState);
																
	/// <summary>
	/// (CreateShaderResourceView) - Crie uma exibição de sombreador-recurso para acessar dados em um recurso.
	/// </summary>
	/// <param name="Param_Recurso">Ponteiro para o recurso que irá servir como entrada para um sombreador. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_SHADER_RESOURCE .</param>
	/// <param name="Param_DescExbi">Ponteiro para uma descrição de exibição de sombreador-recurso (veja D3D11_SHADER_RESOURCE_VIEW_DESC). Defina este parâmetro como NULL para criar uma 
	/// exibição que acessa o recurso inteiro (usando o recurso foi criado com o formato).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ShaderView retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_ShaderView">Recebe a interface para o visualizador de Shader.</param>
	virtual CarenResult CreateShaderResourceView(
					ICarenD3D11Resource^ Param_Recurso, 
					Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_DescExbi,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11ShaderResourceView^% Param_Out_ShaderView);

	/// <summary>
	/// (CreateTexture1D) - Cria uma matriz de texturas 1D.
	/// </summary>
	/// <param name="Param_DescTextura1D">Uma estrutura CA_D3D11_TEXTURE1D_DESC que descreve um recurso de textura 1D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
	/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
	/// mipmap para 0.</param>
	/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 1D. Aplicativos não é possível especificar NULL para 
	/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
	/// quando eles são criados.</param>
	/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura1D retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_Textura1D">Recebe a interface que contém o buffer da interface de Textura 1D.</param>
	virtual CarenResult CreateTexture1D(
					Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_DescTextura1D, 
					cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
					UInt32 Param_TamanhoArraySubRecursos,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11Texture1D^% Param_Out_Textura1D);

	/// <summary>
	/// (CreateTexture2D) - Crie uma matriz de texturas 2D.
	/// </summary>
	/// <param name="Param_DescTextura2D">Uma estrutura CA_D3D11_TEXTURE2D_DESC que descreve um recurso de textura 2D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
	/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
	/// mipmap para 0.</param>
	/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 2D. Aplicativos não é possível especificar NULL para 
	/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
	/// quando eles são criados.</param>
	/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura2D retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_Textura2D">Recebe a interface que contém o buffer da interface de Textura 2D.</param>
	virtual CarenResult CreateTexture2D(
					Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_DescTextura2D,
					cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
					UInt32 Param_TamanhoArraySubRecursos,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11Texture2D^% Param_Out_Textura2D);

	/// <summary>
	/// (CreateTexture3D) - Crie uma única textura 3D.
	/// </summary>
	/// <param name="Param_DescTextura3D">Uma estrutura CA_D3D11_TEXTURE3D_DESC que descreve um recurso de textura 3D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
	/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
	/// mipmap para 0.</param>
	/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 3D. Aplicativos não é possível especificar NULL para 
	/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
	/// quando eles são criados.</param>
	/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura3D retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_Textura3D">Recebe a interface que contém o buffer da interface de Textura 3D.</param>
	virtual CarenResult CreateTexture3D(
					Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_DescTextura3D,
					cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
					UInt32 Param_TamanhoArraySubRecursos,
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11Texture3D^% Param_Out_Textura3D);

	/// <summary>
	/// (CreateUnorderedAccessView) - Cria uma visão para acessar um recurso de acesso não ordenada.
	/// </summary>
	/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
	/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
	/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
	/// <param name="Param_Out_Interface">Recebe a interface do Recurso de acesso não ordenado.</param>
	virtual CarenResult CreateUnorderedAccessView(
					ICarenD3D11Resource^ Param_Recurso,
					Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_DescSombreador, 
					[Out] ICarenD3D11UnorderedAccessView^% Param_Out_Interface);

	/// <summary>
	/// (CreateVertexShader) - Crie um objeto shader de vértice de um sombreador compilado.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_VertexShaderInterface retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_VertexShader">Recebe a interface do Vertex Shader.</param>
	virtual CarenResult CreateVertexShader(
					ICaren^ Param_ShaderByteCode,
					UInt64 Param_TamanhoByteCode,
					ICarenD3D11ClassLinkage^ Param_Linkage, 
					Boolean Param_ValidarParametros,
					[Out] ICarenD3D11VertexShader^% Param_Out_VertexShader);

	/// <summary>
	/// (GetCreationFlags) - Se os sinalizadores usados durante a chamada para criar o dispositivo com D3D11CreateDevice.
	/// </summary>
	/// <param name="Param_Out_Flags">Recebe um flags de bit a bits da enumerção (CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS) que contém o modo de criaçã do dispositivo.</param>
	virtual CarenResult GetCreationFlags([Out] Enumeracoes::CA_D3D11_CRIACAO_DISPOSITIVO_FLAGS% Param_Out_Flags);

	/// <summary>
	/// (GetDeviceRemovedReason) - A razão por que o dispositivo foi removido. Esse método retorna um (ResultCode) informando o motivo.
	/// </summary>
	virtual CarenResult GetDeviceRemovedReason();

	/// <summary>
	/// (GetExceptionMode) - Obter os sinalizadores de modo de exceção.
	/// </summary>
	/// <param name="Param_Out_Except">Um valor que contém um ou mais sinalizadores de exceção; Cada sinalizador especifica uma condição que fará com que uma exceção seja levantada. Os sinalizadores estão 
	/// listados em D3D11_RAISE_FLAG. Um valor padrão de 0 significa que não há sinalizadores.</param>
	virtual CarenResult GetExceptionMode([Out] Enumeracoes::CA_D3D11_RAISE_FLAG% Param_Out_Except);

	/// <summary>
	/// (GetFeatureLevel) - Obtém o nível de funcionalidade de dispositivo de hardware.
	/// </summary>
	/// <param name="Param_Out_NivelRecurso">Recebe um flag de bits a bits de um ou mais sinlizadores de niveis de recuso do dispositivo de hardware.</param>
	virtual CarenResult GetFeatureLevel([Out] Enumeracoes::CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecurso);

	/// <summary>
	/// (GetImmediateContext) - Obtém um contexto imediato, que pode reproduzir listas de comando.
	/// </summary>
	/// <param name="Param_Out_ImediateContextInterface">Recebe a interface do contexto do dispositivo.</param>
	virtual CarenResult GetImmediateContext([Out] ICarenD3D11DeviceContext^% Param_Out_ImediateContextInterface);

	/// <summary>
	/// (GetPrivateData) - Obtém os dados definidos pelo aplicativo de um dispositivo.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado ao buffer.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer de saida.</param>
	/// <param name="Param_Out_TamanhoBufferSaida">Recebe o tamanho que total do buffer no parametro (Param_Out_Buffer).</param>
	/// <param name="Param_Out_Buffer">Recebe a interface que gerencia o buffer retornado.</param>
	virtual CarenResult GetPrivateData(
					String^ Param_Guid, 
					UInt32 Param_TamanhoBuffer, 
					[Out] UInt32% Param_Out_TamanhoBufferSaida, 
					[Out] ICarenBuffer^% Param_Out_Buffer);

	/// <summary>
	/// (OpenSharedResource) - Dar um dispositivo de acesso a um recurso compartilhado, criado em um dispositivo diferente.
	/// </summary>
	/// <param name="Param_Handle">Um identificador de recurso.</param>
	/// <param name="Param_GuidInterface">O identificador globalmente exclusivo (GUID) para a interface do recurso.</param>
	/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface do recurso que foi ganhado acesso. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult OpenSharedResource(
					IntPtr Param_Handle, 
					String^ Param_GuidInterface, 
					ICaren^ Param_Out_InterfaceSolicitada);

	/// <summary>
	/// (SetExceptionMode) - Obter os sinalizadores de modo de exceção.
	/// </summary>
	/// <param name="Param_RaiseFlags">Os flags de modo de exceção.</param>
	virtual CarenResult SetExceptionMode(UInt32 Param_RaiseFlags);

	/// <summary>
	/// (SetPrivateData) - Define os dados para um dispositivo e associa esses dados a um guid.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado ao buffer.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer de entrada.</param>
	/// <param name="Param_Buffer">Ponteiro para os dados sejam armazenados com este dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer dados anteriormente associados com o 
	/// guid serão destruídos.</param>
	virtual CarenResult SetPrivateData(
					String^ Param_Guid, 
					UInt32 Param_TamanhoBuffer, 
					ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// (SetPrivateDataInterface) - Associar uma interface IUnknown-derivado desta criança de dispositivo e associar essa interface com um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado a interface a ser definida.</param>
	/// <param name="Param_Interface">Ponteiro para uma interface derivada de IUnknown para ser associado ao filho do dispositivo.</param>
	virtual CarenResult SetPrivateDataInterface(
					String^ Param_Guid, 
					ICaren^ Param_Interface);
};