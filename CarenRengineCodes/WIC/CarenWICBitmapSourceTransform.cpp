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
#include "CarenWICBitmapSourceTransform.h"

//Destruidor.
CarenWICBitmapSourceTransform::~CarenWICBitmapSourceTransform()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapSourceTransform::CarenWICBitmapSourceTransform()
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
CarenResult CarenWICBitmapSourceTransform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapSourceTransform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapSourceTransform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapSourceTransform**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapSourceTransform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapSourceTransform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapSourceTransform**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapSourceTransform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapSourceTransform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICBitmapSourceTransform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICBitmapSourceTransform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapSourceTransform::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapSourceTransform::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapSourceTransform::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICBitmapSourceTransform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICBitmapSourceTransform();
}



// Métodos da interface proprietária(ICarenWICBitmapSourceTransform)


/// <summary>
/// Copia os dados de pixels usando os parâmetros de entrada fornecidos.
/// Se NULO for passado para (Param_Retangulo), toda a imagem será copiada. Quando são solicitadas operações de transformação múltipla, o resultado depende da ordem 
/// em que as operações são realizadas. Para garantir previsibilidade e consistência entre os CODECs, é importante que todos os CODECs executem essas operações na mesma ordem.
/// A ordem recomendada dessas operações é: Escala -> Crop -> Flip/Rotate. A conversão do formato pixel pode ser realizada a qualquer momento, já que não tem efeito nas 
/// outras transformações.
/// </summary>
/// <param name="Param_Retangulo">O retângulo de pixels para copiar.</param>
/// <param name="Param_Width">A Largura para dimensionar o bitmap de origem. Este parâmetro deve ser igual ao valor obtido através do ICarenWICBitmapSourceTransform::GetClosestSize.</param>
/// <param name="Param_Height">A Altura para dimensionar o bitmap fonte. Este parâmetro deve ser igual ao valor obtido através do ICarenWICBitmapSourceTransform::GetClosestSize.</param>
/// <param name="Param_GuidFormatoDestino">O GUID do formato de pixel desejado no qual os pixels devem ser devolvidos. Este GUID deve ser um formato obtido através 
/// de uma chamada GetClosestPixelFormat.</param>
/// <param name="Param_TransformDestino">A rotação desejada ou o flip para executar antes da cópia dois pixels. A transformação deve ser uma operação suportada por 
/// uma chamada DoSupportTransform. Se um (Param_TransformDestino) for especificado, o 
/// (Param_Stride) é o stride transformado e é baseado no formato de pixel (Param_GuidFormatoDestino), não no formato de pixel da fonte original.</param>
/// <param name="Param_Stride">O Stride do Buffer de destino.</param>
/// <param name="Param_BufferSize">O tamanho do buffer de destino.</param>
/// <param name="Param_Buffer">O buffer de saída.</param>
CarenResult CarenWICBitmapSourceTransform::CopyPixels(
CA_WICRect^ Param_Retangulo,
UInt32 Param_Width,
UInt32 Param_Height,
String^ Param_GuidFormatoDestino,
CA_WICBitmapTransformOptions Param_TransformDestino,
UInt32 Param_Stride,
UInt32 Param_BufferSize,
ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRect* pRetangulo = NULL;
	GUID GuidFormatPixel = GUID_NULL;
	WICBitmapTransformOptions TransformOptions = static_cast<WICBitmapTransformOptions>(Param_TransformDestino);
	GenPointer pBufferSaida = DefaultGenPointer;

	//Converte a estrutura
	pRetangulo = Util.ConverterWICRectManaged_ToUnManaged(Param_Retangulo);

	//Converte a string com o formato do pixel
	GuidFormatPixel = Util.CreateGuidFromString(Param_GuidFormatoDestino);

	//Recupera o ponteiro para o buffer de saida.
	Resultado = Param_Buffer->GetInternalPointer(pBufferSaida);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPixels(
		pRetangulo, 
		Param_Width, 
		Param_Height, 
		&GuidFormatPixel, 
		TransformOptions, 
		Param_Stride, 
		Param_BufferSize, 
		Util.ConverterIntPtrTo<PBYTE>(pBufferSaida));

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
	DeletarEstruturaSafe(&pRetangulo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se uma opção de transformação específica é suportada nativamente pela implementação da interface ICarenWICBitmapSourceTransform. 
/// </summary>
/// <param name="Param_DestinoTransformacao">O WICBitmapTransformOptions para verificar se eles são suportados.</param>
/// <param name="Param_Out_Suporte">Retorna um valor especificando se a opção de transformação é suportada.</param>
CarenResult CarenWICBitmapSourceTransform::DoesSupportTransform(
CA_WICBitmapTransformOptions Param_DestinoTransformacao,
[Out] Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICBitmapTransformOptions TransformDestino = static_cast<WICBitmapTransformOptions>(Param_DestinoTransformacao);
	BOOL OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportTransform(TransformDestino, &OutSuporte);

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

	//Define o resultado no parametro de saida.
	Param_Out_Suporte = OutSuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o formato de pixel mais próximo ao qual a implementação do ICarenWICBitmapSourceTransform pode copiar nativamente pixels, dado o formato desejado. 
/// </summary>
/// <param name="Param_Ref_INOUT_DestinoGuidFormato">Na entrada, o formato do pixel desejado, na saida, retorna o formato do pixel suportado mais proximo do desejado.</param>
CarenResult CarenWICBitmapSourceTransform::GetClosestPixelFormat(String^% Param_Ref_INOUT_DestinoGuidFormato)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutInPixelFormat = GUID_NULL; //Tem valor na entrada e na saida.

	//Converte a string com o formato desejado.
	OutInPixelFormat = Util.CreateGuidFromString(Param_Ref_INOUT_DestinoGuidFormato);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetClosestPixelFormat(&OutInPixelFormat);

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

	//Define o resultado no parametro de saida.
	Param_Ref_INOUT_DestinoGuidFormato = Util.ConverterGuidToString(OutInPixelFormat);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna as dimensões mais próximas que a implementação pode escalar nativamente para dadas as dimensões desejadas. 
/// </summary>
/// <param name="Param_Ref_INOUT_Width">A Largura desejada. Retorna a Largura suportada mais próxima.</param>
/// <param name="Param_Ref_INOUT_Height">A Altura desejada. Retorna a Altura suportada mais próxima.</param>
CarenResult CarenWICBitmapSourceTransform::GetClosestSize(
UInt32% Param_Ref_INOUT_Width,
UInt32% Param_Ref_INOUT_Height)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 OutInWidth = Param_Ref_INOUT_Width; //Contém dados na entrada e saida.
	UINT32 OutInHeight = Param_Ref_INOUT_Height; //Contém dados na entrada e saida.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetClosestSize(&OutInWidth, &OutInHeight);

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

	//Define os dados nos parametros de saida.
	Param_Ref_INOUT_Width = OutInWidth;
	Param_Ref_INOUT_Height = OutInHeight;

Done:;
	//Retorna o resultado.
	return Resultado;
}