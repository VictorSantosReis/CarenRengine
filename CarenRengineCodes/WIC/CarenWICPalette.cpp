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
#include "CarenWICPalette.h"

//Destruidor.
CarenWICPalette::~CarenWICPalette()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICPalette::CarenWICPalette()
{
	//CÓDIGO DE CRIAÇÃO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenWICPalette::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICPalette::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPalette*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICPalette::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPalette*>(Param_PonteiroNativo);

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
CarenResult CarenWICPalette::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICPalette::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICPalette::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICPalette::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICPalette::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICPalette::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICPalette::LiberarReferencia()
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
void CarenWICPalette::LimparDados()
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
void CarenWICPalette::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICPalette();
}



// Métodos da interface proprietária(ICarenWICPalette)


/// <summary>
/// Recupera o número de cores na tabela de cores. 
/// </summary>
/// <param name="Param_Out_Quantidade">Recebe o número de cores na tabela de cores.</param>
CarenResult CarenWICPalette::GetColorCount([Out] UInt32% Param_Out_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 OutQuantidade = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorCount(&OutQuantidade);

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

	//Define o valor no parametro de saida.
	Param_Out_Quantidade = OutQuantidade;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtéem a matriz de cores fornecida com as cores da tabela de cores internas. A matriz de cores deve ser dimensionada de acordo com os resultados de retorno do GetColorCount. 
/// </summary>
/// <param name="Param_Quantidade">O tamanho da matriz (Param_Out_Cores).</param>
/// <param name="Param_Out_Cores">Uma matriz que recebe as cores da paleta.</param>
/// <param name="Param_Out_CoresReais">Retorna o tamanho real necessário para obter as cores da paleta.</param>
CarenResult CarenWICPalette::GetColors(
UInt32 Param_Quantidade,
[Out] cli::array<UInt32>^% Param_Out_Cores,
[Out] UInt32% Param_Out_CoresReais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32* pOutArrayCores = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Quantidade));
	UINT32 OutCoresReais = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColors(Param_Quantidade, pOutArrayCores, &OutCoresReais);

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

	//Cria a matriz gerenciada.
	Param_Out_Cores = gcnew cli::array<UInt32>(Param_Quantidade);

	//Copia os dados da matriz nativa para gerenciada.
	Util.CopiarItensTo_ArrayGerenciado(Param_Out_Cores, pOutArrayCores, Param_Quantidade);

Done:;
	//Libera a memória utilizada pelo array
	DeletarMatrizUnidimensionalSafe(&pOutArrayCores);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o WICBitmapPaletteType que descreve a paleta. 
/// WICBitmapPaletteCustom é usado para paletas inicializadas tanto do InitializeCustom quanto do InitializeFromBitmap. Não há distinção entre paletas otimizadas e personalizadas.
/// </summary>
/// <param name="Param_Out_PaletteType">Recebe o tipo de paleta do bimtap.</param>
CarenResult CarenWICPalette::GetType([Out] CA_WICBitmapPaletteType% Param_Out_PaletteType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICBitmapPaletteType OutPaleteType;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetType(&OutPaleteType);

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

	//Define o valor no parametro de saida.
	Param_Out_PaletteType = static_cast<CA_WICBitmapPaletteType>(OutPaleteType);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Indica se a paleta contém uma entrada não-opaca (ou seja, uma entrada com um alfa menor que 1).
/// Vários formatos de imagem suportam alfa de diferentes maneiras. PNG tem suporte alfa completo, suportando entradas de paleta parcialmente transparentes. O GIF armazena cores 
/// como 24bpp, sem alfa, mas permite que uma entrada de paleta seja especificada como totalmente transparente. Se uma paleta tiver várias entradas totalmente transparentes (0x00RRGGBB),
///  o GIF usará a última como seu índice transparente.
/// </summary>
/// <param name="Param_Out_HasAlfa">Recebe TRUE se a paleta contiver uma cor transparente; caso contrário, FALSE.</param>
CarenResult CarenWICPalette::HasAlpha([Out] Boolean% Param_Out_HasAlfa)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutHasAlfa = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->HasAlpha(&OutHasAlfa);

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

	//Define o valor no parametro de saida.
	Param_Out_HasAlfa = OutHasAlfa ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa uma paleta para as entradas de cores personalizadas fornecidas. Se for necessária uma cor transparente, forneça-a como parte das entradas personalizadas. 
/// Para adicionar um valor transparente à paleta, seu valor alfa deve ser 0 (0x00RRGGBB).
/// A contagem de entradas é limitada a 256.
/// </summary>
/// <param name="Param_Cores">A matriz de cores.</param>
/// <param name="Param_Quantidade">O número de cores em (Param_Cores).</param>
CarenResult CarenWICPalette::InitializeCustom(
cli::array<UInt32>^ Param_Cores,
UInt32 Param_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32* pArrayCores = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Quantidade));

	//Copia os itens da matriz gerenciada para a nativa.
	Util.CopiarItensTo_ArrayNativo(&pArrayCores, Param_Cores, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeCustom(pArrayCores, Param_Quantidade);

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
	//Deleta a memória utilizada pela matriz.
	DeletarMatrizUnidimensionalSafe(&pArrayCores);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
///  Inicializa uma paleta usando um valor otimizado computado com base no bitmap de referência.
/// A paleta resultante contém o número especificado de cores que melhor representam as cores presentes no bitmap. O algoritmo opera no valor opaco de cor RGB de cada pixel 
/// no bitmap de referência e, portanto, ignora quaisquer valores alfa. Se for necessária uma cor transparente, defina o parâmetro (Param_AdicionarCorTransparente) para TRUE 
/// e uma cor menos otimizada será calculada, reduzindo a (Param_Quantidade), e uma entrada de cor totalmente transparente será adicionada.
/// </summary>
/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) que contém um ponteiro para a fonte do bitmap.</param>
/// <param name="Param_Quantidade">O número de cores para inicializar a paleta com.</param>
/// <param name="Param_AdicionarCorTransparente">Um valor para indicar se deve adicionar uma cor transparente.</param>
CarenResult CarenWICPalette::InitializeFromBitmap(
ICarenWICBitmapSource^ Param_FonteBitmap,
UInt32 Param_Quantidade,
Boolean Param_AdicionarCorTransparente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pBitmapSource = NULL;

	//Recupera o ponteiro para a fonte do bitmap.
	Resultado = RecuperarPonteiroCaren(Param_FonteBitmap, &pBitmapSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromBitmap(pBitmapSource, Param_Quantidade, Param_AdicionarCorTransparente ? TRUE : FALSE);

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
/// Inicialize a paleta com base em uma determinada paleta. 
/// </summary>
/// <param name="Param_Palette">Uma interface(ICarenWICPalette) que contém um ponteiro para paleta de origem.</param>
CarenResult CarenWICPalette::InitializeFromPalette(ICarenWICPalette^ Param_Palette)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* pWicPalette = NULL;

	//Recupera o ponteiro para a fonte do bitmap.
	Resultado = RecuperarPonteiroCaren(Param_Palette, &pWicPalette);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromPalette(pWicPalette);

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
/// Inicializa a paleta para uma das paletas pré-definidas especificadas pelo WICBitmapPaletteType e, opcionalmente, adiciona uma cor transparente. 
/// Se uma cor transparente for adicionada a uma paleta, a paleta não será mais predefinida e é devolvida como WICBitmapPaletteTypeCustom. Para paletas com menos de 256 entradas, 
/// a entrada transparente é adicionada ao final da paleta (ou seja, uma paleta de 16 cores torna-se uma paleta de 17 cores). Para paletas com 256 cores, a entrada transparente 
/// da paleta substituirá a última entrada na paleta pré-definida.
/// </summary>
/// <param name="Param_PaletteType">O tipo de paleta pré-definida desejada.</param>
/// <param name="Param_AdicionarCorTransparente">A cor opcional transparente para adicionar à paleta. Se não for necessária uma cor transparente, use 0. Ao inicializar para uma 
/// paleta em escala de cinza ou preto e branco, defina este 
/// parâmetro como FALSE.</param>
CarenResult CarenWICPalette::InitializePredefined(
CA_WICBitmapPaletteType Param_PaletteType,
Boolean Param_AdicionarCorTransparente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializePredefined(static_cast<WICBitmapPaletteType>(Param_PaletteType), Param_AdicionarCorTransparente ? TRUE : FALSE);

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
/// Recupera um valor que descreve se a paleta é em preto e branco. Uma paleta é considerada em preto e branco apenas se contiver exatamente duas entradas, uma preta completa 
/// (0xFF0000000) e uma branca completa (0xFFFFFFF).
/// </summary>
/// <param name="Param_Out_PretoBranco">Recebe um valor booleano que indica se a paleta é preto e branco. TRUE indica que a paleta é em preto e branco; caso contrário, FALSO.</param>
CarenResult CarenWICPalette::IsBlackWhite([Out] Boolean% Param_Out_PretoBranco)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutIsBlackWhite = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsBlackWhite(&OutIsBlackWhite);

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

	//Define o valor no parametro de saida.
	Param_Out_PretoBranco = OutIsBlackWhite ? TRUE : FALSE;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor que descreve se uma paleta é escala de cinza. 
/// Uma paleta é considerada escala de cinza somente se, para cada entrada, o valor alfa for 0xFF e os valores vermelho, verde e azul coincidirem.
/// </summary>
/// <param name="Param_Out_EscalaCinza">Recebe um valor booleano que indica se a paleta é escala de cinza. TRUE indica que a paleta é escala de cinza; caso contrário FALSO.</param>
CarenResult CarenWICPalette::IsGrayscale([Out] Boolean% Param_Out_EscalaCinza)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutIsGrayscale = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsBlackWhite(&OutIsGrayscale);

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

	//Define o valor no parametro de saida.
	Param_Out_EscalaCinza = OutIsGrayscale ? TRUE : FALSE;

Done:;
	//Retorna o resultado.
	return Resultado;
}