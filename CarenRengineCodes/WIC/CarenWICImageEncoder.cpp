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
#include "CarenWICImageEncoder.h"

//Destruidor.
CarenWICImageEncoder::~CarenWICImageEncoder()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICImageEncoder::CarenWICImageEncoder()
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
CarenResult CarenWICImageEncoder::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICImageEncoder::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IWICImageEncoder*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICImageEncoder::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IWICImageEncoder*>(Param_PonteiroNativo);

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
CarenResult CarenWICImageEncoder::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenWICImageEncoder::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenWICImageEncoder::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICImageEncoder::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICImageEncoder::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICImageEncoder::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICImageEncoder::LiberarReferencia()
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
void CarenWICImageEncoder::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICImageEncoder();
}



// Métodos da interface proprietária(ICarenWICImageEncoder)


/// <summary>
/// Codifica a imagem para o frame dado pelo ICarenWICBitmapFrameEncode. 
/// A imagem passada deve ser criada no mesmo dispositivo do ICarenWICImagingFactory2::CreateImageEncoder. Se os (Param_ParametrosAdicionais) não forem especificados,
///  um conjunto de padrões úteis será assumido.
/// Você deve ter configurado corretamente e de forma independente o ICarenWICBitmapFrameEncode antes de chamar esta API.
/// </summary>
/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
/// <param name="Param_FrameEncode">Uma interface(ICarenWICBitmapFrameEncode) que representa o codificador de frames para o qual a imagem está escrita.</param>
/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
CarenResult CarenWICImageEncoder::WriteFrame(
ICaren^ Param_D2D1Image,
ICarenWICBitmapFrameEncode^ Param_FrameEncode,
CA_WICImageParameters^ Param_ParametrosAdicionais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* vi_pD2d1Image = Nulo;
	IWICBitmapFrameEncode* vi_pBitmapFrameEnco = Nulo;
	WICImageParameters* vi_pWicParameters = Nulo; //Pode ser NULO.

	//Recupera o ponteiro para a interface do direct2d
	Resultado = RecuperarPonteiroCaren(Param_D2D1Image, &vi_pD2d1Image);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface de encodificação de frame.
	Resultado = RecuperarPonteiroCaren(Param_FrameEncode, &vi_pBitmapFrameEnco);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura adicional se informada.
	vi_pWicParameters = ObjetoGerenciadoValido(Param_ParametrosAdicionais) ? Util.ConverterWICImageParametersManaged_ToUnManaged(Param_ParametrosAdicionais) : Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteFrame(vi_pD2d1Image, vi_pBitmapFrameEnco, vi_pWicParameters);

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pWicParameters);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Codifica a imagem como uma miniatura do quadro dado pelo ICarenWICBitmapFrameEncode.
/// A imagem passada deve ser criada no mesmo dispositivo do ICarenWICImagingFactory2::CreateImageEncoder. Se os (Param_ParametrosAdicionais) não forem especificados, um 
/// conjunto de padrões úteis será assumido.
/// Você deve ter configurado corretamente e de forma independente o ICarenWICBitmapFrameEncode antes de chamar esta API.
/// </summary>
/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
/// <param name="Param_FrameEncode">Uma interface(ICarenWICBitmapFrameEncode) que representa o codificador de frames para o qual a miniatura está definida.</param>
/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
CarenResult CarenWICImageEncoder::WriteFrameThumbnail(
ICaren^ Param_D2D1Image,
ICarenWICBitmapFrameEncode^ Param_FrameEncode,
CA_WICImageParameters^ Param_ParametrosAdicionais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* vi_pD2d1Image = Nulo;
	IWICBitmapFrameEncode* vi_pBitmapFrameEnco = Nulo;
	WICImageParameters* vi_pWicParameters = Nulo; //Pode ser NULO.

	//Recupera o ponteiro para a interface do direct2d
	Resultado = RecuperarPonteiroCaren(Param_D2D1Image, &vi_pD2d1Image);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface de encodificação de frame.
	Resultado = RecuperarPonteiroCaren(Param_FrameEncode, &vi_pBitmapFrameEnco);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura adicional se informada.
	vi_pWicParameters = ObjetoGerenciadoValido(Param_ParametrosAdicionais) ? Util.ConverterWICImageParametersManaged_ToUnManaged(Param_ParametrosAdicionais) : Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteFrameThumbnail(vi_pD2d1Image, vi_pBitmapFrameEnco, vi_pWicParameters);

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pWicParameters);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Codifica a imagem dada como miniatura do codificador de bitmap WIC dado. 
/// Você deve criar a imagem que você passa no mesmo dispositivo que no ICarenWICImagingFactory2::CreateImageEncoder. Se você não especificar parâmetros adicionais na 
/// variável que (Param_ParametrosAdicionais) aponta, o codificador usará um conjunto de padrões úteis.
/// Antes de chamar WriteThumbnail, você deve configurar a interface ICarenWICBitmapEncoder para o codificador no qual deseja definir a miniatura.
/// Se o WriteThumbnail falhar, ele poderá retornar E_OUTOFMEMORY, D2DERR_WRONG_RESOURCE_DOMAIN ou outros códigos de erro do codificador.
/// </summary>
/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
/// <param name="Param_BitmapEncoder">Uma interface(ICarenWICBitmapEncoder) que representa o codificador em que a miniatura está definida.</param>
/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
CarenResult CarenWICImageEncoder::WriteThumbnail(
ICaren^ Param_D2D1Image,
ICarenWICBitmapEncoder^ Param_BitmapEncoder,
CA_WICImageParameters^ Param_ParametrosAdicionais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* vi_pD2d1Image = Nulo;
	IWICBitmapEncoder* vi_pBitmapEnco = Nulo;
	WICImageParameters* vi_pWicParameters = Nulo; //Pode ser NULO.

	//Recupera o ponteiro para a interface do direct2d
	Resultado = RecuperarPonteiroCaren(Param_D2D1Image, &vi_pD2d1Image);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface de encodificação de frame.
	Resultado = RecuperarPonteiroCaren(Param_BitmapEncoder, &vi_pBitmapEnco);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura adicional se informada.
	vi_pWicParameters = ObjetoGerenciadoValido(Param_ParametrosAdicionais) ? Util.ConverterWICImageParametersManaged_ToUnManaged(Param_ParametrosAdicionais) : Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteThumbnail(vi_pD2d1Image, vi_pBitmapEnco, vi_pWicParameters);

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pWicParameters);

	//Retorna o resultado.
	return Resultado;
}