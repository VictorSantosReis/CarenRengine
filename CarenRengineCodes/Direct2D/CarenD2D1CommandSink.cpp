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
#include "CarenD2D1CommandSink.h"

//Destruidor.
CarenD2D1CommandSink::~CarenD2D1CommandSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenD2D1CommandSink::CarenD2D1CommandSink(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Cria a implementação da interface
		PonteiroTrabalho = new CLN_ID2D1CommandSink();
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD2D1CommandSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1CommandSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1CommandSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1CommandSink**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1CommandSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1CommandSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1CommandSink**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1CommandSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1CommandSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1CommandSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1CommandSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1CommandSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1CommandSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1CommandSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1CommandSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1CommandSink();
}




// Métodos da interface proprietaria


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenD2D1CommandSink::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnBeginDraw= gcnew DelegateNativo_Evento_OnBeginDraw(this, &CarenD2D1CommandSink::EncaminharEvento_OnBeginDraw);
	Callback_OnEndDraw = gcnew DelegateNativo_Evento_OnEndDraw(this, &CarenD2D1CommandSink::EncaminharEvento_OnEndDraw);
	Callback_OnSetAntialiasMode = gcnew DelegateNativo_Evento_OnSetAntialiasMode(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetAntialiasMode);
	Callback_OnSetTags = gcnew DelegateNativo_Evento_OnSetTags(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetTags);
	Callback_OnSetTextAntialiasMode = gcnew DelegateNativo_Evento_OnSetTextAntialiasMode(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetTextAntialiasMode);
	Callback_OnSetTextRenderingParams = gcnew DelegateNativo_Evento_OnSetTextRenderingParams(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetTextRenderingParams);
	Callback_OnSetTransform = gcnew DelegateNativo_Evento_OnSetTransform(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetTransform);
	Callback_OnSetPrimitiveBlend = gcnew DelegateNativo_Evento_OnSetPrimitiveBlend(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetPrimitiveBlend);
	Callback_OnSetUnitMode = gcnew DelegateNativo_Evento_OnSetUnitMode(this, &CarenD2D1CommandSink::EncaminharEvento_OnSetUnitMode);
	Callback_OnClear = gcnew DelegateNativo_Evento_OnClear(this, &CarenD2D1CommandSink::EncaminharEvento_OnClear);
	Callback_OnDrawGlyphRun = gcnew DelegateNativo_Evento_OnDrawGlyphRun(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawGlyphRun);
	Callback_OnDrawLine = gcnew DelegateNativo_Evento_OnDrawLine(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawLine);
	Callback_OnDrawGeometry = gcnew DelegateNativo_Evento_OnDrawGeometry(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawGeometry);
	Callback_OnDrawRectangle = gcnew DelegateNativo_Evento_OnDrawRectangle(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawRectangle);
	Callback_OnDrawBitmap = gcnew DelegateNativo_Evento_OnDrawBitmap(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawBitmap);
	Callback_OnDrawImage = gcnew DelegateNativo_Evento_OnDrawImage(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawImage);
	Callback_OnDrawGdiMetafile = gcnew DelegateNativo_Evento_OnDrawGdiMetafile(this, &CarenD2D1CommandSink::EncaminharEvento_OnDrawGdiMetafile);
	Callback_OnFillMesh = gcnew DelegateNativo_Evento_OnFillMesh(this, &CarenD2D1CommandSink::EncaminharEvento_OnFillMesh);
	Callback_OnFillOpacityMask = gcnew DelegateNativo_Evento_OnFillOpacityMask(this, &CarenD2D1CommandSink::EncaminharEvento_OnFillOpacityMask);
	Callback_OnFillGeometry = gcnew DelegateNativo_Evento_OnFillGeometry(this, &CarenD2D1CommandSink::EncaminharEvento_OnFillGeometry);
	Callback_OnFillRectangle = gcnew DelegateNativo_Evento_OnFillRectangle(this, &CarenD2D1CommandSink::EncaminharEvento_OnFillRectangle);
	Callback_OnPushAxisAlignedClip = gcnew DelegateNativo_Evento_OnPushAxisAlignedClip(this, &CarenD2D1CommandSink::EncaminharEvento_OnPushAxisAlignedClip);
	Callback_OnPushLayer = gcnew DelegateNativo_Evento_OnPushLayer(this, &CarenD2D1CommandSink::EncaminharEvento_OnPushLayer);
	Callback_OnPopAxisAlignedClip = gcnew DelegateNativo_Evento_OnPopAxisAlignedClip(this, &CarenD2D1CommandSink::EncaminharEvento_OnPopAxisAlignedClip);
	Callback_OnPopLayer = gcnew DelegateNativo_Evento_OnPopLayer(this, &CarenD2D1CommandSink::EncaminharEvento_OnPopLayer);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnBeginDraw = Util.ConverterDelegateToPointer(Callback_OnBeginDraw);
	IntPtr Pointer_OnEndDraw = Util.ConverterDelegateToPointer(Callback_OnEndDraw);
	IntPtr Pointer_OnSetAntialiasMode = Util.ConverterDelegateToPointer(Callback_OnSetAntialiasMode);
	IntPtr Pointer_OnSetTags = Util.ConverterDelegateToPointer(Callback_OnSetTags);
	IntPtr Pointer_OnSetTextAntialiasMode = Util.ConverterDelegateToPointer(Callback_OnSetTextAntialiasMode);
	IntPtr Pointer_OnSetTextRenderingParams = Util.ConverterDelegateToPointer(Callback_OnSetTextRenderingParams);
	IntPtr Pointer_OnSetTransform = Util.ConverterDelegateToPointer(Callback_OnSetTransform);
	IntPtr Pointer_OnSetPrimitiveBlend = Util.ConverterDelegateToPointer(Callback_OnSetPrimitiveBlend);
	IntPtr Pointer_OnSetUnitMode = Util.ConverterDelegateToPointer(Callback_OnSetUnitMode);
	IntPtr Pointer_OnClear = Util.ConverterDelegateToPointer(Callback_OnClear);
	IntPtr Pointer_OnDrawGlyphRun = Util.ConverterDelegateToPointer(Callback_OnDrawGlyphRun);
	IntPtr Pointer_OnDrawLine = Util.ConverterDelegateToPointer(Callback_OnDrawLine);
	IntPtr Pointer_OnDrawGeometry = Util.ConverterDelegateToPointer(Callback_OnDrawGeometry);
	IntPtr Pointer_OnDrawRectangle = Util.ConverterDelegateToPointer(Callback_OnDrawRectangle);
	IntPtr Pointer_OnDrawBitmap = Util.ConverterDelegateToPointer(Callback_OnDrawBitmap);
	IntPtr Pointer_OnDrawImage = Util.ConverterDelegateToPointer(Callback_OnDrawImage);
	IntPtr Pointer_OnDrawGdiMetafile = Util.ConverterDelegateToPointer(Callback_OnDrawGdiMetafile);
	IntPtr Pointer_OnFillMesh = Util.ConverterDelegateToPointer(Callback_OnFillMesh);
	IntPtr Pointer_OnFillOpacityMask = Util.ConverterDelegateToPointer(Callback_OnFillOpacityMask);
	IntPtr Pointer_OnFillGeometry = Util.ConverterDelegateToPointer(Callback_OnFillGeometry);
	IntPtr Pointer_OnFillRectangle = Util.ConverterDelegateToPointer(Callback_OnFillRectangle);
	IntPtr Pointer_OnPushAxisAlignedClip = Util.ConverterDelegateToPointer(Callback_OnPushAxisAlignedClip);
	IntPtr Pointer_OnPushLayer = Util.ConverterDelegateToPointer(Callback_OnPushLayer);
	IntPtr Pointer_OnPopAxisAlignedClip = Util.ConverterDelegateToPointer(Callback_OnPopAxisAlignedClip);
	IntPtr Pointer_OnPopLayer = Util.ConverterDelegateToPointer(Callback_OnPopLayer);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnBeginDraw = Util.AlocarPointerDelegate(Pointer_OnBeginDraw);
	gHandle_Delegate_OnEndDraw = Util.AlocarPointerDelegate(Pointer_OnEndDraw);
	gHandle_Delegate_OnSetAntialiasMode = Util.AlocarPointerDelegate(Pointer_OnSetAntialiasMode);
	gHandle_Delegate_OnSetTags = Util.AlocarPointerDelegate(Pointer_OnSetTags);
	gHandle_Delegate_OnSetTextAntialiasMode = Util.AlocarPointerDelegate(Pointer_OnSetTextAntialiasMode);
	gHandle_Delegate_OnSetTextRenderingParams = Util.AlocarPointerDelegate(Pointer_OnSetTextRenderingParams);
	gHandle_Delegate_OnSetTransform = Util.AlocarPointerDelegate(Pointer_OnSetTransform);
	gHandle_Delegate_OnSetPrimitiveBlend = Util.AlocarPointerDelegate(Pointer_OnSetPrimitiveBlend);
	gHandle_Delegate_OnSetUnitMode = Util.AlocarPointerDelegate(Pointer_OnSetUnitMode);
	gHandle_Delegate_OnClear = Util.AlocarPointerDelegate(Pointer_OnClear);
	gHandle_Delegate_OnDrawGlyphRun = Util.AlocarPointerDelegate(Pointer_OnDrawGlyphRun);
	gHandle_Delegate_OnDrawLine = Util.AlocarPointerDelegate(Pointer_OnDrawLine);
	gHandle_Delegate_OnDrawGeometry = Util.AlocarPointerDelegate(Pointer_OnDrawGeometry);
	gHandle_Delegate_OnDrawRectangle = Util.AlocarPointerDelegate(Pointer_OnDrawRectangle);
	gHandle_Delegate_OnDrawBitmap = Util.AlocarPointerDelegate(Pointer_OnDrawBitmap);
	gHandle_Delegate_OnDrawImage = Util.AlocarPointerDelegate(Pointer_OnDrawImage);
	gHandle_Delegate_OnDrawGdiMetafile = Util.AlocarPointerDelegate(Pointer_OnDrawGdiMetafile);
	gHandle_Delegate_OnFillMesh = Util.AlocarPointerDelegate(Pointer_OnFillMesh);
	gHandle_Delegate_OnFillOpacityMask = Util.AlocarPointerDelegate(Pointer_OnFillOpacityMask);
	gHandle_Delegate_OnFillGeometry = Util.AlocarPointerDelegate(Pointer_OnFillGeometry);
	gHandle_Delegate_OnFillRectangle = Util.AlocarPointerDelegate(Pointer_OnFillRectangle);
	gHandle_Delegate_OnPushAxisAlignedClip = Util.AlocarPointerDelegate(Pointer_OnPushAxisAlignedClip);
	gHandle_Delegate_OnPushLayer = Util.AlocarPointerDelegate(Pointer_OnPushLayer);
	gHandle_Delegate_OnPopAxisAlignedClip = Util.AlocarPointerDelegate(Pointer_OnPopAxisAlignedClip);
	gHandle_Delegate_OnPopLayer = Util.AlocarPointerDelegate(Pointer_OnPopLayer);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_BeginDraw = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_BeginDraw>(Pointer_OnBeginDraw);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_EndDraw = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_EndDraw>(Pointer_OnEndDraw);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetAntialiasMode = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetAntialiasMode>(Pointer_OnSetAntialiasMode);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetTags = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetTags>(Pointer_OnSetTags);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetTextAntialiasMode = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetTextAntialiasMode>(Pointer_OnSetTextAntialiasMode);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetTextRenderingParams = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetTextRenderingParams>(Pointer_OnSetTextRenderingParams);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetTransform = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetTransform>(Pointer_OnSetTransform);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetPrimitiveBlend = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetPrimitiveBlend>(Pointer_OnSetPrimitiveBlend);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_SetUnitMode = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_SetUnitMode>(Pointer_OnSetUnitMode);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_Clear = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_Clear>(Pointer_OnClear);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawGlyphRun = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawGlyphRun>(Pointer_OnDrawGlyphRun);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawLine = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawLine>(Pointer_OnDrawLine);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawGeometry = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawGeometry>(Pointer_OnDrawGeometry);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawRectangle = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawRectangle>(Pointer_OnDrawRectangle);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawBitmap = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawBitmap>(Pointer_OnDrawBitmap);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawImage = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawImage>(Pointer_OnDrawImage);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_DrawGdiMetafile = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_DrawGdiMetafile>(Pointer_OnDrawGdiMetafile);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_FillMesh = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_FillMesh>(Pointer_OnFillMesh);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_FillOpacityMask = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_FillOpacityMask>(Pointer_OnFillOpacityMask);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_FillGeometry = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_FillGeometry>(Pointer_OnFillGeometry);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_FillRectangle = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_FillRectangle>(Pointer_OnFillRectangle);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_PushAxisAlignedClip = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_PushAxisAlignedClip>(Pointer_OnPushAxisAlignedClip);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_PushLayer = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_PushLayer>(Pointer_OnPushLayer);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_PopAxisAlignedClip = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_PopAxisAlignedClip>(Pointer_OnPopAxisAlignedClip);
	((CLN_ID2D1CommandSink*)PonteiroTrabalho)->Evento_PopLayer = Util.ConverterPointerDelegateToNativeDelegate<CLN_ID2D1CommandSink_EventoNativo_PopLayer>(Pointer_OnPopLayer);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenD2D1CommandSink::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnBeginDraw.Free();
	gHandle_Delegate_OnEndDraw.Free();
	gHandle_Delegate_OnSetAntialiasMode.Free();
	gHandle_Delegate_OnSetTags.Free();
	gHandle_Delegate_OnSetTextAntialiasMode.Free();
	gHandle_Delegate_OnSetTextRenderingParams.Free();
	gHandle_Delegate_OnSetTransform.Free();
	gHandle_Delegate_OnSetPrimitiveBlend.Free();
	gHandle_Delegate_OnSetUnitMode.Free();
	gHandle_Delegate_OnClear.Free();
	gHandle_Delegate_OnDrawGlyphRun.Free();
	gHandle_Delegate_OnDrawLine.Free();
	gHandle_Delegate_OnDrawGeometry.Free();
	gHandle_Delegate_OnDrawRectangle.Free();
	gHandle_Delegate_OnDrawBitmap.Free();
	gHandle_Delegate_OnDrawImage.Free();
	gHandle_Delegate_OnDrawGdiMetafile.Free();
	gHandle_Delegate_OnFillMesh.Free();
	gHandle_Delegate_OnFillOpacityMask.Free();
	gHandle_Delegate_OnFillGeometry.Free();
	gHandle_Delegate_OnFillRectangle.Free();
	gHandle_Delegate_OnPushAxisAlignedClip.Free();
	gHandle_Delegate_OnPushLayer.Free();
	gHandle_Delegate_OnPopAxisAlignedClip.Free();
	gHandle_Delegate_OnPopLayer.Free();

	//Libera os ponteiro da classe nativa
	CLN_ID2D1CommandSink* pVarPointer = (CLN_ID2D1CommandSink*)PonteiroTrabalho;

	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_BeginDraw))
	{
		//Descarta o delegate.
		pVarPointer->Evento_BeginDraw = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_EndDraw))
	{
		//Descarta o delegate.
		pVarPointer->Evento_EndDraw = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetAntialiasMode))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetAntialiasMode = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetTags))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetTags = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetTextAntialiasMode))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetTextAntialiasMode = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetTextRenderingParams))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetTextRenderingParams = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetTransform))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetTransform = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetPrimitiveBlend))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetPrimitiveBlend = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_SetUnitMode))
	{
		//Descarta o delegate.
		pVarPointer->Evento_SetUnitMode = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_Clear))
	{
		//Descarta o delegate.
		pVarPointer->Evento_Clear = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawGlyphRun))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawGlyphRun = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawLine))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawLine = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawGeometry))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawGeometry = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawRectangle))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawRectangle = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawBitmap))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawBitmap = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawImage))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawImage = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_DrawGdiMetafile))
	{
		//Descarta o delegate.
		pVarPointer->Evento_DrawGdiMetafile = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_FillMesh))
	{
		//Descarta o delegate.
		pVarPointer->Evento_FillMesh = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_FillOpacityMask))
	{
		//Descarta o delegate.
		pVarPointer->Evento_FillOpacityMask = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_FillGeometry))
	{
		//Descarta o delegate.
		pVarPointer->Evento_FillGeometry = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_FillRectangle))
	{
		//Descarta o delegate.
		pVarPointer->Evento_FillRectangle = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_PushAxisAlignedClip))
	{
		//Descarta o delegate.
		pVarPointer->Evento_PushAxisAlignedClip = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_PushLayer))
	{
		//Descarta o delegate.
		pVarPointer->Evento_PushLayer = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_PopAxisAlignedClip))
	{
		//Descarta o delegate.
		pVarPointer->Evento_PopAxisAlignedClip = NULL;
	}
	//Verifica se é valido e deleta o ponteiro.
	if (ObjetoValido(pVarPointer->Evento_PopLayer))
	{
		//Descarta o delegate.
		pVarPointer->Evento_PopLayer = NULL;
	}

}




// Métodos internos que são chamados pela classe nativa para notificar os eventos ocorridos.


/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnBeginDraw) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnBeginDraw() 
{
	//Chama o evento para notificar o usuário.
	OnBeginDraw();
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnClear) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnClear(_In_opt_ CONST D2D1_COLOR_F* color) 
{
	//Variaveis utilizadas
	Utilidades Util;
	CA_D2D1_COLOR_F^ D2D1Color = nullptr;

	//Verifica se a estrutura é valida.
	if (ObjetoValido(color))
	{
		//Converte a estrutura.
		D2D1Color = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(const_cast<D2D1_COLOR_F*>(color));

		//Chama o evento para notificar o usuário.
		OnClear(D2D1Color);
	}
	else
	{
		//Chama o evento com a estrutura nula
		OnClear(nullptr);
	}

	//Limpa os dados.
	DeletarEstruturaGerenciadaSafe(D2D1Color);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawBitmap) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawBitmap(
	_In_ ID2D1Bitmap* bitmap,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	FLOAT opacity,
	D2D1_INTERPOLATION_MODE interpolationMode,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle,
	_In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform) 
{
	//Variaveis utilizadas
	Utilidades Util;
	ICarenD2D1Bitmap^ OutBitmap = gcnew CarenD2D1Bitmap();
	CA_D2D1_RECT_F^ OutDestRetangulo = nullptr;
	CA_D2D1_RECT_F^ OutOrigemRetangulo = nullptr;
	CA_D2D1_MATRIX_4X4_F^ OutMatrixPerspective = nullptr;

	//Define o ponteiro nativo na interface.
	OutBitmap->AdicionarPonteiro(bitmap);

	//Verifica se os objetos opcionais são validos e converte.
	if (ObjetoValido(destinationRectangle))
	{
		//Converte a estrutura
		OutDestRetangulo = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(destinationRectangle));
	}
	if (ObjetoValido(sourceRectangle))
	{
		//Converte a estrutura
		OutOrigemRetangulo = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(sourceRectangle));
	}
	if (ObjetoValido(perspectiveTransform))
	{
		//Converte a estrutura
		OutMatrixPerspective = Util.ConverterD2D1_MATRIX_4X4_FUnmanagedToManaged(const_cast<D2D1_MATRIX_4X4_F*>(perspectiveTransform));
	}

	//Chama o evento para notificar
	OnDrawBitmap(OutBitmap, OutDestRetangulo, opacity, static_cast<CA_D2D1_INTERPOLATION_MODE>(interpolationMode), OutOrigemRetangulo, OutMatrixPerspective);

	//Deleta os objetos.
	DeletarEstruturaGerenciadaSafe(OutDestRetangulo);
	DeletarEstruturaGerenciadaSafe(OutOrigemRetangulo);
	DeletarEstruturaGerenciadaSafe(OutMatrixPerspective);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawGdiMetafile) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawGdiMetafile(
	_In_ ID2D1GdiMetafile* gdiMetafile,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset) 
{
	//Variaveis
	Utilidades Util;
	ICaren^ OutGdiMetaFile = nullptr;
	CA_D2D1_POINT_2F^ OutTargetOffset = nullptr; //Pode ser nulo.

	//Cria a interface
	OutGdiMetaFile = gcnew Caren();

	//Define o ponteiro na interface.
	OutGdiMetaFile->AdicionarPonteiro(gdiMetafile);

	//Converte a estrutura se ela for valida.
	if (ObjetoValido(targetOffset))
	{
		//Converte a estrutura para a gerenciada.
		OutTargetOffset = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(const_cast<D2D1_POINT_2F*>(targetOffset));
	}

	//Chama o evento.
	OnDrawGdiMetafile(OutGdiMetaFile, OutTargetOffset);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawGeometry) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle) 
{
	//Variaveis
	Utilidades Util;
	ICarenD2D1Geometry^ OutGeometry = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;
	ICarenD2D1StrokeStyle^ OutStrokeStyle = nullptr; //Pode ser NULO.

	//Cria as interfaces 
	OutGeometry = gcnew CarenD2D1Geometry();
	OutBrush = gcnew CarenD2D1Brush();

	//Define os ponteiros.
	OutGeometry->AdicionarPonteiro(geometry);
	OutBrush->AdicionarPonteiro(brush);

	//Verifica se a interface de estilo de traçado foi fornecida
	if (ObjetoValido(strokeStyle))
	{
		//Cria a interface.
		OutStrokeStyle = gcnew CarenD2D1StrokeStyle();

		//Define o ponteiro na interface.
		OutStrokeStyle->AdicionarPonteiro(strokeStyle);
	}

	//Chama o evento.
	OnDrawGeometry(OutGeometry, OutBrush, strokeWidth, OutStrokeStyle);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawGlyphRun) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawGlyphRun(
	D2D1_POINT_2F baselineOrigin,
	_In_ CONST DWRITE_GLYPH_RUN* glyphRun,
	_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
	_In_ ID2D1Brush* foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_POINT_2F^ OutBaselineOrigin = nullptr;
	CA_DWRITE_GLYPH_RUN^ OutDwriteRun = nullptr;
	CA_DWRITE_GLYPH_RUN_DESCRIPTION^ OutDwriteRunDesc = nullptr; //Pode ser NULO.
	ICarenD2D1Brush^ OutBrush = nullptr;
	CA_DWRITE_MEASURING_MODE OutDwriteMeasuring = static_cast<CA_DWRITE_MEASURING_MODE>(measuringMode);

	//Converte as estruturas.
	OutBaselineOrigin = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&baselineOrigin);
	OutDwriteRun = Util.ConverterDWRITE_GLYPH_RUNUnmanagedToManaged(const_cast<DWRITE_GLYPH_RUN*>(glyphRun));

	//Verifica se forneceu a estrutura  (glyphRunDescription).
	if(ObjetoValido(glyphRunDescription))
	{ 
		//Converte a estrutura
		OutDwriteRunDesc = Util.ConverterDWRITE_GLYPH_RUN_DESCRIPTIONUnmanagedToManaged(const_cast<DWRITE_GLYPH_RUN_DESCRIPTION*>(glyphRunDescription));
	}

	//Cria a interface do brush
	OutBrush = gcnew CarenD2D1Brush();

	//Define o ponteiro na interface.
	OutBrush->AdicionarPonteiro(foregroundBrush);

	//Chama o evento.
	OnDrawGlyphRun(OutBaselineOrigin, OutDwriteRun, OutDwriteRunDesc, OutBrush, OutDwriteMeasuring);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawImage) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawImage(
	_In_ ID2D1Image* image,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset,
	_In_opt_ CONST D2D1_RECT_F* imageRectangle,
	D2D1_INTERPOLATION_MODE interpolationMode,
	D2D1_COMPOSITE_MODE compositeMode) 
{
	//Variaveis
	Utilidades Util;
	ICarenD2D1Image^ OutImagem = nullptr;
	CA_D2D1_POINT_2F^ OutTargetOffset = nullptr;//Pode ser NULO.
	CA_D2D1_RECT_F^ OutImageRectangle = nullptr;//Pode ser NULO.
	CA_D2D1_INTERPOLATION_MODE OutInterMode = static_cast<CA_D2D1_INTERPOLATION_MODE>(interpolationMode);
	CA_D2D1_COMPOSITE_MODE OutCompMode = static_cast<CA_D2D1_COMPOSITE_MODE>(compositeMode);

	//Cria a interface de imagem.
	OutImagem = gcnew CarenD2D1Image();

	//Define o ponteiro na interface.
	OutImagem->AdicionarPonteiro(image);

	//Verifica se as estruturas são validas e converte.
	if(ObjetoValido(targetOffset))
	{
		//Converte a estrutura e define.
		OutTargetOffset = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(const_cast<D2D1_POINT_2F*>(targetOffset));
	}
	if (ObjetoValido(imageRectangle))
	{
		//Converte a estrutura e define.
		OutImageRectangle = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(imageRectangle));
	}

	//Chama o evento.
	OnDrawImage(OutImagem, OutTargetOffset, OutImageRectangle, OutInterMode, OutCompMode);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawLine) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawLine(
	D2D1_POINT_2F point0,
	D2D1_POINT_2F point1,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_POINT_2F^ OutPoint0 = nullptr;
	CA_D2D1_POINT_2F^ OutPoint1 = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;
	ICarenD2D1StrokeStyle^ OutStrokeStyle = nullptr; //Pode ser NULO.

	//Converte as estruturas.
	OutPoint0 = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&point0);
	OutPoint1 = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&point1);

	//Cria a interface do brush.
	OutBrush = gcnew CarenD2D1Brush();

	//Define o ponteiro.
	OutBrush->AdicionarPonteiro(brush);

	//Verifica se forneceu a interface de estilo de traçado.
	if (ObjetoValido(strokeStyle))
	{
		//Cria a interface.
		OutStrokeStyle = gcnew CarenD2D1StrokeStyle();

		//Define o ponteiro.
		OutStrokeStyle->AdicionarPonteiro(strokeStyle);
	}

	//Chama o evento.
	OnDrawLine(OutPoint0, OutPoint1, OutBrush, strokeWidth, OutStrokeStyle);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDrawRectangle) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnDrawRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_RECT_F^ OutRect = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;
	ICarenD2D1StrokeStyle^ OutStrokeStyle = nullptr; //Pode ser NULO.

	//Converte a estrutura.
	OutRect = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(rect));

	//Cria a interface de brush
	OutBrush = gcnew CarenD2D1Brush();

	//Define o ponteiro.
	OutBrush->AdicionarPonteiro(brush);

	//Verifica se forneceu a interface de estilo de traçado.
	if (ObjetoValido(strokeStyle))
	{
		//Cria a interface.
		OutStrokeStyle = gcnew CarenD2D1StrokeStyle();

		//Define o ponteiro.
		OutStrokeStyle->AdicionarPonteiro(strokeStyle);
	}

	//Chama o evento.
	OnDrawRectangle(OutRect, OutBrush, strokeWidth, OutStrokeStyle);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnEndDraw) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnEndDraw()
{
	//Chama o evento.
	OnEndDraw();
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFillGeometry) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnFillGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	_In_opt_ ID2D1Brush* opacityBrush)
{
	//Variaveis
	Utilidades Util;
	ICarenD2D1Geometry^ OutGeometry = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;
	ICarenD2D1Brush^ OutBrushOpacity = nullptr; //Pode ser NULO.

	//Cria as interfaces.
	OutGeometry = gcnew CarenD2D1Geometry();
	OutBrush = gcnew CarenD2D1Brush();

	//Define os ponteiros nas interfaces.
	OutGeometry->AdicionarPonteiro(geometry);
	OutBrush->AdicionarPonteiro(brush);

	//Verifica se forneceu o brush de opacidade.
	if (ObjetoValido(opacityBrush))
	{
		//Cria a interface
		OutBrushOpacity = gcnew CarenD2D1Brush();

		//Define o ponteiro na interface.
		OutBrushOpacity->AdicionarPonteiro(opacityBrush);
	}

	//Chama o evento.
	OnFillGeometry(OutGeometry, OutBrush, OutBrushOpacity);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFillMesh) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnFillMesh(
	_In_ ID2D1Mesh* mesh,
	_In_ ID2D1Brush* brush) 
{
	//Variaveis
	ICarenD2D1Mesh^ OutMesh = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;

	//Cria as interfaces.
	OutMesh = gcnew CarenD2D1Mesh();
	OutBrush = gcnew CarenD2D1Brush();

	//Define os ponteiros nas interfaces.
	OutMesh->AdicionarPonteiro(mesh);
	OutBrush->AdicionarPonteiro(brush);

	//Chama o evento.
	OnFillMesh(OutMesh, OutBrush);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFillOpacityMask) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnFillOpacityMask(
	_In_ ID2D1Bitmap* opacityMask,
	_In_ ID2D1Brush* brush,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle) 
{
	//Variaveis
	Utilidades Util;
	ICarenD2D1Bitmap^ OutBitmap = nullptr;
	ICarenD2D1Brush^ OutBrush = nullptr;
	CA_D2D1_RECT_F^ OutRetDestino = nullptr; //Pode ser NULO.
	CA_D2D1_RECT_F^ OutRetOrigem = nullptr; //Pode ser NULO.

	//Cria as interfaces.
	OutBitmap = gcnew CarenD2D1Bitmap();
	OutBrush = gcnew CarenD2D1Brush();

	//Define os ponteiros nas interfaces.
	OutBitmap->AdicionarPonteiro(opacityMask);
	OutBrush->AdicionarPonteiro(brush);

	//Verifica se forneceu as estruturas e converte.
	if(ObjetoValido(destinationRectangle))
	{ 
		//Converte e define a estrutura.
		OutRetDestino = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(destinationRectangle));
	}
	if (ObjetoValido(sourceRectangle))
	{
		//Converte e define a estrutura.
		OutRetOrigem = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(sourceRectangle));
	}

	//Chama o evento
	OnFillOpacityMask(OutBitmap, OutBrush, OutRetDestino, OutRetOrigem);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFillRectangle) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnFillRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush)
{
	//Variaveis
	Utilidades Util;
	ICarenD2D1Brush^ OutBrush = nullptr;
	CA_D2D1_RECT_F^ OutRect = nullptr;

	//Cria a interface.
	OutBrush = gcnew CarenD2D1Brush();

	//Define o ponteiro na interface.
	OutBrush->AdicionarPonteiro(brush);

	//Converte e define a estrutura.
	OutRect = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(rect));

	//Chama o evento.
	OnFillRectangle(OutRect, OutBrush);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnPopAxisAlignedClip) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnPopAxisAlignedClip() 
{
	//Chama o evento.
	OnPopAxisAlignedClip();
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnPopLayer) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnPopLayer() 
{
	//Chama o evento.
	OnPopLayer();
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnPushAxisAlignedClip) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnPushAxisAlignedClip(
	_In_ CONST D2D1_RECT_F* clipRect,
	D2D1_ANTIALIAS_MODE antialiasMode) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_RECT_F^ OutClipRect = nullptr;
	CA_D2D1_ANTIALIAS_MODE OutAntiAlias = static_cast<CA_D2D1_ANTIALIAS_MODE>(antialiasMode);

	//Converte e define a estrutura.
	OutClipRect = Util.ConverterD2D1_RECT_FUnmanagedToManaged(const_cast<D2D1_RECT_F*>(clipRect));

	//Chama o evento.
	OnPushAxisAlignedClip(OutClipRect, OutAntiAlias);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnPushLayer) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnPushLayer(
	_In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
	_In_opt_ ID2D1Layer* layer) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_LAYER_PARAMETERS1^ OutLayerParams = nullptr;
	ICarenD2D1Layer^ OutLayer = nullptr;//Pode ser NULO.

	//Converte a estrutura.
	OutLayerParams = Util.ConverterD2D1_LAYER_PARAMETERS1UnmanagedToManaged(const_cast<D2D1_LAYER_PARAMETERS1*>(layerParameters1));

	//Verifica se forneceu a interface de camada
	if (ObjetoValido(layer))
	{
		//Cria a interface.
		OutLayer = gcnew CarenD2D1Layer();

		//Define o ponteiro na interface.
		OutLayer->AdicionarPonteiro(layer);
	}

	//Chama o evento.
	OnPushLayer(OutLayerParams, OutLayer);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetAntialiasMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode) 
{
	//Chama o evento.
	OnSetAntialiasMode(static_cast<CA_D2D1_ANTIALIAS_MODE>(antialiasMode));
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetPrimitiveBlend) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetPrimitiveBlend(D2D1_PRIMITIVE_BLEND primitiveBlend) 
{
	//Chama o evento.
	OnSetPrimitiveBlend(static_cast<CA_D2D1_PRIMITIVE_BLEND>(primitiveBlend));
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetTags) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetTags(
	D2D1_TAG tag1,
	D2D1_TAG tag2) 
{
	//Chama o evento.
	OnSetTags(static_cast<UInt64>(tag1), static_cast<UInt64>(tag2));
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetTextAntialiasMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode) 
{
	//Chama o evento.
	OnSetTextAntialiasMode(static_cast<CA_D2D1_TEXT_ANTIALIAS_MODE>(textAntialiasMode));
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetTextRenderingParams) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetTextRenderingParams(_In_opt_ IDWriteRenderingParams* textRenderingParams)
{
	//Variaveis
	ICaren^ OutDwriteRenderParams = nullptr; //Pode ser NULO.

	//Verifica se forneceu a interface.
	if (ObjetoValido(textRenderingParams))
	{
		//Cria a interface.
		OutDwriteRenderParams = gcnew Caren();

		//Define o ponteiro na interface.
		OutDwriteRenderParams->AdicionarPonteiro(textRenderingParams);
	}

	//Chama o evento.
	OnSetTextRenderingParams(OutDwriteRenderParams);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetTransform) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetTransform(_In_ CONST D2D1_MATRIX_3X2_F* transform) 
{
	//Variaveis
	Utilidades Util;
	CA_D2D1_MATRIX_3X2_F^ OutTransform = nullptr;

	//Converte a estrutura e define.
	OutTransform = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(const_cast<D2D1_MATRIX_3X2_F*>(transform));

	//Chama o evento.
	OnSetTransform(OutTransform);
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnSetUnitMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
/// </summary>
void CarenD2D1CommandSink::EncaminharEvento_OnSetUnitMode(D2D1_UNIT_MODE unitMode) 
{
	//Chama o evento.
	OnSetUnitMode(static_cast<CA_D2D1_UNIT_MODE>(unitMode));
}