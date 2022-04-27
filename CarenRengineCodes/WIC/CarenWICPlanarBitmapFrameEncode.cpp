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
#include "CarenWICPlanarBitmapFrameEncode.h"

//Destruidor.
CarenWICPlanarBitmapFrameEncode::~CarenWICPlanarBitmapFrameEncode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICPlanarBitmapFrameEncode::CarenWICPlanarBitmapFrameEncode()
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
CarenResult CarenWICPlanarBitmapFrameEncode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICPlanarBitmapFrameEncode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICPlanarBitmapFrameEncode**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICPlanarBitmapFrameEncode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICPlanarBitmapFrameEncode**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICPlanarBitmapFrameEncode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICPlanarBitmapFrameEncode::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICPlanarBitmapFrameEncode::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICPlanarBitmapFrameEncode::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICPlanarBitmapFrameEncode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICPlanarBitmapFrameEncode();
}



// Métodos da interface proprietária(ICarenWICPlanarBitmapFrameEncode)


/// <summary>
/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
/// As chamadas WritePixels sucessivas são assumidas adicionando linhas de varredura sequencialmente à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
/// e ICarenWICBitmapFrameEncode::SetPixelFormat devem ser chamados antes deste método ou ele falhará.
/// O formato de pixel intercalado definido via ICarenWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
/// </summary>
/// <param name="Param_LineCount">O número de linhas para codificar. Consulte a seção Observações para restrições específicas de contagem de linhas do WIC Jpeg.</param>
/// <param name="Param_Planes">Especifica os buffers de origem para cada plano componente codificado.</param>
/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_Planes).</param>
CarenResult CarenWICPlanarBitmapFrameEncode::WritePixels(
UInt32 Param_LineCount,
cli::array<CA_WICBitmapPlane^>^ Param_Planes,
UInt32 Param_QuantidadePlanes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICBitmapPlane* vi_Planes = CriarMatrizEstruturas<WICBitmapPlane>(Param_QuantidadePlanes);
	WICBitmapPlane* vi_PlaneAuxiliar = Nulo;

	//Abre um for para converter e definir os dados.
	for (UINT32 i = 0; i < Param_QuantidadePlanes; i++)
	{
		//Converte a estrutura.
		vi_PlaneAuxiliar = Util.ConverterWICBitmapPlaneManaged_ToUnmanaged(Param_Planes[i]);

		//Define a estrutura no index especifiacdo.
		vi_Planes[i] = *vi_PlaneAuxiliar;

		//Libera a memória utilizada pela estrutura.
		DeletarEstruturaSafe(&vi_PlaneAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WritePixels(Param_LineCount, vi_Planes, Param_QuantidadePlanes);

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
	//Libera a memória utilizada pela matriz de estrutura.
	DeletarMatrizEstruturasSafe(&vi_Planes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
/// Sucessivas chamadas WriteSource são assumidas sequencialmente adicionando linhas de varredura à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
/// e ICarenWICBitmapFrameEncode::SetPixelFormat deve ser chamado antes deste método ou ele falhará.
/// O formato de pixel intercalado definido via IWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
/// </summary>
/// <param name="Param_ArrayPlanes">Especifica uma matriz de interface (ICarenWICBitmapSource) que representam planos de imagem.</param>
/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_ArrayPlanes).</param>
/// <param name="Param_RetanguloOrigem">O retângulo de origem de pixels para codificar a partir dos planos ICarenWICBitmapSource. Nulo indica toda a fonte. A largura de retificada de origem 
/// deve corresponder à largura definida através do SetSize. Chamadas repetidas do WriteSource podem ser feitas desde que a altura total acumulada do retifice seja a mesma definida através do SetSize.</param>
CarenResult CarenWICPlanarBitmapFrameEncode::WriteSource(
cli::array<ICarenWICBitmapSource^>^ Param_ArrayPlanes,
UInt32 Param_QuantidadePlanes,
CA_WICRect^ Param_RetanguloOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource** vi_ArrayPlanes = CriarMatrizPonteiros<IWICBitmapSource>(Param_QuantidadePlanes);
	WICRect* vi_Rect = Nulo;

	//Copia os ponteiros na matriz gerenciada para a matriz de ponteiros nativos.
	Util.CopiarPonteirosGerenciado_ToNativo(vi_ArrayPlanes, Param_ArrayPlanes, Param_QuantidadePlanes);

	//Converte a estrutura
	vi_Rect = Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteSource(vi_ArrayPlanes, Param_QuantidadePlanes, vi_Rect);

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
	//Libera a memória utilizada pela matriz e a estrutura
	DeletarMatrizPonteirosSafe(&vi_ArrayPlanes);
	DeletarEstruturaSafe(&vi_Rect);

	//Retorna o resultado.
	return Resultado;
}