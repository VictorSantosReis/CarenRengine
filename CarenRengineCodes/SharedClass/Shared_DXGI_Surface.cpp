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
#include "Shared_DXGI.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_DXGISurface)


// Métodos da interface ICarenDXGISurface2

/// <summary>
/// (GetResource) - Obtém o índice de recursos parentais e subrecursos que suportam uma superfície de subrecursos.
/// Os objetos atuais que implementam o IDXGISurface são recursos ou visualizações. GetResource para esses objetos retorna "this" ou o 
/// recurso que suporta a exibição, respectivamente. Nesta situação, o índice de subrecursos é 0.
/// </summary>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do tipo de interface solicitado.</param>
/// <param name="Param_Out_ObjetoRecurso">Recebe um ponteiro para um buffer que recebe um ponteiro para o objeto de recurso pai para a superfície do subrecurso.  O usuário deve inicializar a interface antes de chamar este método.</param>
/// <param name="Param_Ref_IndexSubrecurso">Recebe o índice da superfície do subrecurso.</param>
CarenResult Shared_DXGISurface::GetResource(
	IDXGISurface2* Param_MyPointerWork,
	String^ Param_RIID, 
	ICaren^ Param_Out_ObjetoRecurso, 
	UInt32% Param_Ref_IndexSubrecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID riidInterface = GUID_NULL;
	LPVOID pObjetoRecurso = NULL;
	UINT OutIndexSubrecurso = 0;

	//Obtém o guid do recurso
	if (ObjetoGerenciadoValido(Param_RIID))
	{
		//Cria o Guid aparti da string fornecida pelo usuário.
		riidInterface = Util.CreateGuidFromString(Param_RIID);
	}
	else
	{
		//Erro. O riid da interface não pode ser nulo.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetResource(riidInterface, &pObjetoRecurso, &OutIndexSubrecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Adiciona o ponteiro a interface de saida.
	Param_Out_ObjetoRecurso->AdicionarPonteiro(pObjetoRecurso);

	//Define o indice de subrecurso no parametro de saida.
	Param_Ref_IndexSubrecurso = static_cast<UInt32>(OutIndexSubrecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGISurface1

/// <summary>
/// (GetDC) - Retorna um contexto de dispositivo (DC) que permite que você se torne uma superfície de Infraestrutura Gráfica Microsoft DirectX (DXGI) usando a Interface do Dispositivo Gráfico windows (GDI).
/// </summary>
/// <param name="Param_Descartar">Um valor booleano que especifica se deve preservar o conteúdo Direct3D no GDI DC. 
/// TRUE direciona o tempo de execução para não preservar o conteúdo Direct3D no GDI DC; ou seja, o tempo de execução 
/// descarta o conteúdo Direct3D. False garante que o conteúdo Direct3D esteja disponível no GDI DC.</param>
/// <param name="Param_Out_HDCHandle">Recebe um ponteiro para uma Handle(Alça) HDC que representa o contexto atual do dispositivo para renderização GDI.</param>
CarenResult Shared_DXGISurface::GetDC(
	IDXGISurface1* Param_MyPointerWork,
	Boolean Param_Descartar, 
	[Out] IntPtr% Param_Out_HDCHandle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	HDC HandHDC = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDC(Param_Descartar, &HandHDC);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o HDC no parametro de saida.
	Param_Out_HDCHandle = IntPtr(HandHDC);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseDC) - Libera o contexto do dispositivo GDI (DC) que está associado à superfície atual e permite que você use o Direct3D para renderizar.
/// </summary>
/// <param name="Param_Regiao">Um ponteiro para uma estrutura rect que identifica a região suja da superfície. Uma região suja é qualquer 
/// parte da superfície que você usou para renderização GDI e que você quer preservar.Esta área é usada como uma dica de desempenho para 
/// subsistema gráfico em certos cenários.Não utilize este parâmetro para restringir a renderização à região retangular especificada. 
/// Se você passar NULO, ReleaseDC considera toda a superfície como suja. Caso contrário, o (ReleaseDC) usa a área especificada pelo CA_RECT
/// como uma dica de desempenho para indicar quais áreas foram manipuladas pela renderização GDI. Você pode passar um ponteiro para uma 
/// estrutura rect vazia(um retângulo sem posição ou área) se você não alterar qualquer conteúdo.</param>
CarenResult Shared_DXGISurface::ReleaseDC(
	IDXGISurface1* Param_MyPointerWork,
	CA_RECT^ Param_Regiao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PRECT RetanguloSujo = NULL;

	//Verifica se o parametro é valido
	if (ObjetoGerenciadoValido(Param_Regiao))
	{
		//Converte a estrutura gerenciada para a nativa.
		RetanguloSujo = Util.ConverterRECTManagedToUnmanaged(Param_Regiao);
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->ReleaseDC(RetanguloSujo);

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
	//Limpa a estrutura se valida
	if (ObjetoValido(RetanguloSujo))
	{
		//Deleta a memoria alocada
		DeletarEstruturaSafe(&RetanguloSujo);
	}

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGISurface

/// <summary>
/// (GetDesc) - Método responsável por obter uma descrição da superfície.
/// </summary>
/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
CarenResult Shared_DXGISurface::GetDesc(
	IDXGISurface* Param_MyPointerWork,
	[Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_SURFACE_DESC DescSuperfice = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc(&DescSuperfice);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida
	Param_Out_DescSuperfice = Util.ConverterDXGI_SURFACE_DESCUnManaged_ToManaged(&DescSuperfice);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Map) - Método responsável por obter um ponteiro para os dados contidos na superfície e negue o acesso da GPU à superfície.
/// </summary>
/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que contém os dados mapeados da superfice.</param>
CarenResult Shared_DXGISurface::Map(
	IDXGISurface* Param_MyPointerWork,
	CA_DXGI_MAP_FLAGS Param_Flags, 
	[Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT FlagsMap = static_cast<UINT>(Param_Flags);
	DXGI_MAPPED_RECT MapBufferSuperfice = {};

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->Map(&MapBufferSuperfice, FlagsMap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para gerenciada e define no parametro de saida.
	Param_Out_RectMapeado = Util.ConverterDXGI_MAPPED_RECTUnManaged_ToManaged(&MapBufferSuperfice);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Unmap) - Método responsável por invalidar o ponteiro para a superfície recuperada pelo ICarenDXGISurface::Map e 
/// reativar o acesso GPU ao recurso.
/// </summary>
CarenResult Shared_DXGISurface::Unmap(IDXGISurface* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->Unmap();

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