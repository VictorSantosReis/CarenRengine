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
#include "CarenPropertyStore.h"


//Destruidor.
CarenPropertyStore::~CarenPropertyStore()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenPropertyStore::CarenPropertyStore()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenPropertyStore::CarenPropertyStore(String^ Param_RIID)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IPropertyStore* vi_pOutPropertyStore = Nulo;

	//Cria o guid da interface solicitada.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para criar a interface.
	Hr = PSCreateMemoryPropertyStore(vi_Riid, reinterpret_cast<void**>(&vi_pOutPropertyStore));

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define o ponteiro criado no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutPropertyStore;
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenPropertyStore::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenPropertyStore::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IPropertyStore*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IPropertyStore**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenPropertyStore::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IPropertyStore*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IPropertyStore**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenPropertyStore::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenPropertyStore::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenPropertyStore::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenPropertyStore::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenPropertyStore::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenPropertyStore::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenPropertyStore::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenPropertyStore();
}



//
//Métodos da interface ICarenPropertyStore
//


/// <summary>
/// (Commit) - Depois que uma alteração foi feita, esse método salva as alterações.
/// </summary>
CarenResult CarenPropertyStore::SalvarConfigurações()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para salvar as configurações
	Hr = PonteiroTrabalho->Commit();

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
/// (GetAt) - Obtém uma chave de propriedade da matriz de propriedades de um item.
/// </summary>
/// <param name="Param_Id">O índice da chave Propriedade na matriz de estruturas CA_PROPERTYKEY. Este é um índice baseado em zero.</param>
/// <param name="Param_Out_PropKey">TBD.</param>
CarenResult CarenPropertyStore::ObterKeyFromID(UInt32 Param_Id, [Out] Estruturas::CA_PROPERTYKEY^% Param_Out_PropKey)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PROPERTYKEY pKey = {};
	CA_PROPERTYKEY^ PropKeyEstrutura = nullptr;
	Utilidades Util;

	//Chama o método para obter a Key a parti do ID
	Hr = PonteiroTrabalho->GetAt(Param_Id, &pKey);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a estrutura que vai conter a Propkey
	PropKeyEstrutura = gcnew CA_PROPERTYKEY();

	//Define os valores.
	PropKeyEstrutura->PID = pKey.pid;
	PropKeyEstrutura->GUIDProp = pKey.fmtid != GUID_NULL ? Util.ConverterGuidToString(pKey.fmtid) : nullptr;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCount) - Esse método retorna uma contagem do número de propriedades anexadas ao arquivo.
/// </summary>
/// <param name="Param_Out_CountProps">Retorna a contagem de propriedades.</param>
CarenResult CarenPropertyStore::ObterQuantidade([Out] UInt32% Param_Out_CountProps)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD CountProps = 0;

	//Chama o método para obter a quantidade
	Hr = PonteiroTrabalho->GetCount(&CountProps);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_CountProps = CountProps;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetValue) - Este método recupera os dados para uma propriedade específica.
/// </summary>
/// <param name="Param_PropKey">TBD.</param>
/// <param name="Param_Out_Valor">Depois que o método retorna com êxito, este parâmetro retorna a estrutura CA_PROPVARIANT que contém dados sobre a propriedade.</param>
CarenResult CarenPropertyStore::GetValue(Estruturas::CA_PROPERTYKEY^% Param_PropKey, [Out] Estruturas::CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	PROPERTYKEY KeyProp = {};
	LPPROPVARIANT vi_OutPropVar = Nulo;

	//Define os dados na PROPERTYKEY.
	KeyProp.pid = Param_PropKey->PID;
	KeyProp.fmtid = String::IsNullOrEmpty(Param_PropKey->GUIDProp)? GUID_NULL: Util.CreateGuidFromString(Param_PropKey->GUIDProp);

	//Inicializa a PropVariant.
	IniciarPropVariant(&vi_OutPropVar);

	//Chama o método para obter os dados.
	Hr = PonteiroTrabalho->GetValue(KeyProp, vi_OutPropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a propVariant e define no parametro de saida.
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutPropVar);

Done:;
	//Libera a PropVariant.
	DeletarPropVariantSafe(&vi_OutPropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetValue) - Este método define um valor de propriedade ou substitui ou remove um valor existente.
/// </summary>
/// <param name="Param_PropKey">TBD.</param>
/// <param name="Param_PropValor">TBD.</param>
CarenResult CarenPropertyStore::DefinirValor(Estruturas::CA_PROPERTYKEY^% Param_PropKey, Estruturas::CA_PROPVARIANT^ Param_PropValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	PROPERTYKEY KeyProp = {};
	LPPROPVARIANT vi_PropValor = Nulo;

	//Define os dados na PROPERTYKEY.
	KeyProp.pid = Param_PropKey->PID;
	KeyProp.fmtid = String::IsNullOrEmpty(Param_PropKey->GUIDProp) ? GUID_NULL : Util.CreateGuidFromString(Param_PropKey->GUIDProp);

	//Converte a PropVariant gerenciada para a nativa.
	vi_PropValor = static_cast<LPPROPVARIANT>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_PropValor));

	//Verifica se não ocorreu um erro na conversão.
	if (!ObjetoValido(vi_PropValor))
	{
		//Falhou ao converter a propvariant.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		Sair;
	}

	//Chama o método para definir o valor.
	Hr = PonteiroTrabalho->SetValue(KeyProp, *vi_PropValor);

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
	//Libera a PropVariant.
	DeletarPropVariantSafe(&vi_PropValor);

	//Retorna o resultado.
	return Resultado;

}