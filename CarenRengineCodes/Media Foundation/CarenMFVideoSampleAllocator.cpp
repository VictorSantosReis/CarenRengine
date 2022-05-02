﻿/*
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
#include "CarenMFVideoSampleAllocator.h"


//Destruidor.
CarenMFVideoSampleAllocator::~CarenMFVideoSampleAllocator()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFVideoSampleAllocator::CarenMFVideoSampleAllocator()
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
CarenResult CarenMFVideoSampleAllocator::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFVideoSampleAllocator::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFVideoSampleAllocator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFVideoSampleAllocator**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFVideoSampleAllocator::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFVideoSampleAllocator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFVideoSampleAllocator**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFVideoSampleAllocator::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFVideoSampleAllocator::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFVideoSampleAllocator::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFVideoSampleAllocator::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFVideoSampleAllocator::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFVideoSampleAllocator::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFVideoSampleAllocator::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFVideoSampleAllocator();
}





//
// Métodos da Interface Proprietaria.
//

/// <summary>
/// (AllocateSample) - Obtém uma amostra de vídeo do alocador.
/// </summary>
/// <param name="Param_Out_AmostraVideo">Recebe a interface que contém a amostra de vídeo. O chamado deve liberar a interface.</param>
CarenResult CarenMFVideoSampleAllocator::AllocateSample([Out] ICarenMFSample^% Param_Out_AmostraVideo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	ResultadoCOM Hr = E_FAIL;

	//Vairaveis utilizadas no método
	IMFSample *pAmosraRequisitada = NULL;

	//Chama o método para obter a amostra
	Hr = PonteiroTrabalho->AllocateSample(&pAmosraRequisitada);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada com a amostra
	Param_Out_AmostraVideo = gcnew CarenMFSample(false);

	//Chama o método para definir o ponteiro de trabalho.
	Param_Out_AmostraVideo->AdicionarPonteiro(pAmosraRequisitada);

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// (InitializeSampleAllocator) - Inicializa o alocador informando a quantidade de amostras para alocar e o tipo de mídia
/// para cada amostra.				
/// </summary>
/// <param name="Param_CountAmostra">A quantidade de amostas para alocar.</param>
/// <param name="Param_TipoAmostraVideo">Uma interface que contém o Tipo de mídia de vídeo que será alocada.</param>
CarenResult CarenMFVideoSampleAllocator::InitializeSampleAllocator(UInt32 Param_CountAmostra, ICarenMFMediaType^ Param_TipoAmostraVideo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFMediaType* pTipoMidia = NULL;

	//Chama o método que vai recuperar o tipo de midia
	Resultado = Param_TipoAmostraVideo->RecuperarPonteiro((LPVOID*)&pTipoMidia);

	//Verifica se não houve erro
	if(Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método que vai alocar a quantidade de amostras definidas com o tipo informado.
	Hr = PonteiroTrabalho->InitializeSampleAllocator(Param_CountAmostra, pTipoMidia);

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
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetDirectXManager) - Especifica o dispositivo do gerenciamento do Direct3D para o coletor de mídia de vídeo utilizar.
/// O coletor de mídia usa o Gerenciador de dispositivos Direct3D para obter um ponteiro para o dispositivo Direct3D, que ele usa para alocar superfícies Direct3D. O Gerenciador de dispositivos 
/// habilita vários objetos no pipeline (como um processador de vídeo e um decodificador de vídeo) para compartilhar o mesmo dispositivo Direct3D.
/// </summary>
/// <param name="Param_Interface">A interface que o gerenciador do Direct3D a ser usado.</param>
CarenResult CarenMFVideoSampleAllocator::SetDirectXManager(ICaren^ Param_Interface)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IUnknown* pDirectManager = NULL;

	//Chama o método para recuperar o ponteiro para o gerenciador do Direct3D.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)&pDirectManager);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para definir o gerenciador do Direct3D
	Hr = PonteiroTrabalho->SetDirectXManager(pDirectManager);

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
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// (UninitializeSampleAllocator) - Libera Todas as amostras de vídeo que tenham sido alocadas.
/// </summary>
CarenResult CarenMFVideoSampleAllocator::UninitializeSampleAllocator()
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método que vai descarregar os dados.
	Hr = PonteiroTrabalho->UninitializeSampleAllocator();

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
	//retorna o resultado
	return Resultado;
}
