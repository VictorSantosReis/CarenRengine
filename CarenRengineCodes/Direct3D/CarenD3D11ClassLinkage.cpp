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


#include "..\pch.h"
#include "CarenD3D11ClassLinkage.h"

//Destruidor.
CarenD3D11ClassLinkage::~CarenD3D11ClassLinkage()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
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
CarenResult CarenD3D11ClassLinkage::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
CarenResult CarenD3D11ClassLinkage::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID3D11ClassLinkage*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD3D11ClassLinkage::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID3D11ClassLinkage*>(Param_PonteiroNativo);

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
CarenResult CarenD3D11ClassLinkage::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD3D11ClassLinkage::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD3D11ClassLinkage::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD3D11ClassLinkage::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11ClassLinkage::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11ClassLinkage::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11ClassLinkage::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenD3D11ClassLinkage::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD3D11ClassLinkage::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD3D11ClassLinkage();
}

//
//Métodos da interface Proprietaria
//



/// <summary>
/// (CreateClassInstance) - Inicializa um objeto de instância da classe que representa uma instância da classe HLSL.
/// </summary>
/// <param name="Para_NomeTipoClasse">O nome de tipo de uma classe para inicializar.</param>
/// <param name="Param_DeslocamentoBufferConstante">Identifica o (Buffer Constante) que contém os dados de classe.</param>
/// <param name="Param_DeslocamentoVetorConstante">O deslocamento de quatro componentes vetor desde o início do buffer constante onde os dados de classe vão começar. Consequentemente, isto não é um deslocamento de byte.</param>
/// <param name="Param_DeslocamentoTextura">O slot de textura para a primeira textura; pode haver múltiplas texturas seguindo o deslocamento.</param>
/// <param name="Param_DeslocamentoAmostrador">O slot de amostra para o primeiro sampler; pode haver vários amostradores seguindo o deslocamento.</param>
/// <param name="Param_Out_ClasseInstance">Recebe um ponteiro para a interface (ICarenD3D11ClassInstance) para ser inicializada. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenD3D11ClassLinkage::CriarInstanciaClasseHLSL(
	String^ Para_NomeTipoClasse,
	UInt32 Param_DeslocamentoBufferConstante,
	UInt32 Param_DeslocamentoVetorConstante,
	UInt32 Param_DeslocamentoTextura,
	UInt32 Param_DeslocamentoAmostrador,
	ICaren^ Param_Out_ClasseInstance)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCSTR pNomeTipoClasse = NULL;
	ID3D11ClassInstance* pInstanciaClasse = NULL;

	//Converte a string Gerenciada
	pNomeTipoClasse = Util.ConverterStringToChar(Para_NomeTipoClasse);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateClassInstance(pNomeTipoClasse, Param_DeslocamentoBufferConstante, Param_DeslocamentoVetorConstante, Param_DeslocamentoTextura, Param_DeslocamentoAmostrador, &pInstanciaClasse);

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

	//Define o ponteiro para a interface.
	Param_Out_ClasseInstance->AdicionarPonteiro(pInstanciaClasse);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetClassInstance) - Obtém o objeto de instância da classe que representa a classe especificada de HLSL.
/// </summary>
/// <param name="Param_NomeInstanciaClasse">O nome de uma classe para o qual deseja obter a instância de classe.</param>
/// <param name="Param_IndiceInstancia">O índice da instância da classe.</param>
/// <param name="Param_Out_InstanceClasse">Recebe um ponteiro para a interface (ICarenD3D11ClassInstance) para ser inicializada. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenD3D11ClassLinkage::ObterInstanciaClasse(
	String^ Param_NomeInstanciaClasse, 
	UInt32 Param_IndiceInstancia, 
	ICaren^ Param_Out_InstanceClasse) 
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCSTR pNomeInstanciaClasse = NULL;
	ID3D11ClassInstance* pInstanciaClasse = NULL;

	//Obtém o nome da instancia da classe
	pNomeInstanciaClasse = Util.ConverterStringToChar(Param_NomeInstanciaClasse);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetClassInstance(pNomeInstanciaClasse, Param_IndiceInstancia, &pInstanciaClasse);

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

	//Define o ponteiro para a interface.
	Param_Out_InstanceClasse->AdicionarPonteiro(pInstanciaClasse);

Done:;
	//Exclui a memoria da String
	delete pNomeInstanciaClasse;

	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface proprietaria(ICarenD3D11DeviceChild)

/// <summary>
/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
/// </summary>
/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenD3D11ClassLinkage::ObterDispositivo(ICaren^ Param_Out_DispositivoD3D11)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Device* pDevice = NULL;

	//Chama o método
	PonteiroTrabalho->GetDevice(&pDevice);

	//Verifica se a operação obteve sucesso.
	if (ObjetoValido(pDevice))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o código HRESULT.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método.
		goto Done;
	}

	//Define o ponteiro do dispositivo.
	Param_Out_DispositivoD3D11->AdicionarPonteiro(pDevice);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (ObterDadosPrivados) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
CarenResult CarenD3D11ClassLinkage::ObterDadosPrivados(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_BufferDados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	LPVOID pDados = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Chama o método
	Hr = PonteiroTrabalho->GetPrivateData(GuidDados, &OutLarguraDados, &pDados);

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

	//Cria a interface que vai conter o ponteiro de dados.
	Param_Out_BufferDados = gcnew CarenBuffer();

	//Define o ponteiro de dados na interface de buffer.
	Param_Out_BufferDados->CriarBuffer(IntPtr(pDados), false, OutLarguraDados, OutLarguraDados);

	//Define o tamanho real dos dados retornados.
	Param_Out_TamanhoBufferSaida = OutLarguraDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
CarenResult CarenD3D11ClassLinkage::DefinirDadosPrivados(
	String^ Param_Guid,

	UInt32 Param_TamanhoBuffer, ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	PBYTE pDados = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Obtém o ponteiro para os dados.
	Resultado = Param_Buffer->ObterPonteiroInterno(PonteiroDados);

	//Verifica se é valido
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pDados = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método que vai definir os dados.
	Hr = PonteiroTrabalho->SetPrivateData(GuidDados, Param_TamanhoBuffer, pDados);

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
/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
CarenResult CarenD3D11ClassLinkage::DefinirInterfaceDadosPrivados(
	String^ Param_Guid, ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidAssociado = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidAssociado = Util.CreateGuidFromString(Param_Guid);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)pInterface);

	//Verifica se a interface não é invalida
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface é invalida

		//Sai do método
		goto Done;
	}

	//Chama o método para definir a interface.
	Hr = PonteiroTrabalho->SetPrivateDataInterface(GuidAssociado, pInterface);

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