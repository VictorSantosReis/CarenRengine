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
#include "CarenD2D1EffectContext1.h"

//Destruidor.
CarenD2D1EffectContext1::~CarenD2D1EffectContext1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1EffectContext1::CarenD2D1EffectContext1()
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
CarenResult CarenD2D1EffectContext1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1EffectContext1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1EffectContext1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1EffectContext1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1EffectContext1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1EffectContext1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1EffectContext1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1EffectContext1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1EffectContext1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1EffectContext1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1EffectContext1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1EffectContext1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1EffectContext1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1EffectContext1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1EffectContext1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1EffectContext1();
}



// Métodos da interface proprietária(ICarenD2D1EffectContext1)


/// <summary>
/// Cria uma tabela de pesquisa 3D para mapear uma entrada de 3 canais para uma saída de 3 canais. Os dados da tabela devem ser fornecidos em formato de 4 canais. 
/// </summary>
/// <param name="Param_BufferPrecision">Precisão dos dados da tabela de pesquisa de entrada.</param>
/// <param name="Param_Extents">Número de elementos de tabela de procuração por dimensão (X, Y, Z).</param>
/// <param name="Param_Data">Buffer segurando os dados da tabela de pesquisa.</param>
/// <param name="Param_DataSize">Tamanho do buffer de dados da tabela de pesquisa.</param>
/// <param name="Param_Strides">Uma matriz contendo dois valores. O primeiro valor é o tamanho em bytes de uma linha (dimensão X) de dados LUT para a próxima. O segundo valor
/// é o tamanho em bytes de um plano de dados LUT (dimensões X e Y) para o próximo.</param>
/// <param name="Param_Out_LookupTable3D">Recebe um ponteiro para a interface(ICarenD2D1LookupTable3D) de tabela de procuração 3D. </param>
CarenResult CarenD2D1EffectContext1::CreateLookupTable3D(
CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
cli::array<UInt32>^ Param_Extents,
ICarenBuffer^ Param_Data,
UInt32 Param_DataSize,
cli::array<UInt32>^ Param_Strides,
[Out] ICarenD2D1LookupTable3D^% Param_Out_LookupTable3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BUFFER_PRECISION BufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	UINT32* pMatrizExtents = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Extents->Length));
	IntPtr BufferData = IntPtr::Zero;
	UINT32* pMatrizStrides = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Strides->Length));
	ID2D1LookupTable3D* pOutLookupTable = NULL;

	//Copia os itens para as matrizes nativas.
	Util.CopiarItensTo_ArrayNativo(&pMatrizExtents, Param_Extents, Param_Extents->Length);
	Util.CopiarItensTo_ArrayNativo(&pMatrizStrides, Param_Strides, Param_Strides->Length);

	//Recupera o ponteiro para o buffer
	Resultado = Param_Data->GetInternalPointer(BufferData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLookupTable3D(
		BufferPrecision, 
		pMatrizExtents,
		Util.ConverterIntPtrTo<PBYTE>(BufferData), 
		Param_DataSize, 
		pMatrizStrides,
		&pOutLookupTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_LookupTable3D = gcnew CarenD2D1LookupTable3D();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutLookupTable, Param_Out_LookupTable3D, true);

Done:;
	//Libera a memória para as matrizes
	DeletarMatrizUnidimensionalSafe(&pMatrizExtents);
	DeletarMatrizUnidimensionalSafe(&pMatrizStrides);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface proprietária(ICarenD2D1EffectContext)


/// <summary>
/// Verifica se um recurso opcional é suportado pelo dispositivo D3D.
/// </summary>
/// <param name="Param_Feature">O recurso para consultar suporte.</param>
/// <param name="Param_Out_FeatureSupportData">Uma estrutura indicando informações sobre como ou se o recurso é suportado.</param>
/// <param name="Param_SizeFeatureData">O tamanho do parâmetro (Param_Out_FeatureSupportData).</param>
CarenResult CarenD2D1EffectContext1::CheckFeatureSupport(
	CA_D2D1_FEATURE Param_Feature,
	[Out] ICaren^% Param_Out_FeatureSupportData,
	UInt32 Param_SizeFeatureData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_FEATURE FeatureD2d = static_cast<D2D1_FEATURE>(Param_Feature);
	LPVOID pFeatureData = NULL;

	//Recupera um ponteiro para a estrutura de suporte a ser verificada.
	Resultado = RecuperarPonteiroCaren(Param_Out_FeatureSupportData, &pFeatureData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckFeatureSupport(FeatureD2d, pFeatureData, Param_SizeFeatureData);

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
/// Cria uma mistura que pode ser inserida em um gráfico de transformação. 
/// </summary>
/// <param name="Param_NumeroEntradas">O número de entradas na transformação de mistura.</param>
/// <param name="Param_DescBlend">Descreve a transformação de mistura que deve ser criada.</param>
/// <param name="Param_Out_BlendTransform">Retorna uma interface para a transformação da mistura(blend).</param>
CarenResult CarenD2D1EffectContext1::CreateBlendTransform(
	UInt32 Param_NumeroEntradas,
	CA_D2D1_BLEND_DESCRIPTION^ Param_DescBlend,
	[Out] ICarenD2D1BlendTransform^% Param_Out_BlendTransform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BLEND_DESCRIPTION* pBlendDesc = NULL;
	ID2D1BlendTransform* pOutBlendTransform = NULL;

	//Converte a estrutura
	pBlendDesc = Util.ConverterD2D1_BLEND_DESCRIPTIONManagedToUnmanaged(Param_DescBlend);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBlendTransform(Param_NumeroEntradas, pBlendDesc, &pOutBlendTransform);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_BlendTransform = gcnew CarenD2D1BlendTransform();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBlendTransform, Param_Out_BlendTransform, true);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pBlendDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma transformação que estende sua entrada infinitamente em todas as direções, com base na passada no modo de extensão.
/// </summary>
/// <param name="Param_ExtendModeX">O modo de extensão na direção do eixo X.</param>
/// <param name="Param_ExtendModeY">O modo de extensão na direção do eixo Y.</param>
/// <param name="Param_Out_BorderTransform">Retorna uma interface para a transformação devolvida.</param>
CarenResult CarenD2D1EffectContext1::CreateBorderTransform(
	CA_D2D1_EXTEND_MODE Param_ExtendModeX,
	CA_D2D1_EXTEND_MODE Param_ExtendModeY,
	[Out] ICarenD2D1BorderTransform^% Param_Out_BorderTransform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE ExtendModeY = static_cast<D2D1_EXTEND_MODE>(Param_ExtendModeY);
	D2D1_EXTEND_MODE ExtendModeX = static_cast<D2D1_EXTEND_MODE>(Param_ExtendModeX);
	ID2D1BorderTransform* pOutBorderTransform = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBorderTransform(ExtendModeX, ExtendModeY, &pOutBorderTransform);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_BorderTransform = gcnew CarenD2D1BorderTransform();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBorderTransform, Param_Out_BorderTransform, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria e retorna uma transformação de ajuste de limites. Uma transformação de suporte pode ser usada por duas razões diferentes:
/// Para indicar que uma região de sua imagem de entrada já é preto transparente. Isso pode aumentar a eficiência para renderizar bitmaps ou Para aumentar o tamanho da imagem 
/// de entrada. A área expandida será tratada como preta transparente
/// </summary>
/// <param name="Param_RetanguloSaida">O retângulo de saída inicial para a transformação de ajuste dos limites.</param>
/// <param name="Param_Out_Transform">Retorna um ponteiro para a interface de ajuste dos limites da transformação.</param>
CarenResult CarenD2D1EffectContext1::CreateBoundsAdjustmentTransform(
	CA_D2D1_RECT_L^ Param_RetanguloSaida,
	[Out] ICarenD2D1BoundsAdjustmentTransform^% Param_Out_Transform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_L* pRectSaida = NULL;
	ID2D1BoundsAdjustmentTransform* pOutBoundsTransform = NULL;

	//Converte a estrutura.
	pRectSaida = Util.ConverterD2D1_RECT_LManagedToUnmanaged(Param_RetanguloSaida);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBoundsAdjustmentTransform(pRectSaida, &pOutBoundsTransform);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_Transform = gcnew CarenD2D1BoundsAdjustmentTransform();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBoundsTransform, Param_Out_Transform, true);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pRectSaida);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cores a partir de um espaço de cores. Se o espaço de cor for Personalizado, o contexto será inicializado a partir dos parâmetros (Param_Profile) e 
/// (Param_SizeProfileBuffer). 
/// Se o espaço de cor não for Personalizado, o contexto é inicializado com os bytes de perfil associados ao espaço de cor. Os parâmetros de (Param_Profile) e 
/// (Param_SizeProfileBuffer) são ignorados.
/// </summary>
/// <param name="Param_EspacoCor">O espaço do contexto de cores para criar.</param>
/// <param name="Param_Profile">Um buffer contendo os bytes de perfil ICC usados para inicializar o contexto de cor quando o espaço é D2D1_COLOR_SPACE_CUSTOM. Para outros tipos, 
/// o parâmetro é ignorado e deve ser definido como NULO.</param>
/// <param name="Param_SizeProfileBuffer">O tamanho em bytes de (Param_Profile).</param>
/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
CarenResult CarenD2D1EffectContext1::CreateColorContext(
	CA_D2D1_COLOR_SPACE Param_EspacoCor,
	ICarenBuffer^ Param_Profile,
	UInt32 Param_SizeProfileBuffer,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_SPACE ColorSpace = static_cast<D2D1_COLOR_SPACE>(Param_EspacoCor);
	IntPtr pBufferProfile = IntPtr::Zero; //Pode ser NULO.
	ID2D1ColorContext* pOutColorContext = NULL;

	//Recupera o ponteiro para o profile de cor se valido.
	if (ObjetoGerenciadoValido(Param_Profile))
	{
		//Recupera o ponteiro para o profile.
		Resultado = Param_Profile->GetInternalPointer(pBufferProfile);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContext(ColorSpace, pBufferProfile == IntPtr::Zero ? NULL : Util.ConverterIntPtrTo<PBYTE>(pBufferProfile), Param_SizeProfileBuffer, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cor carregando-o a partir do nome de arquivo especificado. Os bytes de perfil são o conteúdo do arquivo especificado pelo (Param_UrlFilename). 
/// </summary>
/// <param name="Param_UrlFilename">O caminho para o arquivo contendo os bytes de perfil para inicializar o contexto de cores.</param>
/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
CarenResult CarenD2D1EffectContext1::CreateColorContextFromFilename(
	String^ Param_UrlFilename,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pUrlArquivo = NULL;
	ID2D1ColorContext* pOutColorContext = NULL;

	//Converte a string
	pUrlArquivo = Util.ConverterStringToWCHAR(Param_UrlFilename);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromFilename(pUrlArquivo, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext, true);

Done:;
	//Libera a memória para a string
	DeletarStringAllocatedSafe(&pUrlArquivo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cores a partir de um ICarenWICColorContext. O espaço D2D1ColorContext do contexto resultante varia.
/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado 
/// para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
/// </summary>
/// <param name="Param_WicColorContext">Um (ICarenWICColorContext) para inicializar o contexto de cores.</param>
/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
CarenResult CarenD2D1EffectContext1::CreateColorContextFromWicColorContext(
	ICaren^ Param_WicColorContext,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext* pWicColorContext = NULL;
	ID2D1ColorContext* pOutColorContext = NULL;

	//Recupera o ponteiro para o contexto de cores do WIC.
	Resultado = RecuperarPonteiroCaren(Param_WicColorContext, &pWicColorContext);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromWicColorContext(pWicColorContext, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um efeito Direct2D para o ID de classe especificado. Isso é o mesmo que ICarenD2D1DeviceContext::CreateEffect para que os efeitos personalizados possam criar outros efeitos
/// e envolvê-los em uma transformação. 
/// O efeito criado não faz referência à contagem do DLL a partir do qual o efeito foi criado. Se o chamador não recarregar um efeito enquanto esse efeito estiver carregado, o comportamento
/// resultante será imprevisível.
/// </summary>
/// <param name="Param_IdEfeito">O ID de efeito embutido ou registrado para criar o efeito. Consulte os GUIDs de efeitos do Direct2D para obter um ID para este parametro.</param>
/// <param name="Param_Out_Efeito">Retorna um ponteiro para a interface(ICarenD2D1Effect) do efeito especificado.</param>
CarenResult CarenD2D1EffectContext1::CreateEffect(
	String^ Param_IdEfeito,
	[Out] ICarenD2D1Effect^% Param_Out_Efeito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdEfeito = GUID_NULL;
	ID2D1Effect* pOutEfeito = NULL;

	//Converte a string para guid.
	IdEfeito = Util.CreateGuidFromString(Param_IdEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateEffect(IdEfeito, &pOutEfeito);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_Efeito = gcnew CarenD2D1Effect();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutEfeito, Param_Out_Efeito, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria e devolve uma transformação Offset.
/// Uma transformação offset é usada para compensar um bitmap de entrada sem ter que inserir um passe de renderização. Uma transformação offset é automaticamente inserida por 
/// uma transformação Affine se a transformação for avaliada em uma transformação alinhada a pixels.
/// </summary>
/// <param name="Param_Offset">O valor de deslocamento.</param>
/// <param name="Param_Out_Transform">Retorna um ponteiro da interface(ICarenD2D1OffsetTransform) para um objeto de transformação Offset.</param>
CarenResult CarenD2D1EffectContext1::CreateOffsetTransform(
	CA_D2D1_POINT_2L^ Param_Offset,
	[Out] ICarenD2D1OffsetTransform^% Param_Out_Transform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2L* pPointOffset = NULL;
	ID2D1OffsetTransform* pOutOffsetTransform = NULL;

	//Converte a estrutura
	pPointOffset = Util.ConverterD2D1_POINT_2LManagedToUnmanaged(Param_Offset);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateOffsetTransform(*pPointOffset, &pOutOffsetTransform);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_Transform = gcnew CarenD2D1OffsetTransform();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutOffsetTransform, Param_Out_Transform, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pOutOffsetTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria ou encontra a textura do recurso dada, dependendo se um id de recurso é especificado. Também inicializa opcionalmente a textura com os dados especificados. 
/// </summary>
/// <param name="Param_IdRecurso">Um GUID opcional para o ID exclusivo que identifica a Lookup Table.</param>
/// <param name="Param_PropsRecursoTextura">As propriedades usadas para criar a textura do recurso.</param>
/// <param name="Param_Dados">Os dados opcionais a serem carregados na textura do recurso.</param>
/// <param name="Param_Strides">Um array de strides para avançar através da textura do recurso, de acordo com a dimensão.</param>
/// <param name="Param_SizeDados">O tamanho, em bytes, dos dados.</param>
/// <param name="Param_Out_RecursoTextura">Retorna um ponteiro para a interface(ICarenD2D1ResourceTexture) da textura devolvida para ser usada como recurso ou efeito pelo Direct2D. </param>
CarenResult CarenD2D1EffectContext1::CreateResourceTexture(
	String^ Param_IdRecurso,
	CA_D2D1_RESOURCE_TEXTURE_PROPERTIES^ Param_PropsRecursoTextura,
	ICarenBuffer^ Param_Dados,
	cli::array<UInt32>^ Param_Strides,
	UInt32 Param_SizeDados,
	[Out] ICarenD2D1ResourceTexture^% Param_Out_RecursoTextura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	D2D1_RESOURCE_TEXTURE_PROPERTIES* pResourceTextureProps = NULL;
	IntPtr pBufferDados = IntPtr::Zero; //Pode ser NULO.
	UINT32* pMatrizStrides = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_PropsRecursoTextura->dimensions));
	ID2D1ResourceTexture* pOutResourceTexture = NULL;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Converte a estrutura
	pResourceTextureProps = Util.ConverterD2D1_RESOURCE_TEXTURE_PROPERTIESManagedToUnmanaged(Param_PropsRecursoTextura);

	//Recupera ao ponteiro para os dados se fornecido
	if (ObjetoGerenciadoValido(Param_Dados))
	{
		//Recupera o ponteiro para os dados.
		Resultado = Param_Dados->GetInternalPointer(pBufferDados);

		//Sai do método em caso de erro.
		SairOnError(Resultado);
	}

	//Copia os dados do array de strides.
	Util.CopiarItensTo_ArrayNativo(&pMatrizStrides, Param_Strides, Param_PropsRecursoTextura->dimensions);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateResourceTexture(
		&IdRecurso,
		pResourceTextureProps,
		pBufferDados == IntPtr::Zero ? NULL : Util.ConverterIntPtrTo<PBYTE>(pBufferDados),
		pMatrizStrides,
		Param_SizeDados,
		&pOutResourceTexture);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_RecursoTextura = gcnew CarenD2D1ResourceTexture();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutResourceTexture, Param_Out_RecursoTextura, true);

Done:;
	//Libera a memória para os dados.
	DeletarMatrizUnidimensionalSafe(&pResourceTextureProps->extents);
	DeletarMatrizUnidimensionalSafe(&pResourceTextureProps->extendModes);
	DeletarEstruturaSafe(&pResourceTextureProps);
	DeletarMatrizUnidimensionalSafe(&pMatrizStrides);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Embrulha um gráfico de efeito em um único nó de transformação e, em seguida, inserido em um gráfico de transformação. Isso permite um efeito para agregar outros efeitos. 
/// Isso normalmente será feito para permitir que as propriedades de efeito sejam ree expressas com um contrato diferente, ou para permitir que diferentes componentes integrem 
/// os efeitos uns dos outros. 
/// </summary>
/// <param name="Param_Efeito">O efeito a ser embrulhado em um nó de transformação.</param>
/// <param name="Param_Out_TransformNode">Retorna um ponteiro para a interface(ICarenD2D1TransformNode) do nó de transformação que encapsulao gráficode efeito. </param>
CarenResult CarenD2D1EffectContext1::CreateTransformNodeFromEffect(
	ICarenD2D1Effect^ Param_Efeito,
	[Out] ICarenD2D1TransformNode^% Param_Out_TransformNode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Effect* pEfeito = NULL;
	ID2D1TransformNode* pOutTransformNode = NULL;

	//Recupera o ponteiro para o efeito
	Resultado = RecuperarPonteiroCaren(Param_Efeito, &pEfeito);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTransformNodeFromEffect(pEfeito, &pOutTransformNode);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_TransformNode = gcnew CarenD2D1TransformNode();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutTransformNode, Param_Out_TransformNode, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um buffer de vértice ou encontra um buffer de vértice padrão e, opcionalmente, inicializa-o com vértices. O buffer retornado pode ser especificado nas 
/// informações de renderização para especificar tanto um sombreador de vértice quanto ou passar vértices personalizados para o sombreador de vértice padrão usado pelo Direct2D. 
/// </summary>
/// <param name="Param_PropsVertexBuffer">As propriedades usadas para descrever o amortecedor de vértice e o sombreador de vértices.</param>
/// <param name="Param_IdRecurso">A identificação única que identifica o buffer de vértice.</param>
/// <param name="Param_PropsCustomVertexBuffer">As propriedades usadas para definir um buffer de vértice personalizado. Se você usar um sombreador de vértice embutido, 
/// você não precisa especificar esta propriedade.</param>
/// <param name="Param_Out_VertexBuffer">Retorna um ponteiro para a interface(ICarenD2D1VertexBuffer) do buffer de vertices devolvido.</param>
CarenResult CarenD2D1EffectContext1::CreateVertexBuffer(
	CA_D2D1_VERTEX_BUFFER_PROPERTIES^ Param_PropsVertexBuffer,
	String^ Param_IdRecurso,
	CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES^ Param_PropsCustomVertexBuffer,
	[Out] ICarenD2D1VertexBuffer^% Param_Out_VertexBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_VERTEX_BUFFER_PROPERTIES* pVertexBufferProps = NULL;
	GUID IdRecurso = GUID_NULL;
	D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES* pCustomVertexBufferProps = NULL;
	ID2D1VertexBuffer* pOutVertexBuffer = NULL;

	//Converte as estruturas.
	pVertexBufferProps = Util.ConverterD2D1_VERTEX_BUFFER_PROPERTIESManagedToUnmanaged(Param_PropsVertexBuffer);
	pCustomVertexBufferProps = Util.ConverterD2D1_CUSTOM_VERTEX_BUFFER_PROPERTIESManagedToUnmanaged(Param_PropsCustomVertexBuffer);

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateVertexBuffer(pVertexBufferProps, &IdRecurso, pCustomVertexBufferProps, &pOutVertexBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_VertexBuffer = gcnew CarenD2D1VertexBuffer();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutVertexBuffer, Param_Out_VertexBuffer, true);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pVertexBufferProps);
	DeletarMatrizUnidimensionalSafe(&pCustomVertexBufferProps->shaderBufferWithInputSignature);
	DeletarMatrizEstruturasSafe(&pCustomVertexBufferProps->inputElements);
	DeletarEstruturaSafe(&pCustomVertexBufferProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Encontra a textura de recurso dada se ela já foi criada com ICarenD2D1EffectContext::CreateResourceTexture com o mesmo GUID.
/// </summary>
/// <param name="Param_IdRecurso">A identificação única que identifica a textura do recurso.</param>
/// <param name="Param_Out_RecursoTextura">Retorna um ponteiro para a interface(ICarenD2D1ResourceTexture) da textura devolvida que pode ser usada como recurso 
/// ou em um efeito Direct2D.</param>
CarenResult CarenD2D1EffectContext1::FindResourceTexture(
	String^ Param_IdRecurso,
	[Out] ICarenD2D1ResourceTexture^% Param_Out_RecursoTextura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	ID2D1ResourceTexture* pResourceTexture = NULL;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindResourceTexture(&IdRecurso, &pResourceTexture);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_RecursoTextura = gcnew CarenD2D1ResourceTexture();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pResourceTexture, Param_Out_RecursoTextura, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Encontra o buffer de vértice dado se ele já foi criado com ICarenD2D1EffectContext::CreateVertexBuffer com o mesmo GUID. 
/// </summary>
/// <param name="Param_IdRecurso">A identificação única que identifica o buffer de vértice.</param>
/// <param name="Param_Out_VertexBuffer">Retorna um ponteiro para a interface(ICarenD2D1VertexBuffer) do buffer de vértice devolvido que pode ser usado como recurso 
/// em um efeito Direct2D.</param>
CarenResult CarenD2D1EffectContext1::FindVertexBuffer(
	String^ Param_IdRecurso,
	[Out] ICarenD2D1VertexBuffer^% Param_Out_VertexBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	ID2D1VertexBuffer* pOutVertexBuffer = NULL;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindVertexBuffer(&IdRecurso, &pOutVertexBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_VertexBuffer = gcnew CarenD2D1VertexBuffer();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutVertexBuffer, Param_Out_VertexBuffer, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o mapeamento da unidade que um efeito usará para propriedades que podem estar em pontos por polegada (Dpi) ou pixels.
/// Se o D2D1_UNIT_MODE for D2D1_UNIT_MODE_PIXELS, tanto o DPI_X quanto o DPI_Y serão definidos como 96.
/// </summary>
/// <param name="Param_Out_DpiX">O DPI no eixo X.</param>
/// <param name="Param_Out_DpiY">O DPI no eixo Y.</param>
void CarenD2D1EffectContext1::GetDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY)
{
	//Variaveis a serem utilizadas.
	FLOAT OutDpiX = 0;
	FLOAT OutDpiY = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDpi(&OutDpiX, &OutDpiY);

	//Define nos parametros de saida.
	Param_Out_DpiX = OutDpiX;
	Param_Out_DpiY = OutDpiY;
}

/// <summary>
/// Isso indica o nível máximo de recurso da lista fornecida que é suportada pelo dispositivo. Se nenhum dos níveis fornecidos for suportado, então esta API falhará com 
/// D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES. 
/// </summary>
/// <param name="Param_NiveisRecurso">Os níveis de recurso fornecidos pelo aplicativo.</param>
/// <param name="Param_QuantidadeNiveis">A contagem de níveis de recursos fornecidos pelo aplicativo</param>
/// <param name="Param_Out_NivelRecursoMaximo">O nível máximo de recurso da lista (Param_NiveisRecurso), que é suportado pelo dispositivo D2D.</param>
CarenResult CarenD2D1EffectContext1::GetMaximumSupportedFeatureLevel(
	cli::array<CA_D3D_FEATURE_LEVEL>^ Param_NiveisRecurso,
	UInt32 Param_QuantidadeNiveis,
	[Out] CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecursoMaximo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D_FEATURE_LEVEL* pMatrizNiveisRecurso = CriarMatrizUnidimensional<D3D_FEATURE_LEVEL>(static_cast<DWORD>(Param_QuantidadeNiveis));
	D3D_FEATURE_LEVEL OutNivelRecurso;

	//Copia os dados para a matriz.
	Util.CopiarItensTo_ArrayNativo(&pMatrizNiveisRecurso, Param_NiveisRecurso, Param_QuantidadeNiveis);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMaximumSupportedFeatureLevel(pMatrizNiveisRecurso, Param_QuantidadeNiveis, &OutNivelRecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o nivel de recurso mais alto no parametro de saida.
	Param_Out_NivelRecursoMaximo = static_cast<CA_D3D_FEATURE_LEVEL>(OutNivelRecurso);

Done:;
	//Libera a memória para a matriz
	DeletarMatrizUnidimensionalSafe(&pMatrizNiveisRecurso);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Indica se a precisão do buffer é suportada pelo dispositivo Direct2D subjacente.
/// </summary>
/// <param name="Param_BufferPrecision">A precisão do buffer para verificar.</param>
/// <param name="Param_Out_Suporte">Retorna TRUE se a precisão do buffer for suportada. Retorna FALSE se a precisão do buffer não for suportada.</param>
void CarenD2D1EffectContext1::IsBufferPrecisionSupported(
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	[Out] Boolean% Param_Out_Suporte)
{
	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION BufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	BOOL OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	OutSuporte = PonteiroTrabalho->IsBufferPrecisionSupported(BufferPrecision);

	//Define o suporte no parametro de saida.
	Param_Out_Suporte = OutSuporte ? true : false;
}

/// <summary>
/// Realiza um teste para ver se o shader fornecido está carregado.
/// </summary>
/// <param name="Param_ShaderId">A identificação única que identifica o sombreador.</param>
/// <param name="Param_Out_Loaded">Retorna TRUE se o shader tiver sido carregado. Retorna FALSE se o shader não está carregado.</param>
void CarenD2D1EffectContext1::IsShaderLoaded(
	String^ Param_ShaderId,
	[Out] Boolean% Param_Out_Loaded)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdShader = GUID_NULL;

	//Cria o guid.
	IdShader = Util.CreateGuidFromString(Param_ShaderId);

	//Chama o método para realizar a operação.
	Param_Out_Loaded = PonteiroTrabalho->IsShaderLoaded(IdShader) ? true : false;
}

/// <summary>
/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
/// para JIT, se ainda não foi. O sombreador especificado deve ser compilado, não em código HLSL bruto.
/// </summary>
/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
CarenResult CarenD2D1EffectContext1::LoadComputeShader(
	String^ Param_IdRecurso,
	ICarenBuffer^ Param_ShaderBuffer,
	UInt32 Param_ShaderBufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	IntPtr ShaderBuffer = IntPtr::Zero;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Recupera o ponteiro para o buffer
	Resultado = Param_ShaderBuffer->GetInternalPointer(ShaderBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadComputeShader(IdRecurso, Util.ConverterIntPtrTo<PBYTE>(ShaderBuffer), Param_ShaderBufferSize);

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
/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
/// para JIT, se ainda não foi.
/// O sombreador especificado deve ser compilado, não em código HLSL bruto.
/// </summary>
/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
CarenResult CarenD2D1EffectContext1::LoadPixelShader(
	String^ Param_IdRecurso,
	ICarenBuffer^ Param_ShaderBuffer,
	UInt32 Param_ShaderBufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	IntPtr ShaderBuffer = IntPtr::Zero;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Recupera o ponteiro para o buffer
	Resultado = Param_ShaderBuffer->GetInternalPointer(ShaderBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadPixelShader(IdRecurso, Util.ConverterIntPtrTo<PBYTE>(ShaderBuffer), Param_ShaderBufferSize);

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
/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
/// para JIT, se ainda não foi. 
/// O sombreador especificado deve ser compilado, não em código HLSL bruto.
/// </summary>
/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
CarenResult CarenD2D1EffectContext1::LoadVertexShader(
	String^ Param_IdRecurso,
	ICarenBuffer^ Param_ShaderBuffer,
	UInt32 Param_ShaderBufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdRecurso = GUID_NULL;
	IntPtr ShaderBuffer = IntPtr::Zero;

	//Cria o guid
	IdRecurso = Util.CreateGuidFromString(Param_IdRecurso);

	//Recupera o ponteiro para o buffer
	Resultado = Param_ShaderBuffer->GetInternalPointer(ShaderBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadVertexShader(IdRecurso, Util.ConverterIntPtrTo<PBYTE>(ShaderBuffer), Param_ShaderBufferSize);

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