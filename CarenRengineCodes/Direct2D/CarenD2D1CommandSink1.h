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
#include "../SDK_Direct2D.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenD2D1Bitmap.h"
#include "CarenD2D1Geometry.h"
#include "CarenD2D1Brush.h"
#include "CarenD2D1StrokeStyle.h"
#include "CarenD2D1Image.h"
#include "CarenD2D1Mesh.h"
#include "CarenD2D1Layer.h"
#include "../NativeClassForEvents/CLN_ID2D1CommandSink1.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
/// </summary>
public ref class CarenD2D1CommandSink1 : public ICarenD2D1CommandSink1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1CommandSink1).
	ID2D1CommandSink1* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a interface e permite que o usuário decida se a biblioteca deve criar a interface ou vai iniciar sem um ponteiro 
	/// de trabalho. Se (Param_CriarInterface) for TRUE, o construtor vai criar uma implementação da interface(ID2D1CommandSink1).
	/// </summary>
	/// <param name="Param_CriarInterface">Um valor booleano, TRUE indica que deve criar uma nova interface intermanete, caso contario, FALSE.</param>
	CarenD2D1CommandSink1(Boolean Param_CriarInterface);

	~CarenD2D1CommandSink1();


	//Conversões implicitas
public:
	static operator CarenD2D1CommandSink1^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1CommandSink1^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1CommandSink1(false);

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1CommandSink1*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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


	//Eventos
public:
	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////


	//Eventos da interface ICarenD2D1CommandSink1.

	virtual event ICarenD2D1CommandSink1::DelegateOnSetPrimitiveBlend1^ OnSetPrimitiveBlend1;



	//Eventos da interface (ICarenD2D1CommandSink)

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (BeginDraw).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnBeginDraw^ OnBeginDraw;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (Clear).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnClear^ OnClear;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawBitmap).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawBitmap^ OnDrawBitmap;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawGdiMetafile).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawGdiMetafile^ OnDrawGdiMetafile;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawGeometry).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawGeometry^ OnDrawGeometry;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawGlyphRun).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawGlyphRun^ OnDrawGlyphRun;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawImage).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawImage^ OnDrawImage;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawLine).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawLine^ OnDrawLine;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (DrawRectangle).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnDrawRectangle^ OnDrawRectangle;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (EndDraw).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnEndDraw^ OnEndDraw;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (FillGeometry).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnFillGeometry^ OnFillGeometry;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (FillMesh).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnFillMesh^ OnFillMesh;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (FillOpacityMask).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnFillOpacityMask^ OnFillOpacityMask;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (FillRectangle).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnFillRectangle^ OnFillRectangle;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (PopAxisAlignedClip).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnPopAxisAlignedClip^ OnPopAxisAlignedClip;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (PopLayer).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnPopLayer^ OnPopLayer;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (PushAxisAlignedClip).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnPushAxisAlignedClip^ OnPushAxisAlignedClip;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (PushLayer).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnPushLayer^ OnPushLayer;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetAntialiasMode).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetAntialiasMode^ OnSetAntialiasMode;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetPrimitiveBlend).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetPrimitiveBlend^ OnSetPrimitiveBlend;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetTags).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetTags^ OnSetTags;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetTextAntialiasMode).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetTextAntialiasMode^ OnSetTextAntialiasMode;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetTextRenderingParams).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetTextRenderingParams^ OnSetTextRenderingParams;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetTransform).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetTransform^ OnSetTransform;

	/// <summary>
	/// Evento chamado para notificar a reprodução do comando (SetUnitMode).
	/// </summary>
	virtual event ICarenD2D1CommandSink1::DelegateOnSetUnitMode^ OnSetUnitMode;



	//Delegates para uso nativo.
private:

	/////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_D2D1CommandSink)//
	/////////////////////////////////////////////////////////////////////////////////////


	//Delegates da interface ICarenD2D1CommandSink1.

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetPrimitiveBlend1) nativo da classe (CLN_D2D1CommandSink1) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetPrimitiveBlend1(D2D1_PRIMITIVE_BLEND primitiveBlend);
	DelegateNativo_Evento_OnSetPrimitiveBlend1^ Callback_OnSetPrimitiveBlend1 = nullptr;



	//Delegates da interface ICarenD2D1CommandSink

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnBeginDraw) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnBeginDraw();
	DelegateNativo_Evento_OnBeginDraw^ Callback_OnBeginDraw = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClear) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClear(_In_opt_ CONST D2D1_COLOR_F* color);
	DelegateNativo_Evento_OnClear^ Callback_OnClear = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawBitmap) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawBitmap(_In_ ID2D1Bitmap* bitmap,
		_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
		FLOAT opacity,
		D2D1_INTERPOLATION_MODE interpolationMode,
		_In_opt_ CONST D2D1_RECT_F* sourceRectangle,
		_In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform);
	DelegateNativo_Evento_OnDrawBitmap^ Callback_OnDrawBitmap = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawGdiMetafile) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawGdiMetafile(
		_In_ ID2D1GdiMetafile* gdiMetafile,
		_In_opt_ CONST D2D1_POINT_2F* targetOffset);
	DelegateNativo_Evento_OnDrawGdiMetafile^ Callback_OnDrawGdiMetafile = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawGeometry) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawGeometry(
		_In_ ID2D1Geometry* geometry,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);
	DelegateNativo_Evento_OnDrawGeometry^ Callback_OnDrawGeometry = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawGlyphRun) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawGlyphRun(
		D2D1_POINT_2F baselineOrigin,
		_In_ CONST DWRITE_GLYPH_RUN* glyphRun,
		_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
		_In_ ID2D1Brush* foregroundBrush,
		DWRITE_MEASURING_MODE measuringMode);
	DelegateNativo_Evento_OnDrawGlyphRun^ Callback_OnDrawGlyphRun = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawImage) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawImage(
		_In_ ID2D1Image* image,
		_In_opt_ CONST D2D1_POINT_2F* targetOffset,
		_In_opt_ CONST D2D1_RECT_F* imageRectangle,
		D2D1_INTERPOLATION_MODE interpolationMode,
		D2D1_COMPOSITE_MODE compositeMode);
	DelegateNativo_Evento_OnDrawImage^ Callback_OnDrawImage = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawLine) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawLine(
		D2D1_POINT_2F point0,
		D2D1_POINT_2F point1,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);
	DelegateNativo_Evento_OnDrawLine^ Callback_OnDrawLine = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDrawRectangle) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDrawRectangle(
		_In_ CONST D2D1_RECT_F* rect,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);
	DelegateNativo_Evento_OnDrawRectangle^ Callback_OnDrawRectangle = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnEndDraw) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnEndDraw();
	DelegateNativo_Evento_OnEndDraw^ Callback_OnEndDraw = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFillGeometry) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFillGeometry(
		_In_ ID2D1Geometry* geometry,
		_In_ ID2D1Brush* brush,
		_In_opt_ ID2D1Brush* opacityBrush);
	DelegateNativo_Evento_OnFillGeometry^ Callback_OnFillGeometry = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFillMesh) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFillMesh(
		_In_ ID2D1Mesh* mesh,
		_In_ ID2D1Brush* brush);
	DelegateNativo_Evento_OnFillMesh^ Callback_OnFillMesh = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFillOpacityMask) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFillOpacityMask(
		_In_ ID2D1Bitmap* opacityMask,
		_In_ ID2D1Brush* brush,
		_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
		_In_opt_ CONST D2D1_RECT_F* sourceRectangle);
	DelegateNativo_Evento_OnFillOpacityMask^ Callback_OnFillOpacityMask = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFillRectangle) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFillRectangle(
		_In_ CONST D2D1_RECT_F* rect,
		_In_ ID2D1Brush* brush);
	DelegateNativo_Evento_OnFillRectangle^ Callback_OnFillRectangle = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnPopAxisAlignedClip) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnPopAxisAlignedClip();
	DelegateNativo_Evento_OnPopAxisAlignedClip^ Callback_OnPopAxisAlignedClip = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnPopLayer) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnPopLayer();
	DelegateNativo_Evento_OnPopLayer^ Callback_OnPopLayer = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnPushAxisAlignedClip) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnPushAxisAlignedClip(
		_In_ CONST D2D1_RECT_F* clipRect,
		D2D1_ANTIALIAS_MODE antialiasMode);
	DelegateNativo_Evento_OnPushAxisAlignedClip^ Callback_OnPushAxisAlignedClip = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnPushLayer) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnPushLayer(
		_In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
		_In_opt_ ID2D1Layer* layer);
	DelegateNativo_Evento_OnPushLayer^ Callback_OnPushLayer = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetAntialiasMode) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode);
	DelegateNativo_Evento_OnSetAntialiasMode^ Callback_OnSetAntialiasMode = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetPrimitiveBlend) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetPrimitiveBlend(D2D1_PRIMITIVE_BLEND primitiveBlend);
	DelegateNativo_Evento_OnSetPrimitiveBlend^ Callback_OnSetPrimitiveBlend = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetTags) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetTags(
		D2D1_TAG tag1,
		D2D1_TAG tag2);
	DelegateNativo_Evento_OnSetTags^ Callback_OnSetTags = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetTextAntialiasMode) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode);
	DelegateNativo_Evento_OnSetTextAntialiasMode^ Callback_OnSetTextAntialiasMode = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetTextRenderingParams) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetTextRenderingParams(_In_opt_ IDWriteRenderingParams* textRenderingParams);
	DelegateNativo_Evento_OnSetTextRenderingParams^ Callback_OnSetTextRenderingParams = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSetTransform) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetTransform(_In_ CONST D2D1_MATRIX_3X2_F* transform);
	DelegateNativo_Evento_OnSetTransform^ Callback_OnSetTransform = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnBeginDraw) nativo da classe (CLN_D2D1CommandSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnSetUnitMode(D2D1_UNIT_MODE unitMode);
	DelegateNativo_Evento_OnSetUnitMode^ Callback_OnSetUnitMode = nullptr;


	//Handles alocadas de cada Delegate.
private:

	//Handles da interface ICarenD2D1CommandSink1.

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetPrimitiveBlend1).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetPrimitiveBlend1;



	//Handles da interface ICarenD2D1CommandSink

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnBeginDraw).
	/// </summary>
	GCHandle gHandle_Delegate_OnBeginDraw;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnClear).
	/// </summary>
	GCHandle gHandle_Delegate_OnClear;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawBitmap).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawBitmap;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawGdiMetafile).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawGdiMetafile;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawGeometry).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawGeometry;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawGlyphRun).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawGlyphRun;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawImage).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawImage;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawLine).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawLine;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDrawRectangle).
	/// </summary>
	GCHandle gHandle_Delegate_OnDrawRectangle;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnEndDraw).
	/// </summary>
	GCHandle gHandle_Delegate_OnEndDraw;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFillGeometry).
	/// </summary>
	GCHandle gHandle_Delegate_OnFillGeometry;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFillMesh).
	/// </summary>
	GCHandle gHandle_Delegate_OnFillMesh;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFillOpacityMask).
	/// </summary>
	GCHandle gHandle_Delegate_OnFillOpacityMask;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFillRectangle).
	/// </summary>
	GCHandle gHandle_Delegate_OnFillRectangle;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnPopAxisAlignedClip).
	/// </summary>
	GCHandle gHandle_Delegate_OnPopAxisAlignedClip;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnPopLayer).
	/// </summary>
	GCHandle gHandle_Delegate_OnPopLayer;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnPushAxisAlignedClip).
	/// </summary>
	GCHandle gHandle_Delegate_OnPushAxisAlignedClip;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnPushLayer).
	/// </summary>
	GCHandle gHandle_Delegate_OnPushLayer;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetAntialiasMode).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetAntialiasMode;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetPrimitiveBlend).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetPrimitiveBlend;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetTags).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetTags;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetTextAntialiasMode).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetTextAntialiasMode;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetTextRenderingParams).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetTextRenderingParams;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetTransform).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetTransform;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSetUnitMode).
	/// </summary>
	GCHandle gHandle_Delegate_OnSetUnitMode;


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenD2D1CommandSink1::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenD2D1CommandSink1)
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();



	//Métodos que recebem os eventos da classe nativa (CLN_D2D1CommandSink1)
public:
	virtual void EncaminharEvento_OnSetPrimitiveBlend1(D2D1_PRIMITIVE_BLEND primitiveBlend);



	//Métodos que recebem os eventos da classe nativa (CLN_D2D1CommandSink)
public:
	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnBeginDraw) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnBeginDraw();

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnClear) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnClear(_In_opt_ CONST D2D1_COLOR_F* color);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawBitmap) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawBitmap(
		_In_ ID2D1Bitmap* bitmap,
		_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
		FLOAT opacity,
		D2D1_INTERPOLATION_MODE interpolationMode,
		_In_opt_ CONST D2D1_RECT_F* sourceRectangle,
		_In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawGdiMetafile) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawGdiMetafile(
		_In_ ID2D1GdiMetafile* gdiMetafile,
		_In_opt_ CONST D2D1_POINT_2F* targetOffset);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawGeometry) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawGeometry(
		_In_ ID2D1Geometry* geometry,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawGlyphRun) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawGlyphRun(
		D2D1_POINT_2F baselineOrigin,
		_In_ CONST DWRITE_GLYPH_RUN* glyphRun,
		_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
		_In_ ID2D1Brush* foregroundBrush,
		DWRITE_MEASURING_MODE measuringMode);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawImage) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawImage(
		_In_ ID2D1Image* image,
		_In_opt_ CONST D2D1_POINT_2F* targetOffset,
		_In_opt_ CONST D2D1_RECT_F* imageRectangle,
		D2D1_INTERPOLATION_MODE interpolationMode,
		D2D1_COMPOSITE_MODE compositeMode);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawLine) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawLine(
		D2D1_POINT_2F point0,
		D2D1_POINT_2F point1,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDrawRectangle) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDrawRectangle(
		_In_ CONST D2D1_RECT_F* rect,
		_In_ ID2D1Brush* brush,
		FLOAT strokeWidth,
		_In_opt_ ID2D1StrokeStyle* strokeStyle);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnEndDraw) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnEndDraw();

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnFillGeometry) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFillGeometry(
		_In_ ID2D1Geometry* geometry,
		_In_ ID2D1Brush* brush,
		_In_opt_ ID2D1Brush* opacityBrush);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnFillMesh) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFillMesh(
		_In_ ID2D1Mesh* mesh,
		_In_ ID2D1Brush* brush);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnFillOpacityMask) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFillOpacityMask(
		_In_ ID2D1Bitmap* opacityMask,
		_In_ ID2D1Brush* brush,
		_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
		_In_opt_ CONST D2D1_RECT_F* sourceRectangle);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnFillRectangle) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFillRectangle(
		_In_ CONST D2D1_RECT_F* rect,
		_In_ ID2D1Brush* brush);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnPopAxisAlignedClip) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnPopAxisAlignedClip();

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnPopLayer) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnPopLayer();

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnPushAxisAlignedClip) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnPushAxisAlignedClip(
		_In_ CONST D2D1_RECT_F* clipRect,
		D2D1_ANTIALIAS_MODE antialiasMode);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnPushLayer) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnPushLayer(
		_In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
		_In_opt_ ID2D1Layer* layer);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetAntialiasMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetPrimitiveBlend) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetPrimitiveBlend(D2D1_PRIMITIVE_BLEND primitiveBlend);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetTags) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetTags(
		D2D1_TAG tag1,
		D2D1_TAG tag2);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetTextAntialiasMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetTextRenderingParams) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetTextRenderingParams(_In_opt_ IDWriteRenderingParams* textRenderingParams);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetTransform) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetTransform(_In_ CONST D2D1_MATRIX_3X2_F* transform);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnSetUnitMode) da classe (ID2D1CommandSink) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnSetUnitMode(D2D1_UNIT_MODE unitMode);
};