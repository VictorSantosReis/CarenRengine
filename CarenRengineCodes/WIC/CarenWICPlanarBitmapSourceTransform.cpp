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
#include "CarenWICPlanarBitmapSourceTransform.h"

//Destruidor.
CarenWICPlanarBitmapSourceTransform::~CarenWICPlanarBitmapSourceTransform()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICPlanarBitmapSourceTransform::CarenWICPlanarBitmapSourceTransform()
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
CarenResult CarenWICPlanarBitmapSourceTransform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICPlanarBitmapSourceTransform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPlanarBitmapSourceTransform*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICPlanarBitmapSourceTransform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPlanarBitmapSourceTransform*>(Param_PonteiroNativo);

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
CarenResult CarenWICPlanarBitmapSourceTransform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICPlanarBitmapSourceTransform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICPlanarBitmapSourceTransform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICPlanarBitmapSourceTransform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICPlanarBitmapSourceTransform::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICPlanarBitmapSourceTransform::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICPlanarBitmapSourceTransform::LiberarReferencia()
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
void CarenWICPlanarBitmapSourceTransform::LimparDados()
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
void CarenWICPlanarBitmapSourceTransform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICPlanarBitmapSourceTransform();
}



// Métodos da interface proprietária(ICarenWICPlanarBitmapSourceTransform)


/// <summary>
/// Copia pixels nos planos de destino. Configurado pelos parâmetros de entrada fornecidos.
/// Se uma conversão (Param_DestinoTransformacao), escala ou formato for especificada, o (CA_WICBitmapPlane::cbStride) é o stride transformado e é baseado no formato de pixel de destino do 
/// parâmetro (Param_PlanosDestino),  não no formato de pixel da fonte original.
/// </summary>
/// <param name="Param_RetanguloOrigem">O retângulo de origem de pixels para copiar.</param>
/// <param name="Param_Width">A largura para dimensionar o bitmap de origem. Este parâmetro deve ser igual a um valor obtido através do ICarenWICPlanarBitmapSourceTransform:: DoesSupportTransform.</param>
/// <param name="Param_Height">A altura para dimensionar o bitmap fonte. Este parâmetro deve ser igual a um valor obtido através do ICarenWICPlanarBitmapSourceTransform:: DoesSupportTransform.</param>
/// <param name="Param_DestinoTransformacao">A rotação ou o flip desejado para executar antes da cópia do pixel. Uma rotação pode ser combinada com um flip horizontal ou um flip vertical.</param>
/// <param name="Param_OpcoesPlanar">Usado para especificar opções adicionais de configuração para a transformação. Decodificador WIC JPEG: WICPlanarOptionsPreserveSubsampling pode ser 
/// especificado para manter as relações de subsamplagem quando a redução. Por padrão, o decodificador JPEG tenta preservar a qualidade baixando apenas o plano Y em alguns casos, alterando a imagem 
/// para 4:4:4 chroma subsampling.</param>
/// <param name="Param_PlanosDestino">Especifica o formato de pixel e o buffer de saída para cada plano componente. O número de planos e o formato de pixel de cada plano devem corresponder aos 
/// valores obtidos através do ICarenWICPlanarBitmapSourceTransform::DoesSupportTransform.</param>
/// <param name="Param_QuantidadePlanos">O número de planos componentes especificados pelo parâmetro (Param_PlanosDestino).</param>
CarenResult CarenWICPlanarBitmapSourceTransform::CopyPixels(
CA_WICRect^ Param_RetanguloOrigem,
UInt32 Param_Width,
UInt32 Param_Height,
CA_WICBitmapTransformOptions Param_DestinoTransformacao,
CA_WICPlanarOptions Param_OpcoesPlanar,
cli::array<CA_WICBitmapPlane^>^ Param_PlanosDestino,
UInt32 Param_QuantidadePlanos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRect* vi_RetanguloOrigem = Nulo;
	WICBitmapPlane* vi_ArrayPlanosDestinos = CriarMatrizEstruturas<WICBitmapPlane>(Param_QuantidadePlanos);
	WICBitmapPlane* vi_PlaneAuxiliar = Nulo;

	//Converte a estrutura do retangulo de origem.
	vi_RetanguloOrigem = Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloOrigem);

	//Faz um for para converter o array de de planos e definir na matriz nativa.
	for (UINT32 i = 0; i < Param_QuantidadePlanos; i++)
	{
		//Converte a estrutura.
		vi_PlaneAuxiliar = Util.ConverterWICBitmapPlaneManaged_ToUnmanaged(Param_PlanosDestino[i]);

		//Define na matriz nativa.
		vi_ArrayPlanosDestinos[i] = *vi_PlaneAuxiliar;

		//Libera a memória utilizada pela estrutura
		DeletarEstruturaSafe(&vi_PlaneAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPixels(
		vi_RetanguloOrigem,
		Param_Width,
		Param_Height,
		static_cast<WICBitmapTransformOptions>(Param_DestinoTransformacao),
		static_cast<WICPlanarOptions>(Param_OpcoesPlanar),
		vi_ArrayPlanosDestinos,
		Param_QuantidadePlanos
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
	//Libera a memória utilizadas pelas variaveis
	DeletarEstruturaSafe(&vi_RetanguloOrigem);
	DeletarMatrizEstruturasSafe(&vi_ArrayPlanosDestinos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Use este método para determinar se uma saída planar desejada é suportada e permiti que o chamador escolha um caminho de código otimizado, se for. Caso contrário, os chamadores devem recuar 
/// para ICarenWICBitmapSourceTransform ou ICarenWICBitmapSource e recuperar pixels intercalados.
/// Quando uma transformação é suportada, este método retorna a descrição dos planos resultantes no parâmetro (Param_Out_DescricaoPlanos).
/// </summary>
/// <param name="Param_Ref_INOUT_Width">Na entrada, a largura desejada. Na saída, a largura suportada mais próxima da largura desejada; este é o mesmo tamanho ou maior do que a largura desejada.</param>
/// <param name="Param_Ref_INOUT_Height">Na entrada, a altura desejada. Na saída, a altura suportada mais próxima da altura desejada; este é o mesmo tamanho ou maior do que a largura desejada.</param>
/// <param name="Param_DestinoTransformacao">A operação de rotação ou flip desejada. Várias opções de (CA_WICBitmapTransformOptions) podem ser combinadas neste parâmetro de bandeira.</param>
/// <param name="Param_OpcoesPlanar">Usado para especificar opções adicionais de configuração para a transformação.</param>
/// <param name="Param_GuidDestinoFormatos">Os formatos pixel solicitados dos respectivos planos.</param>
/// <param name="Param_Out_DescricaoPlanos">Quando Param_Out_Suporte == TRUE, o conjunto de descrições do plano contém o tamanho e o formato de cada um dos planos. Decodificador WIC JPEG: Os planos 
/// Cb e Cr podem ser de tamanho diferente dos valores devolvidos por (Param_Ref_INOUT_Width) e (Param_Ref_INOUT_Height) devido à subsamplagem de chroma.</param>
/// <param name="Param_QuantidadePlanos">O número de componentes planares solicitados.</param>
/// <param name="Param_Out_Suporte">Retorna TRUE se as transformações solicitadas forem apoiadas nativamente.</param>
CarenResult CarenWICPlanarBitmapSourceTransform::DoesSupportTransform(
UInt32% Param_Ref_INOUT_Width, 
UInt32% Param_Ref_INOUT_Height,
CA_WICBitmapTransformOptions Param_DestinoTransformacao,
CA_WICPlanarOptions Param_OpcoesPlanar,
cli::array<String^>^ Param_GuidDestinoFormatos,
[Out] cli::array<CA_WICBitmapPlaneDescription^>^% Param_Out_DescricaoPlanos,
UInt32 Param_QuantidadePlanos,
[Out] Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32 vi_InOutWidth = Param_Ref_INOUT_Width;
	UINT32 vi_InOutHeight = Param_Ref_INOUT_Height;
	GUID* vi_ArrayGuidFormatos = CriarMatrizEstruturas<GUID>(Param_QuantidadePlanos);
	WICBitmapPlaneDescription* vi_OutArrayDescPlanes = CriarMatrizEstruturas<WICBitmapPlaneDescription>(Param_QuantidadePlanos);
	BOOL vi_OutSuporte = FALSE;

	//Abre um for para criar os guids e definir na matriz.
	for (UINT32 i = 0; i < Param_QuantidadePlanos; i++)
	{
		//Converte e define no index especificado.
		vi_ArrayGuidFormatos[i] = Util.CreateGuidFromString(Param_GuidDestinoFormatos[i]);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportTransform(
		&vi_InOutWidth,
		&vi_InOutHeight,
		static_cast<WICBitmapTransformOptions>(Param_DestinoTransformacao),
		static_cast<WICPlanarOptions>(Param_OpcoesPlanar),
		vi_ArrayGuidFormatos,
		vi_OutArrayDescPlanes,
		Param_QuantidadePlanos,
		&vi_OutSuporte
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

	//Cria ao array de descrição de planos a ser retornado.
	Param_Out_DescricaoPlanos = gcnew cli::array<CA_WICBitmapPlaneDescription^>(Param_QuantidadePlanos);

	//Abre um for para converter os dados nativos e definir na matriz gerenciada
	for (UINT32 i = 0; i < Param_QuantidadePlanos; i++)
	{
		//Converte e define no index especificado
		Param_Out_DescricaoPlanos[i] = Util.ConverterWICBitmapPlaneDescriptionUnmanaged_ToManaged(&vi_OutArrayDescPlanes[i]);
	}

	//Define os dados de lagrura e altura retornados.
	Param_Ref_INOUT_Width = vi_InOutWidth;
	Param_Ref_INOUT_Height = vi_InOutHeight;

	//Define o valor de suporte
	Param_Out_Suporte = vi_OutSuporte ? true : false;

Done:;
	//Libera a memória utilizadas pelas variaveis.
	DeletarMatrizEstruturasSafe(&vi_ArrayGuidFormatos);
	DeletarMatrizEstruturasSafe(&vi_OutArrayDescPlanes);

	//Retorna o resultado.
	return Resultado;
}