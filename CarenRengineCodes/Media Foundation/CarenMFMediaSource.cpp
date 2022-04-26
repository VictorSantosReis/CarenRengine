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
#include "CarenMFMediaSource.h"


//Destruidor.
CarenMFMediaSource::~CarenMFMediaSource()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Construtores
CarenMFMediaSource::CarenMFMediaSource()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenMFMediaSource::CarenMFMediaSource(ICarenMFCollection^ Param_SourceCollection)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFCollection* vi_pCollectionSource = Nulo;
	IMFMediaSource* vi_pOutMediaSource = Nulo;

	//Verifica se a interface de atributos não é invalida.
	if (!ObjetoGerenciadoValido(Param_SourceCollection))
		throw gcnew NullReferenceException("A interface (ICarenMFCollection) no parametro (Param_SourceCollection) não pode ser NULO!");

	//Tenta recuperar o ponteiro para a interface de atributos.
	CarenResult Resultado = RecuperarPonteiroCaren(Param_SourceCollection, &vi_pCollectionSource);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		throw gcnew Exception("Não foi possivel recuperar o ponteiro para a interface de coleção no parametro (Param_SourceCollection).");

	//Chama o método para criar a interface.
	Hr = MFCreateAggregateSource(vi_pCollectionSource, &vi_pOutMediaSource);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutMediaSource;
}
CarenMFMediaSource::CarenMFMediaSource(ICarenMFAttributes^ Param_Atributos)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFAttributes* vi_pAtributos = Nulo;
	IMFMediaSource* vi_pOutMediaSource = Nulo;

	//Verifica se a interface de atributos não é invalida.
	if (!ObjetoGerenciadoValido(Param_Atributos))
		throw gcnew NullReferenceException("A interface (ICarenMFAttributes) no parametro (Param_Atributos) não pode ser NULO!");

	//Tenta recuperar o ponteiro para a interface de atributos.
	CarenResult Resultado = RecuperarPonteiroCaren(Param_Atributos, &vi_pAtributos);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		throw gcnew Exception("Não foi possivel recuperar o ponteiro para a interface de atributos no parametro (Param_Atributos).");

	//Chama o método para criar a interface.
	Hr = MFCreateDeviceSource(vi_pAtributos, &vi_pOutMediaSource);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutMediaSource;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFMediaSource::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaSource::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaSource*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaSource::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaSource*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaSource::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaSource::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaSource::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaSource::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaSource::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaSource::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaSource::LiberarReferencia()
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
void CarenMFMediaSource::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaSource();
}





// Métodos da interface proprietaria (ICarenMFMediaSource)



/// <summary>
/// (CreatePresentationDescriptor) - Recupera uma cópia do descritor de apresentação da fonte de mídia. Os aplicativos usam o descritor de apresentação para selecionar fluxos e obter informações sobre o conteúdo de origem.
/// </summary>
/// <param name="Param_Out_DescritorApresentação">Recebe a interface para o descritor de apresentação.</param>
CarenResult CarenMFMediaSource::CreatePresentationDescriptor([Out] ICarenMFPresentationDescriptor^% Param_Out_DescritorApresentação)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFPresentationDescriptor* vi_pOutPresentationDesc = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePresentationDescriptor(&vi_pOutPresentationDesc);

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

	//Cria a interface que vai ser retornada.
	Param_Out_DescritorApresentação = gcnew CarenMFPresentationDescriptor();

	//Define o ponteiro na interface a ser retornada.
	CarenSetPointerToICarenSafe(vi_pOutPresentationDesc, Param_Out_DescritorApresentação, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetCharacteristics) - Recupera as características da fonte de mídia.
/// </summary>
/// <param name="Param_Out_Caracteristicas">Recebe um OR de bit a bit de zero ou mais sinalizadores da enumeração (CA_MFMEDIASOURCE_CHARACTERISTICS).</param>
CarenResult CarenMFMediaSource::GetCharacteristics([Out] Enumeracoes::CA_MFMEDIASOURCE_CHARACTERISTICS% Param_Out_Caracteristicas)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutCharacteristicsSource = 0;

	//Chama o método para obter as caracteriscticas.
	Hr = PonteiroTrabalho->GetCharacteristics(&vi_OutCharacteristicsSource);

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

	//Define as caracteristicas no parametro de saida
	Param_Out_Caracteristicas = static_cast<CA_MFMEDIASOURCE_CHARACTERISTICS>(vi_OutCharacteristicsSource);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Start) - Inicia, procura ou reinicia a fonte de mídia especificando onde iniciar a reprodução.
/// </summary>
/// <param name="Param_DescritorApresentação">A interface de ICarenMFPresentationDescriptor de descritor de apresentação da fonte de mídia. Para obter o descritor de apresentação, chamade o método (ICarenMFPresentationDescriptor::CreatePresentationDescriptor). 
/// Você pode modificar o descritor de apresentação antes de chamar Start, para selecionar ou desmarcar fluxos ou alterar os tipos de mídia.</param>
/// <param name="Param_GuidTimeFormato">Um GUID que especifica o formato de hora. O formato de hora define as unidades para o parâmetro Param_PosiçãoInicio. Se o valor é NULL, o formato é definido como unidades de 100 nanossegundos. Algumas fontes de 
/// mídia podem oferecer suporte o formato de hora adicional. Este parâmetro pode ser nulo. Se o valor for nulo, é equivalente a GUID_NULL.</param>
/// <param name="Param_PosiçãoInicio">Especifica onde iniciar a reprodução. As unidades deste parâmetro são indicadas pelo formato tempo dado em Param_GuidTimeFormato. Se o formato de hora é GUID_NULL, o tipo de variante deve ser VT_I8 ou VT_EMPTY. Use VT_I8 
/// para especificar uma nova posição inicial, em unidades de 100 nanossegundos. Use VT_EMPTY para começar a partir da posição atual. Outros formatos de hora podem usar outros tipos CA_PROPVARIANT.</param>
CarenResult CarenMFMediaSource::Start(ICarenMFPresentationDescriptor^ Param_DescritorApresentação, String^ Param_GuidTimeFormato, Estruturas::CA_PROPVARIANT^ Param_PosiçãoInicio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFPresentationDescriptor* vi_pPresentationDesc = Nulo;
	GUID vi_GuidTimeFormat = GUID_NULL;
	PROPVARIANT* vi_pPropvar = Nulo;

	//Recupera o ponteiro para o descritor de apresentação.
	CarenGetPointerFromICarenSafe(Param_DescritorApresentação, vi_pPresentationDesc);

	//Converte a string para GUID se informado.
	if (StringObjetoValido(Param_GuidTimeFormato))
		CarenCreateGuidFromStringSafe(Param_GuidTimeFormato, vi_GuidTimeFormat);
	
	//Converte a PROPVARIANT gerenciada para a nativa.
	CarenConvertPropvariantToNativeSafe(Param_PosiçãoInicio, vi_pPropvar);

	//Chama o método para poder iniciar.
	Hr = PonteiroTrabalho->Start(
		vi_pPresentationDesc,
		&vi_GuidTimeFormat,
		const_cast<PROPVARIANT*>(vi_pPropvar));

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
	DeletarPropVariantSafe(&vi_pPropvar);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Pause) - Pausa todos os fluxos ativos na fonte de mídia.
/// </summary>
CarenResult CarenMFMediaSource::Pause()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para pausar
	Hr = PonteiroTrabalho->Pause();

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
/// (Stop) - Interrompe todos os fluxos ativos na fonte de mídia.
/// </summary>
CarenResult CarenMFMediaSource::Stop()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para desligado.
	Hr = PonteiroTrabalho->Shutdown();

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
/// (Shutdown) - Desliga a fonte de mídia e libera os recursos que ela está usando.
/// </summary>
CarenResult CarenMFMediaSource::Shutdown()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para desligado.
	Hr = PonteiroTrabalho->Shutdown();

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





// Métodos da interface (ICarenMFMediaEventGenerator)


/// <summary>
/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
/// dependerá do valor de Param_Flags.
/// </summary>
/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaSource::GetEvent(CA_MF_GET_FLAGS_EVENT Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaEvent* vi_pOutMediaEvent = NULL;

	//Chama o método para obter o evento.
	Hr = PonteiroTrabalho->GetEvent(static_cast<DWORD>(Param_Flags), &vi_pOutMediaEvent);

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

	//Cria a interface que vai ser retornada no parametro de saida.
	Param_Out_MidiaEvent = gcnew CarenMFMediaEvent();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaEvent, Param_Out_MidiaEvent, true);

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
CarenResult CarenMFMediaSource::BeginGetEvent(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncCallback* vi_pCallback = NULL;
	IUnknown* vi_pDadosObjeto = NULL; //Pode ser Nulo.

	//Recupera o ponteiro para a interface de Callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Verifica se forneceu uma interface de dados e recupera o ponteiro
	if (ObjetoGerenciadoValido(Param_ObjetoDesconhecido))
		CarenGetPointerFromICarenSafe(Param_ObjetoDesconhecido, vi_pDadosObjeto);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginGetEvent(vi_pCallback, vi_pDadosObjeto);

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
CarenResult CarenMFMediaSource::EndGetEvent(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncResult* vi_pResultAsync = Nulo;
	IMFMediaEvent* vi_pOutMediaEvent = Nulo;

	//Recupera o ponteiro para a interface de resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_ResultAsync, vi_pResultAsync);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndGetEvent(vi_pResultAsync, &vi_pOutMediaEvent);

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

	//Cria a interface a ser retornada.
	Param_Out_MidiaEvent = gcnew CarenMFMediaEvent();

	//Define o ponteiro na interface a ser retornada.
	CarenSetPointerToICarenSafe(vi_pOutMediaEvent, Param_Out_MidiaEvent, true);

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
CarenResult CarenMFMediaSource::QueueEvent(
	Enumeracoes::CA_MediaEventType Param_TipoEvento,
	String^ Param_GuidExtendedType,
	Int32 Param_HResultCode,
	Estruturas::CA_PROPVARIANT^ Param_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MediaEventType vi_TypeEvent = static_cast<MediaEventType>(Param_TipoEvento);
	GUID vi_GuidExtendEvent = GUID_NULL; //Pode ser NULO.
	HRESULT vi_Hresult = static_cast<HRESULT>(Param_HResultCode);
	PROPVARIANT* vi_Propvar = Nulo; //Pode ser NULO.

	 //Converte a string para o GUID se fornecido.
	if (StringObjetoValido(Param_GuidExtendedType))
	{
		//Cria o GUID.
		CarenCreateGuidFromStringSafe(Param_GuidExtendedType, vi_GuidExtendEvent);
	}

	//Verifica se forneceu uma estrutura PROPVARIANT com o valor do evento.
	if (ObjetoGerenciadoValido(Param_Dados))
		CarenConvertPropvariantToNativeSafe(Param_Dados, vi_Propvar); //Converte CA_PROPVARIANT

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueueEvent(
		vi_TypeEvent,
		vi_GuidExtendEvent,
		vi_Hresult,
		ObjetoValido(vi_Propvar) ? const_cast<PROPVARIANT*>(vi_Propvar) : Nulo
	);

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
	//Libera a memória utilizada pela propvariant.
	DeletarPropVariantSafe(&vi_Propvar);

	//Retorna o resultado da operação.
	return Resultado;
}