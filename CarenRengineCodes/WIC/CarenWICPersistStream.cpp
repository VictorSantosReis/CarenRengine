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
#include "CarenWICPersistStream.h"

//Destruidor.
CarenWICPersistStream::~CarenWICPersistStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICPersistStream::CarenWICPersistStream()
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
CarenResult CarenWICPersistStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICPersistStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICPersistStream*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICPersistStream**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICPersistStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICPersistStream*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICPersistStream**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICPersistStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICPersistStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICPersistStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICPersistStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICPersistStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICPersistStream::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICPersistStream::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICPersistStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICPersistStream();
}



// Métodos da interface proprietária(ICarenWICPersistStream)


/// <summary>
/// Carrega dados de um fluxo de entrada usando os parâmetros determinados. 
/// NULO pode ser passado para (Param_GuidPreferredVendor) para indicar nenhuma preferência.
/// </summary>
/// <param name="Param_Stream">O fluxo de entrada.</param>
/// <param name="Param_GuidPreferredVendor">O GUID do fornecedor preferido.</param>
/// <param name="Param_PersistOptions">O WICPersistOptions usado para carregar o fluxo.</param>
CarenResult CarenWICPersistStream::LoadEx(
ICarenStream^ Param_Stream,
String^ Param_GuidPreferredVendor,
CA_WICPersistOptions Param_PersistOptions)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IStream* vi_Fluxo = Nulo;
	GUID vi_guidVendor = GUID_NULL;

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Stream, vi_Fluxo);

	//Converte a string para o guid.
	vi_guidVendor = Util.CreateGuidFromString(Param_GuidPreferredVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadEx(vi_Fluxo, &vi_guidVendor, static_cast<DWORD>(Param_PersistOptions));

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
/// Salva o ICaremWICPersistStream para o ICarenStream de entrada dado usando os parâmetros determinados.
/// </summary>
/// <param name="Param_Stream">O fluxo para salvar.</param>
/// <param name="Param_PersistOptions">As WICPersistOptions a serem usadas ao salvar.</param>
/// <param name="Param_ClearDirty">Indica se o valor "dirty" será limpo de todos os metadados após a salvação.</param>
CarenResult CarenWICPersistStream::SaveEx(
ICarenStream^ Param_Stream,
CA_WICPersistOptions Param_PersistOptions,
Boolean Param_ClearDirty)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_Fluxo = Nulo;
	BOOL vi_ClearDity = Param_ClearDirty ? TRUE : FALSE;

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Stream, vi_Fluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SaveEx(vi_Fluxo, static_cast<DWORD>(Param_PersistOptions), vi_ClearDity);

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




// Métodos da interface (ICarenPersistStream)


/// <summary>
/// Recupera o tamanho do fluxo necessário para salvar o objeto.
/// Este método retorna o tamanho necessário para salvar um objeto. Você pode chamar este método para determinar o tamanho e definir os 
/// buffers necessários antes de chamar o método ICarenPersistStream::Save.
/// </summary>
/// <param name="Param_Out_Size">Retorna o tamanho em bytes do fluxo necessário para salvar este objeto, em bytes.</param>
/// <returns></returns>
CarenResult CarenWICPersistStream::GetSizeMax(UInt64% Param_Out_Size)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ULARGE_INTEGER vi_OutSize = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSizeMax(&vi_OutSize);

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

	//Define no parametro de saida.
	Param_Out_Size = vi_OutSize.QuadPart;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se um objeto mudou desde que foi salvo pela última vez em seu fluxo.
/// Este método retorna SS_OK para indicar que o objeto foi alterado. Caso contrário, ele retorna SS_FALSE.
/// Você deve tratar quaisquer códigos de retorno de erro como uma indicação de que o objeto foi alterado. A menos que este método retorne 
/// explicitamente SS_FALSE, assuma que o objeto deve ser salvo.
/// </summary>
/// <returns></returns>
CarenResult CarenWICPersistStream::IsDirty()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsDirty();

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
/// Inicializa um objeto do fluxo onde ele foi salvo anteriormente.
/// </summary>
/// <param name="Param_Fluxo">Um ICarenStream para o fluxo a partir do qual o objeto deve ser carregado.</param>
/// <returns></returns>
CarenResult CarenWICPersistStream::Load(ICarenStream^ Param_Fluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_Fluxo = Nulo;

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Fluxo, vi_Fluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Load(vi_Fluxo);

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
/// Salva um objeto para o fluxo especificado.
/// </summary>
/// <param name="Param_Fluxo">Um ICarenStream para o fluxo no qual o objeto deve ser salvo.</param>
/// <param name="Param_ClearDirty">Indica se o sinalizador sujo deve ser limpo após a conclusão do salvamento.Se TRUE, o sinalizador deve ser apagado. Se FALSE, o 
/// sinalizador deve ser deixado inalterado.</param>
/// <returns></returns>
CarenResult CarenWICPersistStream::Save(ICarenStream^ Param_Fluxo, Boolean Param_ClearDirty)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_Fluxo = Nulo;

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Fluxo, vi_Fluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Save(vi_Fluxo, Param_ClearDirty ? TRUE : FALSE);

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




// Métodos da interface (ICarenPersist)


/// <summary>
/// Recupera o identificador de classe (CLSID) do objeto.
/// </summary>
/// <param name="Param_Out_ClassID">Retorna o CLSID do objeto atual.</param>
/// <returns></returns>
CarenResult CarenWICPersistStream::GetClassID([Out] String^% Param_Out_ClassID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_OutClassId = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetClassID(&vi_OutClassId);

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
	Param_Out_ClassID = Util.ConverterGuidToString(vi_OutClassId);

Done:;
	//Retorna o resultado.
	return Resultado;
}