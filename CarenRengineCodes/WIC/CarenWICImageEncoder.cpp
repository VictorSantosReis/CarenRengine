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
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICImageEncoder::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICImageEncoder*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICImageEncoder**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICImageEncoder::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICImageEncoder*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICImageEncoder**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICImageEncoder::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICImageEncoder::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICImageEncoder::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICImageEncoder::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICImageEncoder::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICImageEncoder::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
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

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pWicParameters);

	//Retorna o resultado.
	return Resultado;
}