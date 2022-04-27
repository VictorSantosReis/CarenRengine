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
#include "CarenMFQualityAdvise2.h"

//Destruidor.
CarenMFQualityAdvise2::~CarenMFQualityAdvise2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFQualityAdvise2::CarenMFQualityAdvise2()
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
CarenResult CarenMFQualityAdvise2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFQualityAdvise2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFQualityAdvise2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFQualityAdvise2**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFQualityAdvise2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFQualityAdvise2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFQualityAdvise2**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFQualityAdvise2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFQualityAdvise2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFQualityAdvise2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFQualityAdvise2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFQualityAdvise2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFQualityAdvise2::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFQualityAdvise2::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFQualityAdvise2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFQualityAdvise2();
}



// Métodos da interface proprietária(ICarenMFQualityAdvise2)


/// <summary>
/// Encaminhe um evento MEQualityNotify do sink da mídia.
/// </summary>
/// <param name="Param_Evento">Uma interface ICarenMFMediaEvent para o evento.</param>
/// <param name="Param_Out_Flags">Recebe um Or bitwise de zero ou mais bandeiras da enumeração CA_MF_QUALITY_ADVISE_FLAGS.</param>
CarenResult CarenMFQualityAdvise2::NotifyQualityEvent(
ICarenMFMediaEvent^ Param_Evento,
OutParam CA_MF_QUALITY_ADVISE_FLAGS% Param_Out_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaEvent* vi_pMediaEvent = Nulo;
	DWORD vi_OutQualityFlags = 0;

	//Recupera o ponteiro para o evento.
	CarenGetPointerFromICarenSafe(Param_Evento, vi_pMediaEvent);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->NotifyQualityEvent(vi_pMediaEvent, &vi_OutQualityFlags);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte o valor e define no parametro de saida.
	Param_Out_Flags = static_cast<CA_MF_QUALITY_ADVISE_FLAGS>(vi_OutQualityFlags);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenMFQualityAdvise)


/// <summary>
/// Dropa as amostras em um intervalo de tempo especificado.
/// </summary>
/// <param name="Param_NsAmountToDrop">Quantidade de tempo para dropar, em unidades de 100 nanossegundos. Esse valor é sempre absoluto. Se o método for chamado várias vezes, não adicione os horários das chamadas anteriores.</param>
CarenResult CarenMFQualityAdvise2::DropTime(UInt64 Param_NsAmountToDrop)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DropTime(Param_NsAmountToDrop);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o modo de drop atual.
/// </summary>
/// <param name="Param_Out_DropMode">Recebe o modo de drop, especificado como membro da enumeração CA_MF_QUALITY_DROP_MODE.</param>
CarenResult CarenMFQualityAdvise2::GetDropMode([Out] CA_MF_QUALITY_DROP_MODE% Param_Out_DropMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MF_QUALITY_DROP_MODE vi_OutQualityDrop = MF_QUALITY_DROP_MODE::MF_DROP_MODE_NONE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDropMode(&vi_OutQualityDrop);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_DropMode = static_cast<CA_MF_QUALITY_DROP_MODE>(vi_OutQualityDrop);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o nível de qualidade atual.
/// </summary>
/// <param name="Param_Out_NivelQualidade">Recebe o nível de qualidade, especificado como membro da enumeração CA_MF_QUALITY_LEVEL.</param>
CarenResult CarenMFQualityAdvise2::GetQualityLevel([Out] CA_MF_QUALITY_LEVEL% Param_Out_NivelQualidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	MF_QUALITY_LEVEL vi_OutQualityLevel = MF_QUALITY_LEVEL::MF_QUALITY_NORMAL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetQualityLevel(&vi_OutQualityLevel);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_NivelQualidade = static_cast<CA_MF_QUALITY_LEVEL>(vi_OutQualityLevel);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o modo de drop. No modo de drop, um componente dropa amostras, mais ou menos agressivamente dependendo do nível do modo de drop.
/// Se esse método for chamado a uma fonte de mídia, a fonte de mídia pode alternar entre saídas diluídas e não diluídas. Se isso ocorrer, os fluxos afetados enviarão um evento MEStreamThinMode para indicar a transição. A operação é assíncroda; após o retorno do SetDropMode, você pode receber amostras que estavam na fila antes da transição. O evento MEStreamThinMode marca o ponto exato no fluxo onde a transição ocorre.
/// </summary>
/// <param name="Param_DropMode">Modo de queda solicitado, especificado como membro da enumeração CA_MF_QUALITY_DROP_MODE.</param>
CarenResult CarenMFQualityAdvise2::SetDropMode(CA_MF_QUALITY_DROP_MODE Param_DropMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDropMode(static_cast<MF_QUALITY_DROP_MODE>(Param_DropMode));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o nível de qualidade. O nível de qualidade determina como o componente consome ou produz amostras.
/// </summary>
/// <param name="Param_NivelQualidade">Nível de qualidade solicitado, especificado como membro da enumeração CA_MF_QUALITY_LEVEL.</param>
CarenResult CarenMFQualityAdvise2::SetQualityLevel(CA_MF_QUALITY_LEVEL Param_NivelQualidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetQualityLevel(static_cast<MF_QUALITY_LEVEL>(Param_NivelQualidade));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}