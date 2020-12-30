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
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenD2D1DeviceContext.h"
#include "CarenD2D1DeviceContext1.h"
#include "CarenD2D1DeviceContext2.h"
#include "CarenD2D1PrintControl.h"
#include "../DXGI/CarenDXGIDevice.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. 
/// Esta interface executa todas as mesmas funções da interface ICarenD2D1Device1 existente.
/// </summary>
public ref class CarenD2D1Device2 : public ICarenD2D1Device2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Device2).
	ID2D1Device2* PonteiroTrabalho = NULL;


	//Contrutor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1Device2();

	~CarenD2D1Device2();

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


	//Métodos da interface(ICarenD2D1Device2)
public:
	/// <summary>
	/// Cria um novo ICarenD2D1DeviceContext2 a partir de um dispositivo Direct2D.
	/// </summary>
	/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
	/// <param name="Param_Out_ContextoDispositivo2">Retorna uma interface(ICarenD2D1DeviceContext2) que contém um ponteiro para o novo contexto do dispositivo.</param>
	virtual CarenResult CreateDeviceContext(
	CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
	[Out] ICarenD2D1DeviceContext2^% Param_Out_ContextoDispositivo2);

	/// <summary>
	/// Limpa todos os contextos do dispositivo que fazem referência a um determinado bitmap.
	/// </summary>
	/// <param name="Param_Bitmap">O bitmap, criado neste dispositivo, para o qual todos os contextos do dispositivo de referência serão limpos.</param>
	virtual void FlushDeviceContexts(ICarenD2D1Bitmap^ Param_Bitmap);

	/// <summary>
	/// Retorna o dispositivo DXGI associado a este dispositivo Direct2D.
	/// </summary>
	/// <param name="Param_Out_DxgiDevice">Retorna uma interface(ICarenDXGIDevice) que contém um ponteiro para o dispositivo DXGI associado a este dispositivo Direct2D.</param>
	virtual CarenResult GetDxgiDevice([Out] ICarenDXGIDevice^% Param_Out_DxgiDevice);


	//Métodos da interface(ICarenD2D1Device1)
public:
	/// <summary>
	/// Cria um novo ICarenD2D1DeviceContext1 a partir de um dispositivo Direct2D.
	/// </summary>
	/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
	/// <param name="Param_Out_ContextoDispositivo1">Retorna uma interface(ICarenD2D1DeviceContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
	virtual CarenResult CreateDeviceContext(
		CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
		[Out] ICarenD2D1DeviceContext1^% Param_Out_ContextoDispositivo1);

	/// <summary>
	/// Recupera a prioridade de renderização atual do dispositivo.
	/// </summary>
	/// <param name="Param_Out_Prioridade">Retorna a prioridade de renderização atual do dispositivo.</param>
	virtual void GetRenderingPriority(
		[Out] CA_D2D1_RENDERING_PRIORITY% Param_Out_Prioridade);

	/// <summary>
	/// Define a prioridade das operações de renderização Direct2D realizadas em qualquer contexto de dispositivo associado ao dispositivo.
	/// </summary>
	/// <param name="Param_Prioridade">A prioridade de renderização desejada para o dispositivo e contextos associados.</param>
	virtual void SetRenderingPriority(CA_D2D1_RENDERING_PRIORITY Param_Prioridade);


	//Métodos da interface(ICarenD2D1Device)
public:
	/// <summary>
	/// Libera todos os recursos de renderização utilizados pelo Direct2D.
	/// </summary>
	/// <param name="Param_Miliseconds">Descarta apenas recursos que não foram usados por mais do que o tempo especificado em milissegundos. O padrão é de 0 milissegundos.</param>
	virtual void ClearResources(UInt32 Param_Miliseconds);

	/// <summary>
	/// Cria um novo contexto de dispositivo a partir de um dispositivo Direct2D.
	/// O novo contexto do dispositivo não terá um bitmap de destino selecionado. O chamador deve criar e selecionar um bitmap como a superfície alvo do contexto.
	/// </summary>
	/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
	/// <param name="Param_Out_ContextoDispositivo">Retorna uma interface(ICarenD2D1DeviceContext) que contém um ponteiro para o novo contexto do dispositivo. </param>
	virtual CarenResult CreateDeviceContext(
		CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
		[Out] ICarenD2D1DeviceContext^% Param_Out_ContextoDispositivo);

	/// <summary>
	/// Cria um objeto ICarenD2D1PrintControl que converte primitivos Direct2D armazenados no ICarenD2D1CommandList em uma representação de página fixa. O subsistema de impressão então consome os primitivos.
	/// </summary>
	/// <param name="Param_WicImagingFactory">Uma interface(ICarenWICImagingFactory) que representa a fábrica de imagens WIC.</param>
	/// <param name="Param_PrintDocumentPackage">Uma interface(IPrintDocumentPackageTarget)[NAO IMPLEMENTADA POR ESSA API] que representa o alvo de trabalho de impressão.</param>
	/// <param name="Param_PropsControlPrint">As opções a serem aplicadas ao controle de impressão.</param>
	/// <param name="Param_Out_PrintControl">Retorna uma interface(ICarenD2D1PrintControl) que contém um ponteiro para o objeto D2D1PrintControl.</param>
	virtual CarenResult CreatePrintControl(
		ICaren^ Param_WicImagingFactory,
		ICaren^ Param_PrintDocumentPackage,
		CA_D2D1_PRINT_CONTROL_PROPERTIES^ Param_PropsControlPrint,
		[Out] ICarenD2D1PrintControl^% Param_Out_PrintControl);


	/// <summary>
	/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
	/// </summary>
	/// <param name="Param_Out_MaxSizeMemory">Retorna a quantidade máxima de memória de textura em bytes.</param>
	virtual void GetMaximumTextureMemory([Out] UInt64% Param_Out_MaxSizeMemory);

	/// <summary>
	/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
	///  O Direct2D pode exceder a memória de textura máxima que você define com este método para um único quadro, se necessário, para renderizar o quadro.
	/// </summary>
	/// <param name="Param_MaxSizeMemory">A nova quantidade máxima de memória em bytes para a textura.</param>
	virtual void SetMaximumTextureMemory(UInt64 Param_MaxSizeMemory);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};