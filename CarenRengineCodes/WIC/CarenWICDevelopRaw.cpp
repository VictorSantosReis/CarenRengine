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
#include "CarenWICDevelopRaw.h"

//Destruidor.
CarenWICDevelopRaw::~CarenWICDevelopRaw()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICDevelopRaw::CarenWICDevelopRaw()
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
CarenResult CarenWICDevelopRaw::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDevelopRaw::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDevelopRaw*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDevelopRaw**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDevelopRaw::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDevelopRaw*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDevelopRaw**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDevelopRaw::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDevelopRaw::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICDevelopRaw::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICDevelopRaw::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICDevelopRaw::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICDevelopRaw::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICDevelopRaw::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICDevelopRaw::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICDevelopRaw();
}



// Métodos da interface proprietária(ICarenWICDevelopRaw)


/// <summary>
/// Obtém o valor de contraste da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Contraste">Retorna o valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. 
/// O limite inferior de 0,0 não representa nenhum contraste aplicado à imagem, 
/// enquanto o limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::GetContrast([Out] double% Param_Out_Contraste)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutContraste = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContrast(&vi_OutContraste);

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

	//Define no parametro de saida.
	Param_Out_Contraste = vi_OutContraste;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o conjunto atual de parâmetros.
/// </summary>
/// <param name="Param_Out_ParametrosAtuais">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a bag que contém o conjunto atual de parametros.</param>
CarenResult CarenWICDevelopRaw::GetCurrentParameterSet([Out] ICarenPropertyBag2^% Param_Out_ParametrosAtuais)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IPropertyBag2* vi_OutBag2;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentParameterSet(&vi_OutBag2);

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

	//Cria a interface a ser retornada.
	Param_Out_ParametrosAtuais = gcnew CarenPropertyBag2();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_OutBag2, Param_Out_ParametrosAtuais, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a compensação de exposição parar o valor da imagem bruta. 
/// </summary>
/// <param name="Param_Out_EV">Retorna o valor de parada de compensação de exposição. O padrão é a configuração "as-shot".</param>
CarenResult CarenWICDevelopRaw::GetExposureCompensation([Out] double% Param_Out_EV)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutEv = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetExposureCompensation(&vi_OutEv);

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

	//Define no parametro de saida.
	Param_Out_EV = vi_OutEv;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a configuração gama atual da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Gamma">Retorna o valor da configuração gama atual.</param>
CarenResult CarenWICDevelopRaw::GetGamma([Out] double% Param_Out_Gamma)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutGamma = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGamma(&vi_OutGamma);

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

	//Define no parametro de saida.
	Param_Out_Gamma = vi_OutGamma;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a informação sobre a atual gama Kelvin da imagem bruta. 
/// </summary>
/// <param name="Param_Out_MinKelvinTemp">Retorna a temperatura mínima de Kelvin.</param>
/// <param name="Param_Out_MaxKelvinTemp">Retorna a temperatura máxima de Kelvin.</param>
/// <param name="Param_Out_KelvinTempStepValue">Retorna a temperatura do Kelvin Step.</param>
CarenResult CarenWICDevelopRaw::GetKelvinRangeInfo(
[Out] UInt32% Param_Out_MinKelvinTemp,
[Out] UInt32% Param_Out_MaxKelvinTemp,
[Out] UInt32% Param_Out_KelvinTempStepValue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT vi_OutMinkelvin, vi_OutMaxKelvin, vi_OutKelvinTempStep = 0;
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetKelvinRangeInfo(&vi_OutMinkelvin, &vi_OutMaxKelvin, &vi_OutKelvinTempStep);

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

	//Define os dados no parametro.
	Param_Out_MinKelvinTemp = vi_OutMinkelvin;
	Param_Out_MaxKelvinTemp = vi_OutMaxKelvin;
	Param_Out_KelvinTempStepValue = vi_OutKelvinTempStep;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o ponto branco da imagem bruta. Se os pontos brancos nomeados não forem suportados pela imagem bruta ou o arquivo bruto contiver pontos brancos nomeados que não 
/// são suportados por esta API, o implementador codec ainda deve marcar essa capacidade como suportada. Se os pontos brancos nomeados não forem suportados pela imagem bruta, 
/// um esforço melhor deve ser feito para ajustar a imagem ao ponto branco nomeado, mesmo quando não é um ponto branco pré-definido do arquivo bruto.
/// Se o arquivo bruto contiver pontos brancos nomeados não suportados por esta API, o implementador codec deverá suportar os pontos brancos nomeados no CA_WICNamedWhitePoint.
/// </summary>
/// <param name="Param_Out_WhitePoint">Retorna a combinação bitwise dos valores de enumeração.</param>
CarenResult CarenWICDevelopRaw::GetNamedWhitePoint([Out] CA_WICNamedWhitePoint% Param_Out_WhitePoint)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICNamedWhitePoint vi_OutNamedPoint;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNamedWhitePoint(&vi_OutNamedPoint);

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

	//Converte e define no parametro de saida.
	Param_Out_WhitePoint = static_cast<CA_WICNamedWhitePoint>(vi_OutNamedPoint);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor de redução de ruído da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Noise">Retorna o valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para 
/// redução de ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa 
/// redução de ruído aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::GetNoiseReduction([Out] double% Param_Out_Noise)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutNoise = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNoiseReduction(&vi_OutNoise);

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

	//Deine no parametro de saida.
	Param_Out_Noise = vi_OutNoise;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o CA_WICRawRenderMode atual. 
/// </summary>
/// <param name="Param_Out_ModoRender">Recebe uma enumeração que define o modo de renderização atual.</param>
CarenResult CarenWICDevelopRaw::GetRenderMode([Out] CA_WICRawRenderMode% Param_Out_ModoRender)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICRawRenderMode vi_OutRenderMode;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRenderMode(&vi_OutRenderMode);

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

	//Converte e define no parametro de saida.
	Param_Out_ModoRender = static_cast<CA_WICRawRenderMode>(vi_OutRenderMode);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o ângulo de rotação atual. 
/// </summary>
/// <param name="Param_Out_Rotacao">Retorna o ângulo de rotação atual.</param>
CarenResult CarenWICDevelopRaw::GetRotation([Out] double% Param_Out_Rotacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutRotacao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRotation(&vi_OutRotacao);

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

	//Deine no parametro de saida.
	Param_Out_Rotacao = vi_OutRotacao;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor de saturação da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Saturacao">Retorna o valor de saturação da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para saturação é de 0,0 a 1,0. 
/// Um valor de 0.0 representa uma imagem com uma imagem totalmente desaturada, 
/// enquanto um valor de 1.0 representa a maior quantidade de saturação que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::GetSaturation([Out] double% Param_Out_Saturacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutSaturacao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSaturation(&vi_OutSaturacao);

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

	//Deine no parametro de saida.
	Param_Out_Saturacao = vi_OutSaturacao;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor de nitidez da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Shapness">Retorna o valor de nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0.
///  O limite inferior de 0,0 não representa nenhum nitidez aplicado à imagem, enquanto 
/// o limite superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::GetSharpness([Out] double% Param_Out_Shapness)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutShapness = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSharpness(&vi_OutShapness);

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

	//Deine no parametro de saida.
	Param_Out_Shapness = vi_OutShapness;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor da tonalidade da imagem bruta. 
/// </summary>
/// <param name="Param_Out_Tint">Retorna o valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez 
/// é de -1,0 a +1,0. O limite inferior de -1,0 representa um viés verde completo 
/// para a imagem, enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
CarenResult CarenWICDevelopRaw::GetTint([Out] double% Param_Out_Tint)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutTint = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTint(&vi_OutTint);

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

	//Deine no parametro de saida.
	Param_Out_Tint = vi_OutTint;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a curva de tom da imagem bruta. 
/// </summary>
/// <param name="Param_ToneCurveBufferSize">O tamanho da estrutura (Param_Ref_ToneCurve).</param>
/// <param name="Param_Ref_ToneCurve">Retorna uma estrutura (CA_WICRawToneCurve) da imagem bruta. Define esse valor para NULO para obter o tamanho necessário para (Param_ToneCurveBufferSize).</param>
/// <param name="Param_Out_ToneCurveBufferSizeAtual">Retorna o tamanho necessário para retornar a estrutura (Param_Ref_ToneCurve).</param>
CarenResult CarenWICDevelopRaw::GetToneCurve(
UInt32 Param_ToneCurveBufferSize,
CA_WICRawToneCurve^% Param_Ref_ToneCurve,
[Out] UInt32% Param_Out_ToneCurveBufferSizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRawToneCurve vi_OutWicToneCurve = {};
	UINT vi_OutToneCurveBufferSize = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetToneCurve(Param_ToneCurveBufferSize, ObjetoGerenciadoValido(Param_Ref_ToneCurve)? &vi_OutWicToneCurve: Nulo, &vi_OutToneCurveBufferSize);

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

	//Define a estrutura se valida
	if (ObjetoGerenciadoValido(Param_Ref_ToneCurve))
		Param_Ref_ToneCurve = Util.ConverterWICRawToneCurveUnmanaged_ToManaged(&vi_OutWicToneCurve);

	//Define a largura da estrutura atual.
	Param_Out_ToneCurveBufferSizeAtual = vi_OutToneCurveBufferSize;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a temperatura Kelvin do ponto branco da imagem bruta.
/// </summary>
/// <param name="Param_Out_WhitePointKelvin">Retorna o valor da temperatura Kelvin do ponto branco da imagem bruta. O padrão é o valor de configuração "as-shot".</param>
CarenResult CarenWICDevelopRaw::GetWhitePointKelvin([Out] UInt32% Param_Out_WhitePointKelvin)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT vi_OutWhitePoint = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWhitePointKelvin(&vi_OutWhitePoint);

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

	//Define no parametro de saida.
	Param_Out_WhitePointKelvin = vi_OutWhitePoint;
	
Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os valores RGB do ponto branco. 
/// </summary>
/// <param name="Param_Out_Red">Retorna o valor do ponto branco vermelho.</param>
/// <param name="Param_Out_Green">Retorna o valor do ponto branco verde.</param>
/// <param name="Param_Out_Blue">Retorna o valor do ponto branco azul.</param>
CarenResult CarenWICDevelopRaw::GetWhitePointRGB(
[Out] UInt32% Param_Out_Red,
[Out] UInt32% Param_Out_Green,
[Out] UInt32% Param_Out_Blue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT vi_OutRed, vi_OutGreen, vi_OutBlue = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWhitePointRGB(&vi_OutRed, &vi_OutGreen, &vi_OutBlue);

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

	//Define nos parametros de saida.
	Param_Out_Red = vi_OutRed;
	Param_Out_Green = vi_OutGreen;
	Param_Out_Blue = vi_OutBlue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define a opção CA_WICRawParameterSet desejada. 
/// </summary>
/// <param name="Param_Parametros">Uma valor da opção(CA_WICRawParameterSet) a ser definido.</param>
CarenResult CarenWICDevelopRaw::LoadParameterSet(CA_WICRawParameterSet Param_Parametros)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadParameterSet(static_cast<WICRawParameterSet>(Param_Parametros));

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
/// Recupera informações sobre quais recursos são suportados para uma imagem bruta. 
/// Recomenda-se que um codec informe que uma capacidade é suportada mesmo que os resultados nos limites de alcance externo não sejam de perfeita qualidade.
/// </summary>
/// <param name="Param_Out_Info">Retorna uma estrutura (CA_WICRawCapabilitiesInfo) que fornece os recursos suportados pela imagem bruta.</param>
CarenResult CarenWICDevelopRaw::QueryRawCapabilitiesInfo([Out] CA_WICRawCapabilitiesInfo^% Param_Out_Info)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRawCapabilitiesInfo vi_OutRawInfo = {  };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueryRawCapabilitiesInfo(&vi_OutRawInfo);

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

	//Converte e define no parametro de saida.
	Param_Out_Info = Util.ConverterWICRawCapabilitiesInfoUnmanaged_ToManaged(&vi_OutRawInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o valor de contraste da imagem bruta. O implementador codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
/// rotinas de processamento de imagem.
/// </summary>
/// <param name="Param_Contraste">O valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. O limite 
/// inferior de 0,0 não representa nenhum contraste aplicado à imagem, enquanto o 
/// limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::SetContrast(double Param_Contraste)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetContrast(Param_Contraste);

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
/// Define o contexto de cores do destino. 
/// </summary>
/// <param name="Param_ColorContext">O contexto de cores do destino.</param>
CarenResult CarenWICDevelopRaw::SetDestinationColorContext(ICarenWICColorContext^ Param_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext* vi_pWicColor = Nulo;

	//Recupera o ponteiro para o contexto de cor.
	CarenGetPointerFromICarenSafe(Param_ColorContext, vi_pWicColor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDestinationColorContext(vi_pWicColor);

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
/// Define o valor de parada da compensação de exposição. Recomenda - se que um codec informe que esse método é compatível, mesmo se os resultados nos limites da faixa externa 
/// não forem de qualidade perfeita.
/// </summary>
/// <param name="Param_EV">O valor de compensação da exposição.O intervalo de valores para compensação de exposição é de - 5, 0 a + 5, 0, o que equivale a 10 pontos finais.</param>
CarenResult CarenWICDevelopRaw::SetExposureCompensation(double Param_EV)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetExposureCompensation(Param_EV);

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
/// Define o valor gama desejado. 
/// </summary>
/// <param name="Param_Gamma">O valor gama desejado.</param>
CarenResult CarenWICDevelopRaw::SetGamma(double Param_Gamma)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGamma(Param_Gamma);

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
/// Define o ponto branco nomeado do arquivo bruto. 
/// </summary>
/// <param name="Param_WhitePoint">Uma combinação bitwise dos valores de enumeração.</param>
CarenResult CarenWICDevelopRaw::SetNamedWhitePoint(CA_WICNamedWhitePoint Param_WhitePoint)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetNamedWhitePoint(static_cast<WICNamedWhitePoint>(Param_WhitePoint));

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
/// Define o valor de redução de ruído da imagem bruta. O implementador do codec deve determinar o que o valor do intervalo superior representa e deve determinar como mapear o 
/// valor para suas rotinas de processamento de imagem.
/// </summary>
/// <param name="Param_Noise">O valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para redução de
///  ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa redução de ruído 
/// aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::SetNoiseReduction(double Param_Noise)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetNoiseReduction(Param_Noise);

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
/// Define o método de retorno de chamada de notificação. 
/// </summary>
/// <param name="Param_NotificationCallback">Uma interface de callback que vai receber as notificações.</param>
CarenResult CarenWICDevelopRaw::SetNotificationCallback(ICarenWICDevelopRawNotificationCallback^ Param_NotificationCallback)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICDevelopRawNotificationCallback* vi_pRawNotifyCallback = Nulo;

	//Recupera o ponteiro para o Callback
	CarenGetPointerFromICarenSafe(Param_NotificationCallback, vi_pRawNotifyCallback);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetNotificationCallback(vi_pRawNotifyCallback);

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
/// Define o WICRawRenderMode atual. 
/// </summary>
/// <param name="Param_ModoRender">O modo renderização a ser usado.</param>
CarenResult CarenWICDevelopRaw::SetRenderMode(CA_WICRawRenderMode Param_ModoRender)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRenderMode(static_cast<WICRawRenderMode>(Param_ModoRender));

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
/// Define o ângulo de rotação desejado. 
/// </summary>
/// <param name="Param_Rotacao">O ângulo de rotação desejado.</param>
CarenResult CarenWICDevelopRaw::SetRotation(double Param_Rotacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRotation(Param_Rotacao);

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
/// Define o valor de saturação da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor 
/// para suas rotinas de processamento de imagem.
/// </summary>
/// <param name="Param_Saturacao">O valor de saturação da imagem bruta. A faixa de valor para saturação é de 0,0 a 1,0. Um valor de 0.0 representa uma imagem com uma imagem 
/// totalmente desaturada, enquanto um valor de 1.0 representa a maior quantidade 
/// de saturação que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::SetSaturation(double Param_Saturacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSaturation(Param_Saturacao);

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
/// Define o valor de nitidez da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
/// rotinas de processamento de imagem.
/// </summary>
/// <param name="Param_Sharpness">O valor da nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0. O limite inferior de 
/// 0,0 não representa nenhum nitidez aplicado à imagem, enquanto o limite 
/// superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
CarenResult CarenWICDevelopRaw::SetSharpness(double Param_Sharpness)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSharpness(Param_Sharpness);

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
/// Define o valor da tonalidade da imagem bruta. O implementador do codec deve determinar quais são os valores de alcance externo e deve determinar como mapear os valores para suas 
/// rotinas de processamento de imagem.
/// </summary>
/// <param name="Param_Tint">O valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez é de -1,0 a +1,0. 
/// O limite inferior de -1,0 representa um viés verde completo para a imagem, 
/// enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
CarenResult CarenWICDevelopRaw::SetTint(double Param_Tint)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTint(Param_Tint);

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
/// Define a curva de tom para a imagem bruta. 
/// </summary>
/// <param name="Param_ToneCurveSizeStruct">O tamanho da estrutura (Param_ToneCurve).</param>
/// <param name="Param_ToneCurve">A curva de tom desejada.</param>
CarenResult CarenWICDevelopRaw::SetToneCurve(
UInt32 Param_ToneCurveSizeStruct,
CA_WICRawToneCurve^ Param_ToneCurve)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRawToneCurve* vi_ToneCurve = Nulo;

	//Converte a estrutura.
	vi_ToneCurve = Util.ConverterWICRawToneCurveManaged_ToUnmanaged(Param_ToneCurve);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetToneCurve(Param_ToneCurveSizeStruct, vi_ToneCurve);

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
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&vi_ToneCurve);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o valor do ponto branco kelvin. Os implementadores de codec devem ajustar fielmente a temperatura de cor dentro da faixa suportada nativamente pela imagem bruta. Para valores 
/// fora da faixa de suporte nativa, o implementador codec deve fornecer uma representação de melhor esforço da imagem a essa temperatura de cor.
/// Os implementadores de codec devem retornar WINCODEC_ERR_VALUEOUTOFRANGE se o valor estiver fora do intervalo aceitável definido.
/// </summary>
/// <param name="Param_WhitePointKelvin">O valor do ponto branco kelvin. Os valores aceitáveis de Kelvin são de 1.500 a 30.000.</param>
CarenResult CarenWICDevelopRaw::SetWhitePointKelvin(UInt32 Param_WhitePointKelvin)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetWhitePointKelvin(Param_WhitePointKelvin);

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
/// Define os valores RGB de ponto branco. Devido a outros métodos de configuração de ponto branco(por exemplo, SetWhitePointKelvin), deve - se tomar cuidado pelos implementadores 
/// de codec para garantir a interoperabilidade adequada.Por exemplo, se o chamador define por meio de um ponto branco nomeado, o implementador do codec pode desabilitar a leitura 
/// da temperatura Kelvin correspondente.Em casos específicos em que o implementador do codec deseja negar uma determinada ação por causa de chamadas anteriores, 
/// WINCODEC_ERR_WRONGSTATE deve ser retornado.
/// </summary>
/// <param name="Param_Red">O valor do ponto branco vermelho.</param>
/// <param name="Param_Green">O valor verde do ponto branco.</param>
/// <param name="Param_Blue">O valor do ponto branco azul.</param>
CarenResult CarenWICDevelopRaw::SetWhitePointRGB(
UInt32 Param_Red,
UInt32 Param_Green,
UInt32 Param_Blue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetWhitePointRGB(Param_Red, Param_Green, Param_Blue);

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




// Métodos da interface (ICarenWICBitmapFrameDecode)


/// <summary>
/// Recupera o ICarenWICColorContext associado ao frame de imagem.
/// Se NULO for definido para (Param_Ref_ColorContexts), e 0 for para (Param_Quantidade), este método retornará o número total de contextos de cores na imagem no (Param_Out_TamanhoArrayAtual).
/// </summary>
/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
/// <param name="Param_Ref_ColorContexts">Uma matriz que recebe ponteiros para a interface(ICarenWICColorContext).</param>
/// <param name="Param_Out_TamanhoArrayAtual">Recebe o número de contextos de cores retornados na matriz (Param_Ref_ColorContexts).</param>
CarenResult CarenWICDevelopRaw::GetColorContexts(
	UInt32 Param_Quantidade,
	cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
	[Out] UInt32% Param_Out_TamanhoArrayAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext** pOutArrayColorContexts = NULL; //Pode ser NULO para o usuário obter a quantidade necessária para resgatar as interfaces.
	UINT32 OutTamanhoArrayAtual = 0;

	//Verifica se o usuário informou o array.
	if (ObjetoGerenciadoValido(Param_Ref_ColorContexts))
	{
		//Cria a matriz de interfaces
		pOutArrayColorContexts = CriarMatrizPonteiros<IWICColorContext>(Param_Quantidade);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorContexts(Param_Quantidade, pOutArrayColorContexts == NULL ? NULL : pOutArrayColorContexts, &OutTamanhoArrayAtual);

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

	//Verifica se o array de interfaces é valido e define os dados.
	if (ObjetoValido(pOutArrayColorContexts))
	{
		//Abre um for para criar as interfaces e definir os ponteiros.
		for (UINT32 i = 0; i < OutTamanhoArrayAtual; i++)
		{
			//Cria a interface no index.
			Param_Ref_ColorContexts[i] = gcnew CarenWICColorContext();

			//Define o ponteiro na interface
			DefinirPonteiroInterface(pOutArrayColorContexts[i], Param_Ref_ColorContexts[i]);
		}
	}

	//Define a quantidade de dados no array.
	Param_Out_TamanhoArrayAtual = OutTamanhoArrayAtual;

Done:;
	//Libera a memória utilizada pelo array de interfaces.
	DeletarMatrizPonteirosSafe(&pOutArrayColorContexts);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um leitor de consulta de metadados para o frame.
/// Para formatos de imagem com um frame (JPG, PNG, JPEG-XR), o leitor de consulta de nível de frame do primeiro frame é usado para acessar todos os metadados de imagem, 
/// e o leitor de consulta de nível de decodificador não é usado. Para formatos com mais de um frames (GIF, TIFF), o leitor de consulta de nível de frame para um determinado 
/// frame é usado para acessar metadados específicos desse frame, e no caso de GIF um leitor de metadados de nível de decodificador estará presente. Se o decodificador não suportar 
/// metadados (BMP, ICO), isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
/// </summary>
/// <param name="Param_Out_MetadataReader">Retorna a interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o leitor de consulta de metadados do frame.</param>
CarenResult CarenWICDevelopRaw::GetMetadataQueryReader(
	[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataQueryReader* pOutMetadaReader = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataQueryReader(&pOutMetadaReader);

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

	//Cria a interface a ser retornada.
	Param_Out_MetadataReader = gcnew CarenWICMetadataQueryReader();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutMetadaReader, Param_Out_MetadataReader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma pequena visualização do frame, se suportado pelo codec.
/// </summary>
/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) que contém um ponteiro para o objeto miniatura.</param>
CarenResult CarenWICDevelopRaw::GetThumbnail(
	[Out] ICarenWICBitmapSource^% Param_Out_Thumbnail)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pOutBitmapSource = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetThumbnail(&pOutBitmapSource);

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

	//Cria a interface a ser retornada.
	Param_Out_Thumbnail = gcnew CarenWICBitmapSource();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutBitmapSource, Param_Out_Thumbnail);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICBitmapSource)


/// <summary>
/// Recupera a tabela de cores para formatos de pixel indexados. 
/// </summary>
/// <param name="Param_Palette">Uma ICarenWICPalette. Uma paleta pode ser criada usando o método ICarenWICImagingFactory::CreatePalette.</param>
CarenResult CarenWICDevelopRaw::CopyPalette(ICaren^ Param_Palette)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* pPaleta = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Palette, &pPaleta);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPalette(pPaleta);

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
/// Instrui o objeto a produzir pixels. CopyPixels é uma das duas principais rotinas de processamento de imagens(a outra é Lock), acionando o processamento real.Ele instrui o 
/// objeto a produzir pixels de acordo com seu algoritmo - isso pode envolver a decodificação de uma parte de um JPEG armazenado em disco, a cópia de um bloco de memória ou a 
/// computação analítica de um gradiente complexo.O algoritmo é completamente dependente do objeto que implementa a interface.
/// </summary>
/// <param name="Param_RetanguloCopy">O retângulo para copiar. Um valor NULO especifica todo o bitmap.</param>
/// <param name="Param_Stride">O Stride do bitmap</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer.</param>
/// <param name="Param_Buffer">Um ponteiro para o buffer.</param>
CarenResult CarenWICDevelopRaw::CopyPixels(
	CA_WICRect^ Param_RetanguloCopy,
	UInt32 Param_Stride,
	UInt32 Param_TamanhoBuffer,
	ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRect* pRetanguloCopy = NULL; //Pode ser NULO.
	GenPointer pBufferDados = DefaultGenPointer;

	//Converte a estrutura se tiver sido informada.
	pRetanguloCopy = ObjetoGerenciadoValido(Param_RetanguloCopy) ? Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloCopy) : NULL;

	//Recupera o ponteiro para o buffer
	Resultado = Param_Buffer->GetInternalPointer(pBufferDados);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPixels(pRetanguloCopy, Param_Stride, Param_TamanhoBuffer, Util.ConverterIntPtrTo<PBYTE>(pBufferDados));

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
/// Recupera o formato de pixel da fonte bitmap. O formato de pixel retornado por este método não é necessariamente o formato de pixel que a imagem é armazenada como. O codec pode 
/// executar uma conversão de formato do formato pixel de armazenamento para um formato de pixel de saída.
/// </summary>
/// <param name="Param_Out_FormatoPixel">Recebe o GUID do formato de pixel em que o bitmap está armazenado.</param>
CarenResult CarenWICDevelopRaw::GetPixelFormat([Out] String^% Param_Out_FormatoPixel)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidFormatPixel = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPixelFormat(&OutGuidFormatPixel);

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

	//Converte o GUID para string e define no parametro de saida.
	Param_Out_FormatoPixel = Util.ConverterGuidToString(OutGuidFormatPixel);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a taxa de amostragem entre pixels e medições do mundo físico. 
/// Alguns formatos, como GIF e ICO, não possuem suporte completo ao DPI. Para GIF, este método calcula os valores de DPI a partir da proporção, utilizando um DPI base de (96,0, 96,0).
///  O formato ICO não suporta DPI em tudo, e o método sempre retorna (96.0.96.0) para imagens de ICO. Além disso, o próprio WIC não transforma imagens com base nos valores de DPI em uma 
/// imagem. Cabe ao interlocutor transformar uma imagem baseada na resolução devolvida.
/// </summary>
/// <param name="Param_Out_DpiX">Recebe a resolução dpi do eixo X.</param>
/// <param name="Param_Out_DpiY">Recebe a resolução dpi do eixo Y.</param>
CarenResult CarenWICDevelopRaw::GetResolution(
	[Out] double% Param_Out_DpiX,
	[Out] double% Param_Out_DpiY)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DOUBLE OutDpiX = 0;
	DOUBLE OutDpiY = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetResolution(&OutDpiX, &OutDpiY);

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
	Param_Out_DpiX = OutDpiX;
	Param_Out_DpiY = OutDpiY;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a largura e a altura do bitmap. 
/// </summary>
/// <param name="Param_Out_PixelWidthBitmap">Recebe a Largura do pixel do bitmap.</param>
/// <param name="Param_Out_PixelHeightBitmap">Recebe a Altura do pixel do bitmap.</param>
CarenResult CarenWICDevelopRaw::GetSize(
	[Out] UInt32% Param_Out_PixelWidthBitmap,
	[Out] UInt32% Param_Out_PixelHeightBitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32 OutPixelWidthBitmap = 0;
	UINT32 OutPixelHeightBitmap = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSize(&OutPixelWidthBitmap, &OutPixelHeightBitmap);

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
	Param_Out_PixelWidthBitmap = OutPixelWidthBitmap;
	Param_Out_PixelHeightBitmap = OutPixelHeightBitmap;

Done:;
	//Retorna o resultado.
	return Resultado;
}