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
#include "CarenDXGIOutputDuplication.h"

//Destruidor.
CarenDXGIOutputDuplication::~CarenDXGIOutputDuplication()
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
CarenResult CarenDXGIOutputDuplication::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
	Hr = (reinterpret_cast<IDXGIOutputDuplication*>(PonteiroTrabalho))->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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
	Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

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
CarenResult CarenDXGIOutputDuplication::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIOutputDuplication*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenDXGIOutputDuplication::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIOutputDuplication*>(Param_PonteiroNativo);

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
CarenResult CarenDXGIOutputDuplication::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIOutputDuplication::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIOutputDuplication::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIOutputDuplication::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIOutputDuplication::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIOutputDuplication::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<IDXGIOutputDuplication*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIOutputDuplication::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<IDXGIOutputDuplication*>(PonteiroTrabalho))->Release();

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
void CarenDXGIOutputDuplication::LimparDados()
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
void CarenDXGIOutputDuplication::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenDXGIOutputDuplication();
}



// Métodos da interface proprietária(ICarenDXGIOutputDuplication)


/// <summary>
/// (AcquireNextFrame) - Indica que o aplicativo está pronto para processar a próxima imagem de desktop.
/// </summary>
/// <param name="Param_TimeOutMilliSeconds">O intervalo de tempo, em milissegundos. Este intervalo especifica a quantidade de tempo que este método espera por um novo frame antes de retornar ao 
/// chamador. Este método retorna se o intervalo passar, e uma nova imagem de desktop não estiver disponível.</param>
/// <param name="Param_Out_FrameInfo">Recebe a estrutura CA_DXGI_OUTDUPL_FRAME_INFO que descreve estatísticas de tempo e apresentação para um quadro.</param>
/// <param name="Param_Out_DesktopResource">Recebe um ponteiro para a interface ICarenDXGIResource da superfície que contém o bitmap desktop.</param>
CarenResult CarenDXGIOutputDuplication::AdquirirProximoFrame(
				UInt32 Param_TimeOutMilliSeconds,
				[Out] CA_DXGI_OUTDUPL_FRAME_INFO^% Param_Out_FrameInfo,
				[Out] ICarenDXGIResource^% Param_Out_DesktopResource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_OUTDUPL_FRAME_INFO FrameInfo = { 0 };
	IDXGIResource* pRecurso = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AcquireNextFrame(Param_TimeOutMilliSeconds, &FrameInfo, &pRecurso);

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

	//Converte a estrutura nativa para gerenciada e define no parametro de saida.
	Param_Out_FrameInfo = Util.ConverterDXGI_OUTDUPL_FRAME_INFOUnamaged_ToManaged(&FrameInfo);

	//Cria a interface do recurso a ser retornado.
	Param_Out_DesktopResource = gcnew CarenDXGIResource();

	//Define o ponteiro na interface
	Param_Out_DesktopResource->AdicionarPonteiro(pRecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Recupera uma descrição de uma saída duplicada. Esta descrição especifica as dimensões da superfície que contém a imagem da área de trabalho.
/// </summary>
/// <param name="Param_Out_Desc">Recebe uma estrutura CA_DXGI_OUTDUPL_DESC que descreve a saída duplicada.</param>
CarenResult CarenDXGIOutputDuplication::ObterDescricao([Out] CA_DXGI_OUTDUPL_DESC^% Param_Out_Desc)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_OUTDUPL_DESC DescOutDupl = { 0 };

	//Inicializa a estrutura com ZeroMemory
	ZeroMemory(&DescOutDupl, sizeof(DXGI_OUTDUPL_DESC));

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDesc(&DescOutDupl);

	//Converte a estrutura e define no parametro de saida.
	Param_Out_Desc = Util.ConverterDXGI_OUTDUPL_DESCUnManaged_ToManaged(&DescOutDupl);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFrameDirtyRects) - Obtém informações sobre retângulos sujos para o quadro(Frame) de desktop atual.
/// </summary>
/// <param name="Param_SizeMatrizRetangulos">O tamanho em bytes do buffer que o chamador passou para o parâmetro Param_Out_MatrizRetangulosSujos.</param>
/// <param name="Param_Out_MatrizRetangulosSujos">Recebe uma série de estruturas CA_RECT que identifica as regiões de retângulo sujo para o quadro de desktop.</param>
/// <param name="Param_Out_SizeMatrizRetangulos">Recebe o número de bytes que (ObterFrameDirtyRects) precisa armazenar informações sobre regiões sujas 
/// no buffer em (Param_Out_MatrizRetangulosSujos).</param>
CarenResult CarenDXGIOutputDuplication::ObterFrameDirtyRects(
				UInt32 Param_SizeMatrizRetangulos,
				[Out] cli::array<CA_RECT^>^% Param_Out_MatrizRetangulosSujos,
				[Out] UInt32% Param_Out_SizeMatrizRetangulos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<RECT> MatrizRects;
	UINT OutSizeMatriz = 0;

	//Aloca a quantidade solicitada.
	MatrizRects.reserve(Param_SizeMatrizRetangulos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameDirtyRects(Param_SizeMatrizRetangulos, MatrizRects.data(), &OutSizeMatriz);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);
	
	//Verifica se foi e um erro e se foi devido ao usuário ter informado um buffer pequeno
	//e define no valor de saida do método o valor necessário.
	if(Hr == DXGI_ERROR_MORE_DATA)
	{
		//Define a quantidade necessário retornada pelo método
		Param_Out_SizeMatrizRetangulos = static_cast<UInt32>(OutSizeMatriz);

		//Sai do método
		Sair;
	}

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Define a quantidade de dados no parametro de saida.
	Param_Out_SizeMatrizRetangulos = static_cast<UInt32>(OutSizeMatriz); //Esse valor é adicionado se a função falha com erro (DXGI_ERROR_MORE_DATA).

	//Cria a matriz que será retornada com os retangulos sujos
	Param_Out_MatrizRetangulosSujos = gcnew cli::array<CA_RECT^>(OutSizeMatriz);

	//Converte os dados nativos e define na matriz gerenciada
	for (UINT i = 0; i < OutSizeMatriz; i++)
	{
		//Converte a estrutura nativa para a gerenciada.
		Param_Out_MatrizRetangulosSujos[i] = Util.ConverterRECTUnmanagedToManaged(&MatrizRects.at(i));
	}

	//Limpa os dados do evento
	MatrizRects.clear();
	MatrizRects.shrink_to_fit();

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFrameMoveRects) - Obtém informações sobre os retângulos movidos para o quadro(Frame) de desktop atual.
/// </summary>
/// <param name="Param_SizeMatrizMoveRects">O tamanho em bytes do buffer que o chamador passou para o parâmetro Param_Out_MatrizMoveRects.</param>
/// <param name="Param_Out_MatrizMoveRects">Recebe uma matriz de estruturas CA_DXGI_OUTDUPL_MOVE_RECT que identifica as regiões de retângulo movido para o 
/// quadro de desktop.</param>
/// <param name="Param_Out_SizeMatrizMoveRects">Recebe o número de bytes que (ObterFrameMoveRects) precisa para armazenar informações sobre regiões movidas no buffer 
/// no Param_Out_MatrizMoveRects.</param>
CarenResult CarenDXGIOutputDuplication::ObterFrameMoveRects(
				UInt32 Param_SizeMatrizMoveRects, 
				[Out] cli::array<CA_DXGI_OUTDUPL_MOVE_RECT^>^% Param_Out_MatrizMoveRects,
				[Out] UInt32% Param_Out_SizeMatrizMoveRects)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	std::vector<DXGI_OUTDUPL_MOVE_RECT> MatrizRects;
	UINT OutSizeMatriz = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameMoveRects(Param_SizeMatrizMoveRects, MatrizRects.data(), &OutSizeMatriz);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);
	
	//Verifica se foi e um erro e se foi devido ao usuário ter informado um buffer pequeno
	//e define no valor de saida do método o valor necessário.
	if(Hr == DXGI_ERROR_MORE_DATA)
	{
		//Define a quantidade necessário retornada pelo método
		Param_Out_SizeMatrizMoveRects = static_cast<UInt32>(OutSizeMatriz);

		//Sai do método
		Sair;
	}

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Define a quantidade de dados no parametro de saida.
	Param_Out_SizeMatrizMoveRects = static_cast<UInt32>(OutSizeMatriz); //Esse valor é adicionado se a função falha com erro (DXGI_ERROR_MORE_DATA).

	//Cria a matriz que será retornada com os retangulos sujos
	Param_Out_MatrizMoveRects = gcnew cli::array<CA_DXGI_OUTDUPL_MOVE_RECT^>(OutSizeMatriz);

	//Converte os dados nativos e define na matriz gerenciada
	for (UINT i = 0; i < OutSizeMatriz; i++)
	{
		//Converte a estrutura nativa para a gerenciada.
		Param_Out_MatrizMoveRects[i] = Util.ConverterDXGI_OUTDUPL_MOVE_RECTUnManaged_ToManaged(&MatrizRects.at(i));
	}

	//Limpa os dados do evento
	MatrizRects.clear();
	MatrizRects.shrink_to_fit();

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFramePointerShape) - Obtém informações sobre a nova forma do ponteiro para o quadro(Frame) de desktop atual.
/// </summary>
/// <param name="Param_SizeBufferShape">O tamanho em bytes do buffer que o chamador passou para o parâmetro (Param_Ref_ShapePointerBuffer).</param>
/// <param name="Param_Ref_ShapePointerBuffer">Um ponteiro para um buffer para o qual o (ObterFramePointerShape) copia e retorna dados de pixels para a nova 
/// forma do ponteiro.</param>
/// <param name="Param_Out_SizeBufferShapeRequerido">Recebe o número de bytes que o (ObterFramePointerShape) precisa para armazenar os novos dados de pixel de 
/// forma de ponteiro no buffer em (Param_Ref_ShapePointerBuffer).</param>
/// <param name="Param_Out_PointerShapeInfo">Recebe uma estrutura CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO que contém as informações de forma do ponteiro.</param>
CarenResult CarenDXGIOutputDuplication::ObterFramePointerShape(
				UInt32 Param_SizeBufferShape,
				ICarenBuffer^% Param_Ref_ShapePointerBuffer,
				[Out] UInt32% Param_Out_SizeBufferShapeRequerido,
				[Out] CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^% Param_Out_PointerShapeInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PonteiroBuffer = IntPtr::Zero;
	PBYTE pBufferDataInCarenBuffer = NULL;
	UINT OutSizeBuffer = 0;
	DXGI_OUTDUPL_POINTER_SHAPE_INFO ShapeInfo = { 0 };

	//Recupera o ponteiro para o Buffer que vai receber os dados.
	Resultado = Param_Ref_ShapePointerBuffer->ObterPonteiroInterno(PonteiroBuffer);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao recuperar o buffer.

		//Sai do método
		goto Done;
	}

	//Converte para o ponteiro nativo.
	pBufferDataInCarenBuffer = (PBYTE)PonteiroBuffer.ToPointer();

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFramePointerShape(Param_SizeBufferShape, pBufferDataInCarenBuffer, &OutSizeBuffer, &ShapeInfo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);
	
	//Verifica se foi e um erro e se foi devido ao usuário ter informado um buffer pequeno
	//e define no valor de saida do método o valor necessário.
	if(Hr == DXGI_ERROR_MORE_DATA)
	{
		//Define a quantidade necessário retornada pelo método
		Param_Out_SizeBufferShapeRequerido = static_cast<UInt32>(OutSizeBuffer);

		//Sai do método
		Sair;
	}

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Define o tamanho que foi necessário para preencher o buffer com os dados do pixel
	Param_Out_SizeBufferShapeRequerido = static_cast<UInt32>(OutSizeBuffer); //Esse valor é definido quando ocorre o código de erro: DXGI_ERROR_MORE_DATA

	//Converte a estrutura nativa para gerenciada e define no parametro de saida
	Param_Out_PointerShapeInfo = Util.ConverterDXGI_OUTDUPL_POINTER_SHAPE_INFOUnManaged_ToManaged(&ShapeInfo);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa
	if (ObjetoValido(pBufferDataInCarenBuffer))
	{
		//Nula apenas.
		pBufferDataInCarenBuffer = NULL;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MapDesktopSurface) - Fornece a CPU acesso eficiente a uma imagem desktop se essa imagem de desktop já estiver na memória do sistema.
/// </summary>
/// <param name="Param_Out_MapData">Retorna uma estrutura CA_DXGI_MAPPED_RECT que recebe os dados superficiais que a CPU precisa para acessar diretamente 
/// os dados da superfície.</param>
CarenResult CarenDXGIOutputDuplication::MapearSuperficeDesktop([Out] CA_DXGI_MAPPED_RECT^% Param_Out_MapData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_MAPPED_RECT MapRect = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MapDesktopSurface(&MapRect);

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

	//Converte a estrutura nativa para gerenciada
	Param_Out_MapData = Util.ConverterDXGI_MAPPED_RECTUnManaged_ToManaged(&MapRect);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseFrame) - Indica que o aplicativo terminou de processar o quadro(Frame).
/// </summary>
CarenResult CarenDXGIOutputDuplication::LiberarFrame()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReleaseFrame();

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
/// (UnMapDesktopSurface) - Invalida o ponteiro para a imagem de desktop que foi recuperada usando ICarenDXGIOutputDuplication::MapearSuperficeDesktop.
/// </summary>
CarenResult CarenDXGIOutputDuplication::UnMapearSuperficeDesktop()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnMapDesktopSurface();

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


// Métodos da interface ICarenDXGIObject


/// <summary>
/// (GetParent) - Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIOutputDuplication::ObterPaiObjeto(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = GUID_NULL;
	LPVOID pInterfaceReturn = NULL;

	//Cria o guid da interface.
	RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetParent(RiidInterface, &pInterfaceReturn);

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

	//Define o ponteiro de trabalho na interface de saida.
	Param_Out_ObjetoPai->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateData) - Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGIOutputDuplication::DefinirDadosPrivados(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;

	//Cria o guid
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Recupera o ponteiro para os dados.
	Resultado = Param_Dados->RecuperarPonteiro(&pDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou. O ponteiro não era valido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateData(GuidIndent, Param_TamanhoDados, pDados);

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
/// (GetPrivateData) - Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIOutputDuplication::ObterDadosPrivados(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;
	UINT SizeDados = NULL;

	//Cria o guid a parti da string.
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPrivateData(GuidIndent, &SizeDados, &pDados);

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

	//Define o ponteiro para os dados.
	Param_Out_Dados->AdicionarPonteiro(pDados);

	//Adiciona o tamanho dos dados
	Param_Ref_TamanhoDados = SizeDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateDataInterface) - Defina uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGIOutputDuplication::DefinirDadosPrivadosInterface(String^ Param_GuidInterface, ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Cria o guid
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)&pInterface);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateDataInterface(GuidInterface, pInterface);

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
