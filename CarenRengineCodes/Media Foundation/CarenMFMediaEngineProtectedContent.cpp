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
#include "CarenMFMediaEngineProtectedContent.h"

//Destruidor.
CarenMFMediaEngineProtectedContent::~CarenMFMediaEngineProtectedContent()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineProtectedContent::CarenMFMediaEngineProtectedContent()
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
CarenResult CarenMFMediaEngineProtectedContent::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineProtectedContent::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineProtectedContent*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineProtectedContent**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineProtectedContent::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineProtectedContent*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineProtectedContent**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineProtectedContent::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineProtectedContent::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaEngineProtectedContent::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaEngineProtectedContent::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaEngineProtectedContent::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineProtectedContent::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineProtectedContent::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaEngineProtectedContent::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineProtectedContent();
}



// Métodos da interface proprietária(ICarenMFMediaEngineProtectedContent)


/// <summary>
/// Obtém as proteções de conteúdo que devem ser aplicadas no modo frame-server.
/// </summary>
/// <param name="Param_Out_ProtecoesRequisitadasFlags">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS.</param>
CarenResult CarenMFMediaEngineProtectedContent::GetRequiredProtections([Out] CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS% Param_Out_ProtecoesRequisitadasFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutFlags = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRequiredProtections(&vi_OutFlags);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_ProtecoesRequisitadasFlags = static_cast<CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS>(vi_OutFlags);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o certificado do aplicativo.
/// </summary>
/// <param name="Param_BufferCertificado">Um buffer que contém o certificado no formato X.509, seguido pelo identificador de aplicativo 
/// assinado com uma assinatura SHA-256 usando a chave privada do certificado.</param>
/// <param name="Param_CountData">O tamanho do Buffer (Param_BufferCertificado), em bytes.</param>
CarenResult CarenMFMediaEngineProtectedContent::SetApplicationCertificate(ICarenBuffer^ Param_BufferCertificado, UInt32 Param_CountData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pBuffer = DefaultGenPointer;

	//Recupera o ponteiro para o buffer com o certificado.
	Param_BufferCertificado->GetInternalPointer(vi_pBuffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetApplicationCertificate(const_cast<PBYTE>(Util.ConverterIntPtrTo<PBYTE>(vi_pBuffer)), static_cast<DWORD>(Param_CountData));

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
/// Define o CPM (Content Protection Manager).
/// </summary>
/// <param name="Param_CPM">Um ponteiro para a interface ICarenContentProtectionManager, implementado pelo chamador.</param>
CarenResult CarenMFMediaEngineProtectedContent::SetContentProtectionManager(ICarenMFContentProtectionManager^ Param_CPM)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFContentProtectionManager* vi_pProtectionManager = Nulo;

	//Recupera o ponteiro para a interface de gerenciamento de proteção.
	CarenGetPointerFromICarenSafe(Param_CPM, vi_pProtectionManager);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetContentProtectionManager(vi_pProtectionManager);

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
/// Especifica a janela que deve receber proteções de link de saída.
/// </summary>
/// <param name="Param_WinHandle">A Handle para a janela a receber as proteções.</param>
CarenResult CarenMFMediaEngineProtectedContent::SetOPMWindow(IntPtr Param_WinHandle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOPMWindow(Util.ConverterIntPtrToHWND(Param_WinHandle));

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
/// Permite que o Media Engine acesse conteúdo protegido enquanto estiver no modo frame-server.
/// </summary>
/// <param name="Param_D3D11DeviceContext">Um ponteiro para o conteúdo do dispositivo Direct3D 11. O Media Engine consulta este ponteiro para a interface 
/// ICarenD3D11VideoContext.</param>
CarenResult CarenMFMediaEngineProtectedContent::ShareResources(ICaren^ Param_D3D11DeviceContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pDispositivoD3D11Context = Nulo;

	//Recupera o ponteiro para o dispositivo de contexto do direct3d 11
	CarenGetPointerFromICarenSafe(Param_D3D11DeviceContext, vi_pDispositivoD3D11Context);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ShareResources(vi_pDispositivoD3D11Context);

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
/// Copia um quadro de vídeo protegido para uma superfície DXGI.
/// </summary>
/// <param name="Param_SuperficeDestino">Um ponteiro para a interface da superfície de destino.</param>
/// <param name="Param_RetanguloOrigem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem</param>
/// <param name="Param_RetanguloDestino">Uma estrutura CA_RECT que especifica o retângulo de destino.</param>
/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
/// <param name="Param_Out_FlagsProtecaoConteudo">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS. 
/// Esses sinalizadores indicam quais proteções de conteúdo o aplicativo deve aplicar antes de apresentar a superfície.</param>
CarenResult CarenMFMediaEngineProtectedContent::TransferVideoFrame(
ICaren^ Param_SuperficeDestino,
CA_MFVideoNormalizedRect^ Param_RetanguloOrigem,
CA_RECT^ Param_RetanguloDestino,
CA_MFARGB^ Param_CorBorda,
[Out] CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS% Param_Out_FlagsProtecaoConteudo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* vi_pSuperficeDestino = Nulo;
	MFVideoNormalizedRect* vi_pRectOrigem = Nulo;
	PRECT vi_pRectDestino = Nulo;
	MFARGB* vi_pCorBorda = Nulo;
	DWORD vi_OutFlags = 0;

	//Recupera o ponteiro para a superfice de destino.
	CarenGetPointerFromICarenSafe(Param_SuperficeDestino, vi_pSuperficeDestino);

	//Converte as estruturas.
	vi_pRectOrigem = Util.ConverterMFVideoNormalizedRectManaged_ToUnamaged(Param_RetanguloOrigem);
	vi_pRectDestino = Util.ConverterRECTManagedToUnmanaged(Param_RetanguloDestino);
	vi_pCorBorda = Util.ConverterMFARGBManaged_ToUnamaged(Param_CorBorda);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->TransferVideoFrame(
		vi_pSuperficeDestino, 
		vi_pRectOrigem, 
		vi_pRectDestino, 
		vi_pCorBorda, 
		&vi_OutFlags
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define o valor dos flags no parametro de saida.
	Param_Out_FlagsProtecaoConteudo = static_cast<CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS>(vi_OutFlags);

Done:;
	//Libera a memória utilizada pelas estruturas
	DeletarEstruturaSafe(&vi_pRectOrigem);
	DeletarEstruturaSafe(&vi_pRectDestino);
	DeletarEstruturaSafe(&vi_pCorBorda);

	//Retorna o resultado.
	return Resultado;
}