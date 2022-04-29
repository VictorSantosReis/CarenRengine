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

#include "../pch.h"
#include "CarenWICBitmapCodecProgressNotification.h"

//Destruidor.
CarenWICBitmapCodecProgressNotification::~CarenWICBitmapCodecProgressNotification()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;

	//Limpa o ponteiro de eventos.
	delete pWicBitmapProgresClass;
	pWicBitmapProgresClass = NULL;
}
//Construtores
CarenWICBitmapCodecProgressNotification::CarenWICBitmapCodecProgressNotification()
{
	//Cria a classe responsável por receber os eventos.
	pWicBitmapProgresClass = new CLN_WicBitmapProgress();
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenWICBitmapCodecProgressNotification::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapCodecProgressNotification::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapCodecProgressNotification*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapCodecProgressNotification**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapCodecProgressNotification::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapCodecProgressNotification*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapCodecProgressNotification**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapCodecProgressNotification::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapCodecProgressNotification::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICBitmapCodecProgressNotification::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICBitmapCodecProgressNotification::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapCodecProgressNotification::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapCodecProgressNotification::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapCodecProgressNotification::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICBitmapCodecProgressNotification::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICBitmapCodecProgressNotification();
}



// Métodos da interface proprietária(ICarenWICBitmapCodecProgressNotification)


/// <summary>
/// Registra uma função de retorno de chamada de notificação de progresso. Permite que o usuário implemente seu proprio retorno de chamada sem precisar usar o evento disponivel nessa classe.
/// Os aplicativos só podem registrar um único retorno de chamada. As chamadas de registro subsequentes substituirão o retorno de chamada previamente registrado. Para não registrar 
/// um retorno de chamada, passe no NULO ou registre uma nova função de retorno de chamada. O progresso é relatado em uma ordem crescente entre 0,0 e 1.0. Se o (Param_FlagsProgresso) 
/// incluir o WICProgressNotificationBegin, o retorno de chamada é garantido para ser chamado com o progresso 0.0. Se o (Param_FlagsProgresso) incluir o WICProgressNotificationEnd, 
/// o retorno de chamada é garantido para ser chamado com o progresso 1.0. WICProgressNotificaçãoFrequent aumenta a frequência em que o retorno de chamada é chamado. Se uma operação 
/// for esperada para levar mais de 30 segundos, o WICProgressNotificationFrequent deve ser adicionado ao (Param_FlagsProgresso).
/// </summary>
/// <param name="Param_Callback">Uma interface(ICaren) que contém um ponteiro de função para a função de chamada de notificação de progresso definida pelo aplicativo.</param>
/// <param name="Param_ComponenteData">Uma interface(ICaren) que contém um ponteiro para componente de dados para o método de retorno de chamada.</param>
/// <param name="Param_FlagsProgresso">As bandeiras CA_WICProgressOperation e CA_WICProgressNotification para uso para notificação de progresso.</param>
CarenResult CarenWICBitmapCodecProgressNotification::RegisterProgressNotification(
ICaren^ Param_Callback,
ICaren^ Param_ComponenteData,
UInt32 Param_FlagsProgresso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LPVOID pCallback = NULL;
	LPVOID* pComponentData = NULL;

	//Recupera o ponteiro para o callback
	Resultado = RecuperarPonteiroCaren(Param_Callback, &pCallback);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o componente.
	Resultado = RecuperarPonteiroCaren(Param_ComponenteData, &pComponentData);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterProgressNotification(reinterpret_cast<PFNProgressNotification>(pCallback), pComponentData, static_cast<DWORD>(Param_FlagsProgresso));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}


//Métodos que registram e deletam os dados dos eventos.

/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenWICBitmapCodecProgressNotification::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnProgressNotification = gcnew DelegateNativo_Evento_OnProgressNotification(this, &CarenWICBitmapCodecProgressNotification::EncaminharEvento_OnProgressNotification);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnProgressNotification = Util.ConverterDelegateToPointer(Callback_OnProgressNotification);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnProgressNotification = Util.AlocarPointerDelegate(Pointer_OnProgressNotification);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
	pWicBitmapProgresClass->Evento_Progresso = Util.ConverterPointerDelegateToNativeDelegate<PFNProgressNotification>(Pointer_OnProgressNotification);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenWICBitmapCodecProgressNotification::UnRegisterCallback()
{
	//Libera a alça para o evento.
	gHandle_Delegate_OnProgressNotification.Free();

	//Nula os ponteiros.
	if (ObjetoValido(pWicBitmapProgresClass->Evento_Progresso))
	{
		//Nula o evento.
		pWicBitmapProgresClass->Evento_Progresso = NULL;
	}
}


//Métodos que encaminha os eventos para o usuário.

HRESULT CarenWICBitmapCodecProgressNotification::EncaminharEvento_OnProgressNotification(LPVOID pvData, ULONG uFrameNum, WICProgressOperation operation, double dblProgress)
{
	//Varivaeis
	CarenResult Resultado = CarenResult(ResultCode::SS_OK, true);
	ICarenBuffer^ pBufferDados = gcnew CarenBuffer();
	CA_WICProgressOperation ProgresOp = static_cast<CA_WICProgressOperation>(operation);

	//Cria o buffer como um ponteiro para os dados.
	pBufferDados->CreateBuffer(IntPtr(pvData), false, 0, 0);

	//Chama o evento para notificar o usuário
	Resultado = OnProgressNotification(pBufferDados, uFrameNum, ProgresOp, dblProgress);

	//Retorna o resultado do evento.
	return static_cast<HRESULT>(Resultado.HResult);
}
