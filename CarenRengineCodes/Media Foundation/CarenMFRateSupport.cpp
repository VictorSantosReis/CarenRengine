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
#include "CarenMFRateSupport.h"


//Destruidor.
CarenMFRateSupport::~CarenMFRateSupport()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFRateSupport::CarenMFRateSupport()
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
CarenResult CarenMFRateSupport::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFRateSupport::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFRateSupport*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFRateSupport**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFRateSupport::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFRateSupport*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFRateSupport**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFRateSupport::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFRateSupport::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFRateSupport::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFRateSupport::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFRateSupport::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFRateSupport::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFRateSupport::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFRateSupport::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFRateSupport();
}



//
//Métodos da interface proprietaria.
//

/// <summary>
/// (GetFastestRate) - Obtém a taxa de reprodução mais rápida suportada pelo objeto.
/// </summary>
/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução de encaminhamento mais rápida ou a taxa de reprodução inversa.</param>
/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução mais rápida diluído. Caso contrário, o método recupera o mais rápido não-diluído taxa de reprodução. 
/// Para alguns formatos (como ASF), desbaste significa descartar todos os quadros que não são I-frames. Se um componente produz dados de fluxo, como uma fonte de mídia ou um 
/// demultiplexer, ele deve prestar atenção para o (Param_Thin) parâmetro e retornar MF_E_THINNING_UNSUPPORTED se ele não é possível Thin o fluxo.</param>
/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais rápida que o objeto oferece suporte.</param>
CarenResult CarenMFRateSupport::GetFastestRate(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	_MFRATE_DIRECTION Direction = static_cast<_MFRATE_DIRECTION>(Param_Diracao);
	float MaxiTaxaReproducao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFastestRate(Direction, Param_Thin, &MaxiTaxaReproducao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_TaxaReproducao = MaxiTaxaReproducao;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetSlowestRate) - Recupera a taxa de reprodução mais lenta suportada pelo objeto.
/// </summary>
/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução direta mais lenta ou a taxa de reprodução inversa.</param>
/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução diluído mais lenta. Caso contrário, o método recupera a taxa de reprodução mais lenta não Diluível. 
/// O valor retornado em Plfrate representa um limite inferior. A reprodução a esta taxa não é garantida. Chame ICarenMFRateSupport::SuporteTaxa para verificar se a taxa de limite 
/// é suportado. Por exemplo, um componente que ofereça suporte a taxas arbitrariamente lentas retornará zero em (Param_Out_TaxaReproducao), e os aplicativos devem chamar 
/// (SuporteTaxa) separadamente para determinar se o componente oferece suporte à taxa 0.</param>
/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais lenta que o objeto oferece suporte.</param>
CarenResult CarenMFRateSupport::GetSlowestRate(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	_MFRATE_DIRECTION Direction = static_cast<_MFRATE_DIRECTION>(Param_Diracao);
	float MaxiTaxaReproducao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSlowestRate(Direction, Param_Thin, &MaxiTaxaReproducao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_TaxaReproducao = MaxiTaxaReproducao;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsRateSupported) - Consulta se o objeto oferece suporte a uma taxa de reprodução especificada.
/// </summary>
/// <param name="Param_Thin">Se true, o método consulta se o objeto oferece suporte a taxa de reprodução com desbaste. Caso contrário, o método consultará se o objeto suporta a taxa de 
/// reprodução sem desbaste.</param>
/// <param name="Param_Taxa">A taxa de reprodução para consulta.</param>
/// <param name="Param_Out_TaxaSuportada">Se o objeto não suportar a taxa de reprodução fornecida em (Param_Taxa), esse parâmetro receberá a taxa de reprodução suportada mais próxima. 
/// Se o método retorna SS_OK, esse parâmetro recebe o valor fornecido em (Param_Taxa).</param>
CarenResult CarenMFRateSupport::IsRateSupported(Boolean Param_Thin, float Param_Taxa, [Out] float% Param_Out_TaxaSuportada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	float TaxaReproducao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsRateSupported(Param_Thin, Param_Taxa, &TaxaReproducao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_TaxaSuportada = TaxaReproducao;

Done:;
	//Retorna o resultado.
	return Resultado;
}