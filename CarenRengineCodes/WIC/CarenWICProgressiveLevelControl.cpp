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
#include "CarenWICProgressiveLevelControl.h"

//Destruidor.
CarenWICProgressiveLevelControl::~CarenWICProgressiveLevelControl()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICProgressiveLevelControl::CarenWICProgressiveLevelControl()
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
CarenResult CarenWICProgressiveLevelControl::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICProgressiveLevelControl::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICProgressiveLevelControl*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICProgressiveLevelControl**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICProgressiveLevelControl::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICProgressiveLevelControl*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICProgressiveLevelControl**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICProgressiveLevelControl::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICProgressiveLevelControl::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICProgressiveLevelControl::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICProgressiveLevelControl::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICProgressiveLevelControl::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICProgressiveLevelControl::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICProgressiveLevelControl::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICProgressiveLevelControl();
}



// Métodos da interface proprietária(ICarenWICProgressiveLevelControl)


/// <summary>
/// Obtém o nível progressivo atual do decodificador. O nível sempre é padrão para o mais alto nível progressivo. Para decodificar um nível progressivo mais baixo, o SetCurrentLevel deve primeiro ser chamado.
/// </summary>
/// <param name="Param_Out_LevelAtual">Retorna o nível atual especificado.</param>
CarenResult CarenWICProgressiveLevelControl::GetCurrentLevel([Out] UInt32% Param_Out_LevelAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutLevelAtual = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentLevel(&vi_OutLevelAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o no parametro de saida.
	Param_Out_LevelAtual = vi_OutLevelAtual;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de níveis de decodificação progressiva suportado pelo CODEC.
/// Os usuários não devem usar essa função para iterar através dos níveis progressivos de uma imagem JPEG progressiva. Os níveis progressivos jpeg são determinados pela imagem e não têm uma 
/// contagem de nível fixo. O uso deste método forçará o aplicativo a esperar que todos os níveis progressivos sejam baixados antes que ele possa retornar. Em vez disso, os aplicativos devem 
/// usar o seguinte código para iterar através dos níveis progressivos de uma imagem JPEG progressiva.
/// </summary>
/// <param name="Param_Out_QuantLeveis">Retorna o número de níveis suportados pelo CODEC.</param>
CarenResult CarenWICProgressiveLevelControl::GetLevelCount([Out] UInt32% Param_Out_QuantLeveis)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutLevelCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetLevelCount(&vi_OutLevelCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_QuantLeveis = vi_OutLevelCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica o nível a ser recuperado na próxima chamada para ICarenWICBitmapSource::CopyPixels.
/// Uma chamada não precisa solicitar todos os níveis suportados. Se um chamador solicitar o nível 1, sem ter solicitado anteriormente o nível 0, os bits retornados pela próxima chamada para 
/// CopyPixels incluirão ambos os níveis.
/// Os usuários devem usar esse método para iterar através dos níveis progressivos de uma imagem JPEG progressiva em vez do método GetCurrentLevel. Os níveis progressivos jpeg são determinados 
/// pela imagem e não têm uma contagem de nível fixo. O uso do método GetCurrentLevel forçará o aplicativo a esperar que todos os níveis progressivos sejam baixados antes que ele possa retornar. 
/// Em vez disso, os aplicativos devem usar o seguinte código para iterar através dos níveis progressivos de uma imagem JPEG progressiva.
/// Se o nível solicitado for inválido, o erro devolvido será ER_WINCODEC_ERR_INVALIDPROGRESSIVELEVEL.
/// </summary>
/// <param name="Param_Level">Especifica qual nível retornará em seguida. Se for maior do que o número total de níveis suportados, um erro será devolvido.</param>
CarenResult CarenWICProgressiveLevelControl::SetCurrentLevel(UInt32 Param_Level)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentLevel(Param_Level);

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