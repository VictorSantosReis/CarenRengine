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
#include "CarenD2D1ImageSourceFromWic.h"

//Destruidor.
CarenD2D1ImageSourceFromWic::~CarenD2D1ImageSourceFromWic()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1ImageSourceFromWic::CarenD2D1ImageSourceFromWic()
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
CarenResult CarenD2D1ImageSourceFromWic::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ImageSourceFromWic::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ImageSourceFromWic*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ImageSourceFromWic**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ImageSourceFromWic::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ImageSourceFromWic*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ImageSourceFromWic**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ImageSourceFromWic::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ImageSourceFromWic::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1ImageSourceFromWic::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1ImageSourceFromWic::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1ImageSourceFromWic::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1ImageSourceFromWic::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1ImageSourceFromWic::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1ImageSourceFromWic();
}



// Métodos da interface proprietária(ICarenD2D1ImageSourceFromWic)


/// <summary>
/// Garante que uma região especificada do cache de origem da imagem seja preenchida. Este método pode ser usado para minimizar falhas realizando trabalhos caros para preencher caches fora de um loop de renderização. 
/// Este método também pode ser usado para carregar especulativamente dados de imagem antes de serem necessários por meio do desenho de rotinas.
/// </summary>
/// <param name="Param_RegiaoRetangulo">Especifica a região da imagem, em pixels, que deve ser preenchida no cache. Por padrão, esta é toda a extensão da imagem.</param>
CarenResult CarenD2D1ImageSourceFromWic::EnsureCached(CA_D2D1_RECT_U^ Param_RegiaoRetangulo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_U* pRect = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pRect = Util.ConverterD2D1_RECT_UManagedToUnmanaged(Param_RegiaoRetangulo);

	//Verifica se converteu com sucesso
	if (!ObjetoValido(pRect))
	{
		//Falhou ao converter a estrutura.

		//Define falha de conversão de estrutura.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_ESTRUTURA, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnsureCached(pRect);

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
	//Libera a memória para a matriz.
	DeletarEstruturaSafe(&pRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a fonte de imagem do bitmap subjacente do Componente de Imagem do Windows (WIC).
/// </summary>
/// <param name="Param_Out_WicBitmapSource">Retorna um ponteiro para a interface (ICarenWICBitmapSource) que representa a fonte do bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1ImageSourceFromWic::GetSource(ICaren^ Param_Out_WicBitmapSource)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource* pWicBitmapSource = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetSource(&pWicBitmapSource);

	//Verifica se a interface é valida
	if (!ObjetoValido(pWicBitmapSource))
		Sair;

	//Define o ponteiro na interface de saida.
	Param_Out_WicBitmapSource->AdicionarPonteiro(pWicBitmapSource);

Done:;
}

/// <summary>
/// Este método apara as regiões povoadas do cache de fonte de imagem apenas para o retângulo especificado.
/// A região fornecida deve ser construída para incluir a escala em que a fonte de imagem será desenhada. Essas coordenadas devem ser fornecidas em coordenadas locais.
/// Isso significa que eles devem ser ajustados antes de chamar a API de acordo com o DPI e outras transformações relevantes, que podem incluir a transformação do mundo e as transformações de pincel.
/// </summary>
/// <param name="Param_RegiaoPreservaRetangulo">Especifica a região da imagem, em pixels, que deve ser preservada no cache de fonte de imagem. Regiões que estão fora do retângulo são despejadas do cache. 
/// Por padrão, este é um retângulo vazio, o que significa que toda a imagem é despejada do cache.</param>
CarenResult CarenD2D1ImageSourceFromWic::TrimCache(CA_D2D1_RECT_U^ Param_RegiaoPreservaRetangulo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_U* pRect = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pRect = Util.ConverterD2D1_RECT_UManagedToUnmanaged(Param_RegiaoPreservaRetangulo);

	//Verifica se converteu com sucesso
	if (!ObjetoValido(pRect))
	{
		//Falhou ao converter a estrutura.

		//Define falha de conversão de estrutura.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_ESTRUTURA, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TrimCache(pRect);

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
	//Libera a memória para a matriz.
	DeletarEstruturaSafe(&pRect);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1ImageSource)


/// <summary>
/// Permite que o sistema operacional livre a memória de vídeo dos recursos descartando seu conteúdo.
/// </summary>
CarenResult CarenD2D1ImageSourceFromWic::OfferResources()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OfferResources();

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
/// Restaura o acesso aos recursos que foram oferecidos anteriormente pelo chamada OfferResources.
/// </summary>
/// <param name="Param_Out_RecursoDescartado">Retorna com TRUE se o conteúdo do recurso correspondente foi descartado e agora está indefinido ou FALSO se o conteúdo antigo do recurso correspondente ainda estiver intacto. 
/// O chamador pode passar NULO, se o chamador pretende preencher os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
CarenResult CarenD2D1ImageSourceFromWic::TryReclaimResources([Out] Boolean% Param_Out_RecursoDescartado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BOOL OutBool = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TryReclaimResources(&OutBool);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o bool e define no parametro de saida.
	Param_Out_RecursoDescartado = static_cast<Boolean>(OutBool);

Done:;
	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1ImageSourceFromWic::GetFactory(ICaren^ Param_Out_Factory)
{
	//Variaveis a serem utilizadas.
	ID2D1Factory* pFactory = NULL;

       //Variavel de resultados.
       CarenResult Resultado;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFactory(&pFactory);

	//Verifica se o ponteiro é válido
	if (!ObjetoValido(pFactory))
		Sair;

	//Adiciona o ponteiro na interface informada.
	Resultado = Param_Out_Factory->AdicionarPonteiro(pFactory);

	//Verifica o resultado da operação.
	if(Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera o ponteiro recuperado anteriormente.
		pFactory->Release();
		pFactory = NULL;

		//Chama uma execeção para indicar o erro.
		throw gcnew Exception( String::Format("Ocorreu uma falha ao definir o ponteiro nativo na interface gerenciada. Código de erro > {0}", Resultado.StatusCode));
	}

Done:;
}