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
#include "CarenWICDdsEncoder.h"

//Destruidor.
CarenWICDdsEncoder::~CarenWICDdsEncoder()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICDdsEncoder::CarenWICDdsEncoder()
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
CarenResult CarenWICDdsEncoder::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDdsEncoder::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDdsEncoder*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDdsEncoder**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDdsEncoder::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDdsEncoder*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDdsEncoder**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDdsEncoder::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDdsEncoder::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICDdsEncoder::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICDdsEncoder::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICDdsEncoder::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICDdsEncoder::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICDdsEncoder::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICDdsEncoder::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICDdsEncoder();
}



// Métodos da interface proprietária(ICarenWICDdsEncoder)


/// <summary>
/// Cria um novo frame para codificar. Isso equivale ao ICarenWICBitmapEncoder::CreateNewFrame, mas retorna informações adicionais sobre o índice de array, o nível de mip e 
/// a fatia do quadro recém-criado. Em contraste com ICarenWICBitmapEncoder::CreateNewFrame, não há parâmetro ICarenPropertyBag2 porque os frames DDS individuais não têm propriedades separadas.
/// </summary>
/// <param name="Param_Out_FrameEncode">Retorna uma interface(ICarenWICBitmapFrameEncode) que contém um ponteiro para o novo frame.</param>
/// <param name="Param_Out_ArrayIndex">Retorna o local onde o índice de matriz é devolvido. Opcional.</param>
/// <param name="Param_Out_MipLevel">Retorna o local onde o índice de nível mip é devolvido. Opcional.</param>
/// <param name="Param_Out_SliceIndex">Retorna o local onde o índice de fatia é devolvido. Opcional.</param>
CarenResult CarenWICDdsEncoder::CreateNewFrame(
[Out] ICarenWICBitmapFrameEncode^% Param_Out_FrameEncode,
[Out] UInt32% Param_Out_ArrayIndex,
[Out] UInt32% Param_Out_MipLevel,
[Out] UInt32% Param_Out_SliceIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapFrameEncode* vi_OutFrameEncode = Nulo;
	UINT vi_OutArrayIndex, vi_OutMipLevel, vi_OutSliceIndex = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateNewFrame(&vi_OutFrameEncode, &vi_OutArrayIndex, &vi_OutMipLevel, &vi_OutSliceIndex);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_FrameEncode = gcnew CarenWICBitmapFrameEncode();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_OutFrameEncode, Param_Out_FrameEncode, true);

	//Define o restante dos dados.
	Param_Out_ArrayIndex = vi_OutArrayIndex;
	Param_Out_MipLevel = vi_OutMipLevel;
	Param_Out_SliceIndex = vi_OutSliceIndex;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém dados específicos do DDS. Um aplicativo pode ligar para o GetParameters para obter os parâmetros DDS padrão, modificar alguns ou todos eles e, em seguida, chamar SetParameters.
/// </summary>
/// <param name="Param_Out_Parametros">Retorna uma estrutura que contém as informações do DDS.</param>
CarenResult CarenWICDdsEncoder::GetParameters([Out] CA_WICDdsParameters^% Param_Out_Parametros)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICDdsParameters Vi_OutDds = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetParameters(&Vi_OutDds);

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
	Param_Out_Parametros = Util.ConverterWICDdsParametersUnmanaged_ToManaged(&Vi_OutDds);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define dados específicos do DDS. Você não pode chamar esse método depois de começar a gravar dados de frame, por exemplo, chamando ICarenWICDdsEncoder::CreateNewFrame.
/// A definição de parâmetros DDS usando este método fornece ao codificador DDS informações sobre o número esperado de frames e as dimensões e outros parâmetros de cada frame.
/// </summary>
/// <param name="Param_Parametros">Uma estrutura onde as informações a serem definidas estão contidas.</param>
CarenResult CarenWICDdsEncoder::SetParameters(CA_WICDdsParameters^ Param_Parametros)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICDdsParameters* vi_Dds = Nulo;

	//Converte a estrutura.
	vi_Dds = Util.ConverterWICDdsParametersManaged_ToUnmanaged(Param_Parametros);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetParameters(vi_Dds);

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_Dds);

	//Retorna o resultado.
	return Resultado;
}