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

#pragma once
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos para descarregar determinadas operações na implementação IWICBitmapSource subjacente.
/// </summary>
public ref class CarenWICBitmapSourceTransform : public ICarenWICBitmapSourceTransform
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapSourceTransform).
	IWICBitmapSourceTransform* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapSourceTransform();
	
	~CarenWICBitmapSourceTransform();

	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}


	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenWICBitmapSourceTransform)
public:
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
	virtual CarenResult CopyPixels(
	CA_WICRect^ Param_Retangulo,
	UInt32 Param_Width,
	UInt32 Param_Height,
	String^ Param_GuidFormatoDestino,
	CA_WICBitmapTransformOptions Param_TransformDestino,
	UInt32 Param_Stride,
	UInt32 Param_BufferSize,
	ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// Determina se uma opção de transformação específica é suportada nativamente pela implementação da interface ICarenWICBitmapSourceTransform. 
	/// </summary>
	/// <param name="Param_DestinoTransformacao">O WICBitmapTransformOptions para verificar se eles são suportados.</param>
	/// <param name="Param_Out_Suporte">Retorna um valor especificando se a opção de transformação é suportada.</param>
	virtual CarenResult DoesSupportTransform(
	CA_WICBitmapTransformOptions Param_DestinoTransformacao,
	[Out] Boolean% Param_Out_Suporte);

	/// <summary>
	/// Recupera o formato de pixel mais próximo ao qual a implementação do ICarenWICBitmapSourceTransform pode copiar nativamente pixels, dado o formato desejado. 
	/// </summary>
	/// <param name="Param_Ref_INOUT_DestinoGuidFormato">Na entrada, o formato do pixel desejado, na saida, retorna o formato do pixel suportado mais proximo do desejado.</param>
	virtual CarenResult GetClosestPixelFormat(String^% Param_Ref_INOUT_DestinoGuidFormato);

	/// <summary>
	/// Retorna as dimensões mais próximas que a implementação pode escalar nativamente para dadas as dimensões desejadas. 
	/// </summary>
	/// <param name="Param_Ref_INOUT_Width">A Largura desejada. Retorna a Largura suportada mais próxima.</param>
	/// <param name="Param_Ref_INOUT_Height">A Altura desejada. Retorna a Altura suportada mais próxima.</param>
	virtual CarenResult GetClosestSize(
	UInt32% Param_Ref_INOUT_Width,
	UInt32% Param_Ref_INOUT_Height);
};