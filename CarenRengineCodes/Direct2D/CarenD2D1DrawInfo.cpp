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

#include "../pch.h"
#include "CarenD2D1DrawInfo.h"

//Destruidor.
CarenD2D1DrawInfo::~CarenD2D1DrawInfo()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1DrawInfo::CarenD2D1DrawInfo()
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
CarenResult CarenD2D1DrawInfo::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DrawInfo::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DrawInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DrawInfo**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DrawInfo::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DrawInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DrawInfo**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DrawInfo::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DrawInfo::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1DrawInfo::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1DrawInfo::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1DrawInfo::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1DrawInfo::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1DrawInfo::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1DrawInfo();
}



// Métodos da interface proprietária(ICarenD2D1DrawInfo)


/// <summary>
/// Defina as instruções do sombreador para esta transformação. 
/// </summary>
/// <param name="Param_ShaderId">O ID de recurso para o sombreador.</param>
/// <param name="Param_PixelOptions">Informações adicionais fornecidas ao renderizador para indicar as operações que o sombreador de pixel faz.</param>
CarenResult CarenD2D1DrawInfo::SetPixelShader(
String^ Param_ShaderId,
CA_D2D1_PIXEL_OPTIONS Param_PixelOptions)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID pShaderId = GUID_NULL;
	D2D1_PIXEL_OPTIONS PixelOptions = static_cast<D2D1_PIXEL_OPTIONS>(Param_PixelOptions);

	//Converte a string gerenciada.
	pShaderId = Util.CreateGuidFromString(Param_ShaderId);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPixelShader(pShaderId, PixelOptions);

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
/// Define o buffer constante para o sombreador de pixels desta transformação. 
/// </summary>
/// <param name="Param_Buffer">Os dados aplicados ao buffer constante.</param>
/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante</param>
CarenResult CarenD2D1DrawInfo::SetPixelShaderConstantBuffer(
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr BufferData = IntPtr::Zero;

	//Recupera o ponteiro para o buffer
	Resultado = Param_Buffer->GetInternalPointer(BufferData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPixelShaderConstantBuffer(Util.ConverterIntPtrTo<PBYTE>(BufferData), Param_BufferSize);

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
/// Define a textura do recurso correspondente ao índice de textura do sombreador dado. 
/// </summary>
/// <param name="Param_IndexTextura">O índice da textura está ligado ao sombreador de pixels.</param>
/// <param name="Param_ResourceTexture">A textura de recursos criado.</param>
CarenResult CarenD2D1DrawInfo::SetResourceTexture(
UInt32 Param_IndexTextura,
ICarenD2D1ResourceTexture^ Param_ResourceTexture)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1ResourceTexture* pResourceTexture = NULL;

	//Recupera o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ResourceTexture, &pResourceTexture);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetResourceTexture(Param_IndexTextura, pResourceTexture);

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
/// Define um buffer de vértice, um sombreador de vértice correspondente e opções para controlar como os vértices devem ser manuseados pelo contexto Direct2D. 
/// Os sombreadores de vértice associados ao buffer de vértice através do sombreador de vértice GUID devem ter sido carregados através do método ICarenD2D1EffectContext::LoadVertexShader 
/// antes que esta chamada seja feita.
/// Se esta chamada falhar, a instância ICarenD2D1Effect correspondente será colocada em um estado de erro e falha ao desenhar.
/// </summary>
/// <param name="Param_VertexBuffer">O buffer de vértice, se isso for limpo, será usado o sombreador de vértice padrão e o mapeamento para os retângulos de transformação.</param>
/// <param name="Param_VertexOptions">Opções que influenciam como o renderizador interagirá com o sombreador de vértice.</param>
/// <param name="Param_DescricaoBlend">Como os vértices serão misturados com a textura de saída.</param>
/// <param name="Param_VertexRange">O conjunto de vértices para usar a partir do buffer.</param>
/// <param name="Param_GuidVertexShader">O GUID do sombreador de vértice.</param>
CarenResult CarenD2D1DrawInfo::SetVertexProcessing(
ICarenD2D1VertexBuffer^ Param_VertexBuffer,
CA_D2D1_VERTEX_OPTIONS Param_VertexOptions,
CA_D2D1_BLEND_DESCRIPTION^ Param_DescricaoBlend,
CA_D2D1_VERTEX_RANGE^ Param_VertexRange,
String^ Param_GuidVertexShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1VertexBuffer* pVertexBuffer = NULL;
	D2D1_VERTEX_OPTIONS VertexOptions = static_cast<D2D1_VERTEX_OPTIONS>(Param_VertexOptions);
	D2D1_BLEND_DESCRIPTION* pBlendDesc = NULL;
	D2D1_VERTEX_RANGE* pVertexRange = NULL;
	GUID GuidVertexShader = GUID_NULL;

	//Recupera o ponteiro para a interface de buffer de vertice.
	Resultado = RecuperarPonteiroCaren(Param_VertexBuffer, &pVertexBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pBlendDesc = Util.ConverterD2D1_BLEND_DESCRIPTIONManagedToUnmanaged(Param_DescricaoBlend);
	pVertexRange = Util.ConverterD2D1_VERTEX_RANGEManagedToUnmanaged(Param_VertexRange);

	//Cria o guid a parti da string.
	GuidVertexShader = Util.CreateGuidFromString(Param_GuidVertexShader);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetVertexProcessing(pVertexBuffer, VertexOptions, pBlendDesc, pVertexRange, &GuidVertexShader);

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
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pBlendDesc);
	DeletarEstruturaSafe(&pVertexRange);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o buffer constante para o sombreador de vértice desta transformação. 
/// </summary>
/// <param name="Param_Buffer">Os dados aplicados ao buffer constante</param>
/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante.</param>
CarenResult CarenD2D1DrawInfo::SetVertexShaderConstantBuffer(
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr BufferData = IntPtr::Zero;

	//Recupera o ponteiro para o buffer
	Resultado = Param_Buffer->GetInternalPointer(BufferData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetVertexShaderConstantBuffer(Util.ConverterIntPtrTo<PBYTE>(BufferData), Param_BufferSize);

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




// Métodos da interface (ICarenD2D1RenderInfo)


/// <summary>
/// Especifica que a saída da transformação na qual as informações de renderização estão encapsuladas é ou não armazenada em cache. 
/// </summary>
/// <param name="Param_IsCached">TRUE se a saída da transformação for armazenada em cache; caso contrário, FALSO.</param>
void CarenD2D1DrawInfo::SetCached(Boolean Param_IsCached)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetCached(Param_IsCached ? TRUE : FALSE);
}

/// <summary>
/// Define como uma entrada específica para a transformação deve ser tratada pelo renderizador em termos de amostragem. 
/// </summary>
/// <param name="Param_InputIndex">O índice da entrada que terá a descrição de entrada aplicada.</param>
/// <param name="Param_InputDescription">A descrição da entrada a ser aplicada à transformação.</param>
CarenResult CarenD2D1DrawInfo::SetInputDescription(
	UInt32 Param_InputIndex,
	CA_D2D1_INPUT_DESCRIPTION^ Param_InputDescription)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INPUT_DESCRIPTION* pInputDesc = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pInputDesc = Util.ConverterD2D1_INPUT_DESCRIPTIONManagedToUnmanaged(Param_InputDescription);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetInputDescription(Param_InputIndex, *pInputDesc);

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
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pInputDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Fornece uma sugestão estimada de custo de execução do sombreador para D2D. 
/// A contagem de instruções pode ser definida de acordo com o número de instruções no sombreador. Essas informações são usadas como uma dica ao renderizar imagens extremamente grandes. Chamar esta API é opcional, 
/// mas pode melhorar o desempenho se você fornecer um número preciso.
/// [NOTA] As instruções que ocorrem em um loop devem ser contadas de acordo com o número de iterações em loop.
/// </summary>
/// <param name="Param_InstructionCount">Uma contagem aproximada de instruções do sombreador associado.</param>
void CarenD2D1DrawInfo::SetInstructionCountHint(UInt32 Param_InstructionCount)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetInstructionCountHint(Param_InstructionCount);
}

/// <summary>
/// Permite que um chamador controle a precisão de saída e a profundidade do canal da transformação em que as informações de renderização são encapsuladas. 
/// Se a precisão de saída da transformação não for especificada, ela será padrão para a precisão especificada no contexto do dispositivo Direct2D. O máximo de 16bpc UNORM e 16bpc FLOAT é 32bpc FLOAT.
/// A profundidade do canal de saída corresponderá ao máximo das profundidades do canal de entrada se a profundidade do canal estiver D2D1_CHANNEL_DEPTH_DEFAULT.
/// Não há profundidade de canal de saída global, isso é sempre deixado para o controle das transformações.
/// </summary>
/// <param name="Param_BufferPrecision">O tipo de buffer que deve ser usado como saída a partir desta transformação.</param>
/// <param name="Param_ChannelDepth">O número de canais que serão usados no buffer de saída.</param>
CarenResult CarenD2D1DrawInfo::SetOutputBuffer(
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION BuffPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	D2D1_CHANNEL_DEPTH ChannelDep = static_cast<D2D1_CHANNEL_DEPTH>(Param_ChannelDepth);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputBuffer(BuffPrecision, ChannelDep);

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