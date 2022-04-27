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
#include "CarenMFAudioStreamVolume.h"


//Destruidor.
CarenMFAudioStreamVolume::~CarenMFAudioStreamVolume()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFAudioStreamVolume::CarenMFAudioStreamVolume()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFAudioStreamVolume::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAudioStreamVolume::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAudioStreamVolume*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAudioStreamVolume**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAudioStreamVolume::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAudioStreamVolume*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAudioStreamVolume**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAudioStreamVolume::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAudioStreamVolume::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFAudioStreamVolume::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFAudioStreamVolume::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFAudioStreamVolume::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFAudioStreamVolume::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFAudioStreamVolume::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFAudioStreamVolume::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFAudioStreamVolume();
}





//Métodos da interface ICarenMFAudioStreamVolume


/// <summary>
/// (GetAllVolumes) - Recupera os níveis de volume para todos os canais no fluxo de áudio.
/// </summary>
/// <param name="Param_TamanhoMatriz">O Tamanho da matriz no parmêtro (Param_Out_MatrizVolumes). Esse valor representa a quantidade de canais de áudio.
/// Para obter esse valor, chame o método (GetChannelCount).</param>
/// <param name="Param_Out_MatrizVolumes">Recebe a matriz com o nível de volume de para cada canal no fluxo.</param>
CarenResult CarenMFAudioStreamVolume::GetAllVolumes(UInt32 Param_TamanhoMatriz, [Out] cli::array<float>^% Param_Out_MatrizVolumes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<float> ArrayVolumes;

	//Define o tamanho do array
	ArrayVolumes.reserve(Param_TamanhoMatriz);

	//Chama o método que vai receber o array.
	Hr = PonteiroTrabalho->GetAllVolumes(Param_TamanhoMatriz, ArrayVolumes.data());

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

	//Define os dados no parametro de saida
	for (UINT32 i = 0; i < Param_TamanhoMatriz; i++)
	{
		//Define o valor no parametro de saida.
		Param_Out_MatrizVolumes[i] = ArrayVolumes[i];
	}

	//Limpa o vetor
	ArrayVolumes.clear();
	ArrayVolumes.shrink_to_fit();

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetChannelCount) - Recupera o número de canais no fluxo de áudio.
/// </summary>
/// <param name="Param_Out_QuantidadeCanais">Recebe o número de canais no fluxo de áudio.</param>
CarenResult CarenMFAudioStreamVolume::GetChannelCount([Out] UInt32% Param_Out_QuantidadeCanais) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 QuantCanais = 0;

	//Chama o método para obter a quantidade de canais.
	Hr = PonteiroTrabalho->GetChannelCount(&QuantCanais);

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

	//Define a quantidade de canais no paremetro de saida
	Param_Out_QuantidadeCanais = QuantCanais;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetChannelVolume) - Recupera o nível de volume para um canal específico no fluxo de áudio.
/// </summary>
/// <param name="Param_IdCanal">Índice baseado em zero do canal de áudio. Para obter o número de canais, chame o método (GetChannelCount).</param>
/// <param name="Param_Out_NivelVolume">Recebe o nível de volume no canal especificado.</param>
CarenResult CarenMFAudioStreamVolume::GetChannelVolume(UInt32 Param_IdCanal, [Out] float% Param_Out_NivelVolume) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	float NivelVolumeCanal = 0.0;

	//Chama o método para obter o nivel de volume no canal.
	Hr = PonteiroTrabalho->GetChannelVolume(Param_IdCanal, &NivelVolumeCanal);

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

	//Define o nivel de volume no parametro de saida
	Param_Out_NivelVolume = NivelVolumeCanal;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetAllVolumes) - Define os níveis de volume individual para todos os canais no fluxo de áudio.
/// </summary>
/// <param name="Param_TamanhoMatriz">O Tamanho da matriz no parmêtro (Param_NiveisVolume). Esse valor representa a quantidade de canais de áudio.
/// Para obter esse valor, chame o método (GetChannelCount).</param>
/// <param name="Param_NiveisVolume"> A matriz sspecifica os níveis de volume para todos os canais. Antes de chamar o método, defina cada elemento da matriz para o
/// nível de volume desejado para o canal.</param>
CarenResult CarenMFAudioStreamVolume::SetAllVolumes(UInt32 Param_TamanhoMatriz, cli::array<float>^ Param_NiveisVolume) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	std::vector<float> ArrayVolumes;

	//Define o tamanho do array
	ArrayVolumes.reserve(Param_TamanhoMatriz);

	//Copia os niveis de volume
	for (UINT32 i = 0; i < Param_TamanhoMatriz; i++)
	{
		//Define o valor no parametro de saida.
		Param_NiveisVolume[i] = ArrayVolumes[i];
	}

	//Chama o método para definir todos os volumes
	Hr = PonteiroTrabalho->SetAllVolumes(Param_TamanhoMatriz, ArrayVolumes.data());

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
/// (SetChannelVolume) - Define o nível de volume para um canal específico no fluxo de áudio.
/// </summary>
/// <param name="Param_IdCanal">Índice baseado em zero do canal de áudio. Para obter o número de canais, chame o método (GetChannelCount).</param>
/// <param name="Param_NivelVolume">O nível de volume a ser definido no canal especificado.</param>
CarenResult CarenMFAudioStreamVolume::SetChannelVolume(UInt32 Param_IdCanal, float Param_NivelVolume) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir o volume no canal especificado
	Hr = PonteiroTrabalho->SetChannelVolume(Param_IdCanal, Param_NivelVolume);

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