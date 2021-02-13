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
#include "CarenMFStreamSink.h"


//Destruidor.
CarenMFStreamSink::~CarenMFStreamSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFStreamSink::CarenMFStreamSink()
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
CarenResult CarenMFStreamSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A operação falhou.
		

		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}


	//Retorna o resultado
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFStreamSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFStreamSink*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFStreamSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFStreamSink*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFStreamSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFStreamSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFStreamSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFStreamSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFStreamSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFStreamSink::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFStreamSink::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFStreamSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFStreamSink();
}


//
// Métodos da interface ICarenMFStreamSink
//



/// <summary>
/// Recupera o (Coletor de Mídia) que possui esse (Coletor de Fluxo).
/// </summary>
/// <param name="Param_Out_MidiaSink">Recebe a interface(ICarenMFMediaSink) do (Coletor de Mídia) responsável por esse (Coletor de Fluxo). O usuário deve criar a interface antes de chamar o método.</param>
CarenResult CarenMFStreamSink::GetMediaSink(ICaren^ Param_Out_MidiaSink)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::SS_OK, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas pelo método
	IMFMediaSink* pMediaSink = NULL;
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMediaSink(&pMediaSink);

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

	//Define o ponteiro no parametro
	Param_Out_MidiaSink->AdicionarPonteiro(pMediaSink);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Fornece uma amostra para o fluxo. O coletor de mídia processa o exemplo.
/// Esse método pode retornar (ER_MF_AMOSTRA_TIME_SPAN_INVALIDO) por vários motivos, dependendo da implementação do coletor de mídia:
/// 1 > Carimbos de hora negativos.
/// 2 > Carimbos de tempo que saltam para trás (dentro do mesmo fluxo).
/// 3 > Os carimbos de hora de um fluxo se afastaram muito dos registros de tempo em outro fluxo no mesmo coletor de mídia 
/// (por exemplo, um coletor de arquivamento que multiplexa os fluxos).
/// </summary>
/// <param name="Param_AmostraMidia">A amostra de mídia a ser processada.</param>
CarenResult CarenMFStreamSink::ProcessSample(ICarenMFSample^ Param_AmostraMidia)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas pelo método
	IMFSample *pSampleMidia = NULL;

	//Chama o método para recuperar o ponteiro para o Sample
	Resultado = Param_AmostraMidia->RecuperarPonteiro((LPVOID*)&pSampleMidia);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para processar a amostra
	Hr = PonteiroTrabalho->ProcessSample(pSampleMidia);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o identificador de fluxo para este coletor de fluxo.
/// </summary>
/// <param name="Param_Out_IdentificadorFluxo">Retorna o identificador deste fluxo.</param>
CarenResult CarenMFStreamSink::GetIdentifier([Out] UInt32% Param_Out_IdentificadorFluxo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	DWORD IdentificadorFluxo = 0;

	//Chama o método para recuperar o identificador deste fluxo.
	Hr = PonteiroTrabalho->GetIdentifier(&IdentificadorFluxo);

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

	//Define o resultado.
	Param_Out_IdentificadorFluxo = safe_cast<UInt32>(IdentificadorFluxo);

	//Deifine sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o manipulador de tipo de mídia para o coletor de fluxo. 
/// Você pode usar o manipulador de tipo de mídia para localizar quais
/// formatos o fluxo oferece suporte e para definir o tipo de mídia no fluxo.
/// </summary>
/// <param name="Param_Out_MidiaHandle">Recebe a interface que possui o (Manipulador de Mídia).</param>
CarenResult CarenMFStreamSink::GetMediaTypeHandler([Out] ICarenMFMediaTypeHandler^% Param_Out_MidiaHandle)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaTypeHandler *pHandlerMedia = NULL;
	ICarenMFMediaTypeHandler^ InterfaceHandlerMidia = nullptr;

	//Chama o método para obter o Gerenciador de tipos de mídia para este StreamSink
	Hr = PonteiroTrabalho->GetMediaTypeHandler(&pHandlerMedia);

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

	//Cria a interface que vai conter o ponteiro
	InterfaceHandlerMidia = gcnew CarenMFMediaTypeHandler(false);
	
	//Chama o método para definir o ponteiro
	InterfaceHandlerMidia->AdicionarPonteiro(pHandlerMedia);

	//Define a interface criada no parametro de retorno.
	Param_Out_MidiaHandle = InterfaceHandlerMidia;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Coloca um marcador no fluxo.
/// O método placemarker coloca um marcador no fluxo entre amostras. O CA_MFSTREAMSINK_MARKER_TYPE enumeração define o 
/// tipo de marcador e o tipo de informações associadas com o marcador.
/// </summary>
/// <param name="Param_Marcador">Especifica o tipo de marcador, como um membro da enumeração: CA_MFSTREAMSINK_MARKER_TYPE</param>
/// <param name="Param_ValorAdicional">Um valor que contém informações adicionais relacionadas ao marcador. Esse parâmetro pode ser (NULO).</param>
/// <param name="Param_DadosAnexoEvento">Valor que é anexado junto ao evento(MEStreamSinkMarker). Chame o método (GetValue) na interface 
/// de evento para obter esse valor. Esse parâmetro pode ser (NULO).</param>
CarenResult CarenMFStreamSink::PlaceMarker(Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE Param_Marcador, Estruturas::CA_PROPVARIANT^ Param_ValorAdicional, Estruturas::CA_PROPVARIANT^ Param_DadosAnexoEvento)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas no método
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_pPropValorAdd = Nulo;
	LPPROPVARIANT vi_pPropDadosAnexoEvento = Nulo;
	MFSTREAMSINK_MARKER_TYPE Marcador;

	//Verifica se define na variavel o marcador definido pelo usuario
	switch (Param_Marcador)
	{
	case CarenRengine::SDKBase::Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE::MFSTREAMSINK_MARKER_DEFAULT:
		//Define o marcador.
		Marcador = MFSTREAMSINK_MARKER_DEFAULT;
		break;

	case CarenRengine::SDKBase::Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE::MFSTREAMSINK_MARKER_ENDOFSEGMENT:
		//Define o marcador.
		Marcador = MFSTREAMSINK_MARKER_ENDOFSEGMENT;
		break;

	case CarenRengine::SDKBase::Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE::MFSTREAMSINK_MARKER_TICK:
		//Define o marcador.
		Marcador = MFSTREAMSINK_MARKER_TICK;
		break;

	case CarenRengine::SDKBase::Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE::MFSTREAMSINK_MARKER_EVENT:
		//Define o marcador.
		Marcador = MFSTREAMSINK_MARKER_EVENT;
		break;
	}

	//Verifica se vai definir valores adicionais ao marcador
	if(Param_ValorAdicional != nullptr)
	{
		//Vai adicionar valores adicionais ao marcador

		//Converte a PropVariant gerenciada para a nativa.
		vi_pPropValorAdd = static_cast<LPPROPVARIANT>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_ValorAdicional));

		//Verifica se não ocorreu um erro na conversão.
		if (!ObjetoValido(vi_pPropValorAdd))
		{
			//Falhou ao converter a propvariant.

			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

			//Sai do método
			Sair;
		}
	}
	else
	{
		//Não vai definir valores adicionais.
	}

	//Verifica se vai anexar um valor ao evento.
	if (Param_DadosAnexoEvento != nullptr)
	{
		//Vai anexa um valor ao evento.

		//Converte a PropVariant gerenciada para a nativa.
		vi_pPropDadosAnexoEvento = static_cast<LPPROPVARIANT>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_DadosAnexoEvento));

		//Verifica se não ocorreu um erro na conversão.
		if (!ObjetoValido(vi_pPropDadosAnexoEvento))
		{
			//Falhou ao converter a propvariant.

			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

			//Sai do método
			Sair;
		}
	}
	else
	{
		//Não vai enexar valores ao evento.


	}

	//Chama o método para definir o marcador.
	Hr = PonteiroTrabalho->PlaceMarker(
		Marcador, 
		Param_ValorAdicional != nullptr? vi_pPropValorAdd: NULL, 
		Param_DadosAnexoEvento != nullptr ? vi_pPropDadosAnexoEvento : NULL);

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

	//Deifine sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa as PropVariants
	DeletarPropVariantSafe(&vi_pPropValorAdd);
	DeletarPropVariantSafe(&vi_pPropDadosAnexoEvento);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Faz com que o coletor de fluxo para descartar todas as amostras que ele 
/// recebeu e ainda não processado.
/// </summary>
CarenResult CarenMFStreamSink::Flush()
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->Flush();

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

	//Deifine sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}





//
// Métodos da interface ICarenMFGeradorEventosMidia
//

/// <summary>
/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
/// dependerá do valor de Param_Flags.
/// </summary>
/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFStreamSink::GetEvent(CA_MF_GET_FLAGS_EVENT Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	ICarenMFMediaEvent^ InterfaceSolictada = nullptr;
	IMFMediaEvent* pMediaEvent = NULL;

	//Chama o método para obter o evento.
	Hr = PonteiroTrabalho->GetEvent((UInt32)Param_Flags, &pMediaEvent);

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

	//Cria a interface que vai conter o evento
	InterfaceSolictada = gcnew CarenMFMediaEvent();

	//Chama o método para deifinir o ponteiro
	InterfaceSolictada->AdicionarPonteiro(pMediaEvent);

	//Define a interface criada no parametro de saida.
	Param_Out_MidiaEvent = InterfaceSolictada;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
/// </summary>
/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
CarenResult CarenMFStreamSink::BeginGetEvent(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncCallback* pInterfaceCallback = NULL;
	IUnknown* pDadosObjeto = NULL;

	//Recupera o Callback
	Resultado = Param_Callback->RecuperarPonteiro((LPVOID*)& pInterfaceCallback);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Verifica se um objeto com dados foi especificado e obtém
	if (Param_ObjetoDesconhecido != nullptr)
	{
		//Obtém o objeto desconhecido.

		Resultado = Param_ObjetoDesconhecido->RecuperarPonteiro((LPVOID*)& pDadosObjeto);
	}

	//Verifica se não houve erro ao obter o objeto de dados.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para obter o proximo evento na fila.
	Hr = PonteiroTrabalho->BeginGetEvent(pInterfaceCallback, ObjetoValido(pDadosObjeto) ? pDadosObjeto : NULL);

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
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
/// </summary>
/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFStreamSink::EndGetEvent(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncResult* pResultAsync = NULL;
	IMFMediaEvent* pMediaEvent = NULL;
	ICarenMFMediaEvent^ InterfaceMidiaEvent = nullptr;

	//Recupera o resultado assincrono.
	Resultado = Param_ResultAsync->RecuperarPonteiro((LPVOID*)& pResultAsync);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para concluir a operação assincrona e obter o Media Event com as informações
	//do evento concluido.
	Hr = PonteiroTrabalho->EndGetEvent(pResultAsync, &pMediaEvent);

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

	//Cria a interface que vai conter o evento
	InterfaceMidiaEvent = gcnew CarenMFMediaEvent();

	//Chama o método para deifinir o ponteiro
	InterfaceMidiaEvent->AdicionarPonteiro(pMediaEvent);

	//Define a interface criada no parametro de saida.
	Param_Out_MidiaEvent = InterfaceMidiaEvent;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (QueueEvent) - Coloca um novo evento na fila do objeto.
/// </summary>
/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.GetType).</param>
/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.GetExtendedType) do evento.</param>
/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetStatus) do evento.</param>
/// <param name="Param_Dados">uma CA_PROPVARIANT que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetValue) do evento.</param>
CarenResult CarenMFStreamSink::InserirEventoFila(Enumeracoes::CA_MediaEventType Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PROPVARIANT^ Param_Dados) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	MediaEventType MTypeEvento = static_cast<MediaEventType>(Param_TipoEvento);
	LPPROPVARIANT vi_PropVar = Nulo;
	bool PropVarConverted = false;
	GUID GuidExtendedType = GUID_NULL;
	HRESULT ValorResultEvento = Param_HResultCode;

	//Cria o Guid se ele for valido.
	if (!String::IsNullOrEmpty(Param_GuidExtendedType))
	{
		//Cria o Guid.
		GuidExtendedType = Util.CreateGuidFromString(Param_GuidExtendedType);
	}

	//Verifica se forneceu dados para o evento.
	if (Param_Dados != nullptr)
	{
		//Converte a PropVariant gerenciada para a nativa.
		vi_PropVar = static_cast<LPPROPVARIANT>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Dados));

		//Verifica se não ocorreu um erro na conversão.
		if (!ObjetoValido(vi_PropVar))
		{
			//Falhou ao converter a propvariant.

			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

			//Sai do método
			Sair;
		}
	}

	//Chama o método para adicionar o evento na lista
	Hr = PonteiroTrabalho->QueueEvent(
		MTypeEvento, 
		GuidExtendedType, 
		ValorResultEvento,
		Param_Dados != nullptr ? vi_PropVar : NULL);

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
	//Libera a PropVariant
	DeletarPropVariantSafe(&vi_PropVar);

	//Retorna o resultado da operação.
	return Resultado;
}