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
#include "CarenChannelAudioVolume.h"


//Destruidor.
CarenChannelAudioVolume::~CarenChannelAudioVolume()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenChannelAudioVolume::CarenChannelAudioVolume()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenChannelAudioVolume::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenChannelAudioVolume::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IChannelAudioVolume*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IChannelAudioVolume**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenChannelAudioVolume::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IChannelAudioVolume*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IChannelAudioVolume**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenChannelAudioVolume::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenChannelAudioVolume::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenChannelAudioVolume::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenChannelAudioVolume::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenChannelAudioVolume::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenChannelAudioVolume::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenChannelAudioVolume::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenChannelAudioVolume();
}






//
// Métodos da interface proprietária(ICarenChannelAudioVolume)
//

/// <summary>
/// (GetAllVolumes) - O método recupera os níveis de volume para todos os canais na sessão de áudio.
/// </summary>
/// <param name="Param_QuantidadeCanais">A quantidade de canais no formato do fluxo. Chame o método (GetChannelCount) para obter a quantidade total.</param>
/// <param name="Param_Out_ArrayVolumes">Retorna um array que contém o nivel de volume de cada canal na sessão de áudio. Os níveis de volume estão no intervalo 0,0 a 1,0.</param>
CarenResult CarenChannelAudioVolume::GetAllVolumes(UInt32 Param_QuantidadeCanais, [Out] cli::array<float>^% Param_Out_ArrayVolumes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	pin_ptr<float> pArrayFloatingVolumes = nullptr;

	//Cria o array gerenciado que vai retornar os dados.
	Param_Out_ArrayVolumes = gcnew cli::array<float>(Param_QuantidadeCanais);

	//Fixa um ponteiro para o primeiro elemento na matriz.
	pArrayFloatingVolumes = &Param_Out_ArrayVolumes[0];

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAllVolumes(Param_QuantidadeCanais, pArrayFloatingVolumes);

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

/// <summary>
/// (GetChannelCount) - O método recupera o número de canais no formato de fluxo para a sessão de áudio.
/// </summary>
/// <param name="Param_QuantidadeCanais">Retorna a quantidade de canais.</param>
CarenResult CarenChannelAudioVolume::GetChannelCount([Out] UInt32% Param_QuantidadeCanais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UInt32 CountCanais = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetChannelCount(&CountCanais);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida
	Param_QuantidadeCanais = CountCanais;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetChannelVolume) - O método recupera o nível de volume para o canal especificado na sessão de áudio.
/// </summary>
/// <param name="Param_NumeroCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N- 1.</param>
/// <param name="Param_Out_NivelVolume">Retorna uma variável no qual o método grava o nível de volume do canal especificado. O nível de volume está no intervalo de 0.0 a 1.0.</param>
CarenResult CarenChannelAudioVolume::GetChannelVolume(UInt32 Param_NumeroCanal, [Out] float% Param_Out_NivelVolume)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	float VolumeCanal = 0.0f;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetChannelVolume(Param_NumeroCanal, &VolumeCanal);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o volume no paramêtro de saida
	Param_Out_NivelVolume = VolumeCanal;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetAllVolumes) - O método define os níveis de volume individuais para todos os canais na sessão de áudio.
/// </summary>
/// <param name="Param_QuantidadeItens">A quantidade de itens no array(Param_ArrayVolumes).</param>
/// <param name="Param_ArrayVolumes">Um array que contém o nivel de volume para cada canal do fluxo na sessão de áudio.</param>
/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume de canal, o Gerenciador 
/// de sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
CarenResult CarenChannelAudioVolume::SetAllVolumes(UInt32 Param_QuantidadeItens, cli::array<float>^ Param_ArrayVolumes, String^ Param_ContextoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	pin_ptr<float> pArrayVolume = &Param_ArrayVolumes[0];
	GUID pGuidContextoEvento = GUID_NULL;

	//Verifica se foi fornecido o contexto do evento.
	if (!String::IsNullOrEmpty(Param_ContextoEvento))
	{
		//Converte a string para o GUID.
		pGuidContextoEvento = Util.CreateGuidFromString(Param_ContextoEvento);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAllVolumes(Param_QuantidadeItens, pArrayVolume, &pGuidContextoEvento);

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

/// <summary>
/// (SetChannelVolume) - O método define o nível de volume para o canal especificado na sessão de áudio.
/// </summary>
/// <param name="Param_IndexCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N- 1.</param>
/// <param name="Param_Volume">O novo nivel de volume que será definido ao canal.</param>
/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume de canal, o Gerenciador 
/// de sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
CarenResult CarenChannelAudioVolume::SetChannelVolume(UInt32 Param_IndexCanal, float Param_Volume, String^ Param_ContextoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID pGuidContextoEvento = GUID_NULL;

	//Verifica se foi fornecido o contexto do evento.
	if (!String::IsNullOrEmpty(Param_ContextoEvento))
	{
		//Converte a string para o GUID.
		pGuidContextoEvento = Util.CreateGuidFromString(Param_ContextoEvento);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetChannelVolume(Param_IndexCanal, Param_Volume, &pGuidContextoEvento);

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