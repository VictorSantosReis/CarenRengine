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


#pragma once
#include "../SDK_Base.h"

//Typedefs que definem os delegates de eventos que seram chamados para notificar o usuario.
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_BeginDraw)();
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_EndDraw)();
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetAntialiasMode)(D2D1_ANTIALIAS_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetTags)(D2D1_TAG, D2D1_TAG);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetTextAntialiasMode)(D2D1_TEXT_ANTIALIAS_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetTextRenderingParams)(IDWriteRenderingParams*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetTransform)(_In_ CONST D2D1_MATRIX_3X2_F*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetPrimitiveBlend)(D2D1_PRIMITIVE_BLEND);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_SetUnitMode)(D2D1_UNIT_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_Clear)(_In_opt_ CONST D2D1_COLOR_F*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawGlyphRun)(D2D1_POINT_2F, _In_ CONST DWRITE_GLYPH_RUN*, _In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION*, ID2D1Brush*, DWRITE_MEASURING_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawLine)(D2D1_POINT_2F, D2D1_POINT_2F, ID2D1Brush*, FLOAT, _In_opt_ ID2D1StrokeStyle*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawGeometry)(_In_ ID2D1Geometry*, _In_ ID2D1Brush*, FLOAT, _In_opt_ ID2D1StrokeStyle*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawRectangle)(_In_ CONST D2D1_RECT_F*, ID2D1Brush*, FLOAT, _In_opt_ ID2D1StrokeStyle*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawBitmap)(_In_ ID2D1Bitmap*, _In_opt_ CONST D2D1_RECT_F*, FLOAT, D2D1_INTERPOLATION_MODE, _In_opt_ CONST D2D1_RECT_F*, _In_opt_ CONST D2D1_MATRIX_4X4_F*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawImage)(_In_ ID2D1Image*, _In_opt_ CONST D2D1_POINT_2F*, _In_opt_ CONST D2D1_RECT_F*, D2D1_INTERPOLATION_MODE, D2D1_COMPOSITE_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_DrawGdiMetafile)(_In_ ID2D1GdiMetafile*, _In_opt_ CONST D2D1_POINT_2F*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_FillMesh)(_In_ ID2D1Mesh*, _In_ ID2D1Brush*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_FillOpacityMask)(_In_ ID2D1Bitmap*, _In_ ID2D1Brush*, _In_opt_ CONST D2D1_RECT_F*, _In_opt_ CONST D2D1_RECT_F*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_FillGeometry)(_In_ ID2D1Geometry*, _In_ ID2D1Brush*, _In_opt_ ID2D1Brush*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_FillRectangle)(_In_ CONST D2D1_RECT_F*, _In_ ID2D1Brush*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_PushAxisAlignedClip)(_In_ CONST D2D1_RECT_F*, D2D1_ANTIALIAS_MODE);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_PushLayer)(_In_ CONST D2D1_LAYER_PARAMETERS1*, _In_opt_ ID2D1Layer*);
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_PopAxisAlignedClip)();
typedef void(__stdcall* CLN_ID2D1CommandSink_EventoNativo_PopLayer)();

#define METODODELC HRESULT __stdcall



/// <summary>
/// Classe responsável por implementar a interface (ID2D1CommandSink) que vai receber uma reprodução de comandos graficos.
/// </summary>
class CLN_ID2D1CommandSink : public ID2D1CommandSink
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

    //Sessão critica de código.
    CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_ID2D1CommandSink() : RefCount(1)
	{
        //Inicia a sessão critica.
        BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);

        //Verifica o resultado
        if (Resultado)
        {

        }
	}

	//Destruição da classe.
	~CLN_ID2D1CommandSink()
	{
        //Deleta a sessão critica
        DeleteCriticalSection(&SessaoCritica);
	}

	//Contém todos os Eventos que seram chamados para notificar o usuário.
public:

	//Eventos nativos.
    CLN_ID2D1CommandSink_EventoNativo_BeginDraw Evento_BeginDraw = NULL;
    CLN_ID2D1CommandSink_EventoNativo_EndDraw Evento_EndDraw = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetAntialiasMode Evento_SetAntialiasMode = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetTags Evento_SetTags = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetTextAntialiasMode Evento_SetTextAntialiasMode = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetTextRenderingParams Evento_SetTextRenderingParams = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetTransform Evento_SetTransform = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetPrimitiveBlend Evento_SetPrimitiveBlend = NULL;
    CLN_ID2D1CommandSink_EventoNativo_SetUnitMode Evento_SetUnitMode = NULL;
    CLN_ID2D1CommandSink_EventoNativo_Clear Evento_Clear = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawGlyphRun Evento_DrawGlyphRun = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawLine Evento_DrawLine = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawGeometry Evento_DrawGeometry = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawRectangle Evento_DrawRectangle = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawBitmap Evento_DrawBitmap = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawImage Evento_DrawImage = NULL;
    CLN_ID2D1CommandSink_EventoNativo_DrawGdiMetafile Evento_DrawGdiMetafile = NULL;
    CLN_ID2D1CommandSink_EventoNativo_FillMesh Evento_FillMesh = NULL;
    CLN_ID2D1CommandSink_EventoNativo_FillOpacityMask Evento_FillOpacityMask = NULL;
    CLN_ID2D1CommandSink_EventoNativo_FillGeometry Evento_FillGeometry = NULL;
    CLN_ID2D1CommandSink_EventoNativo_FillRectangle Evento_FillRectangle = NULL;
    CLN_ID2D1CommandSink_EventoNativo_PushAxisAlignedClip Evento_PushAxisAlignedClip = NULL;
    CLN_ID2D1CommandSink_EventoNativo_PushLayer Evento_PushLayer = NULL;
    CLN_ID2D1CommandSink_EventoNativo_PopAxisAlignedClip Evento_PopAxisAlignedClip = NULL;
    CLN_ID2D1CommandSink_EventoNativo_PopLayer Evento_PopLayer = NULL;


	//Métodos da Interface IUnknown.
public:
	//Procura uma determina interface nessa classe.
	STDMETHODIMP QueryInterface(REFIID guid, void** pObj)
	{
		if (pObj == NULL)
		{
			return E_POINTER;
		}
		else if (guid == IID_IUnknown) {
			*pObj = this;
			AddRef();
			return S_OK;
		}
		else if (__uuidof(ID2D1CommandSink) == guid)
		{
			AddRef();
			*pObj = (ID2D1CommandSink*)this;
			return S_OK;
		}
		else
		{
			*pObj = NULL;
			return E_NOINTERFACE;
		}
	}

	//Adiciona uma referência a classe.
	STDMETHODIMP_(ULONG) AddRef()
	{
		//Incrementa a quantidade de referências.
		return InterlockedIncrement(&RefCount);
	}

	//Libera uma referência a classe.
	STDMETHODIMP_(ULONG) Release()
	{
		//Desecrementa a quantidade de referências e verifica.
		ULONG result = InterlockedDecrement(&RefCount);
		if (result == 0) delete this;
		return result;
	}


	//Métodos da Interface ID2D1CommandSink
public:

    STDMETHOD(BeginDraw)(
        );

    STDMETHOD(EndDraw)(
        );

    STDMETHOD(SetAntialiasMode)(
        D2D1_ANTIALIAS_MODE antialiasMode
        );

    STDMETHOD(SetTags)(
        D2D1_TAG tag1,
        D2D1_TAG tag2
        );

    STDMETHOD(SetTextAntialiasMode)(
        D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode
        );

    STDMETHOD(SetTextRenderingParams)(
        _In_opt_ IDWriteRenderingParams* textRenderingParams
        );

    STDMETHOD(SetTransform)(
        _In_ CONST D2D1_MATRIX_3X2_F* transform
        );

    STDMETHOD(SetPrimitiveBlend)(
        D2D1_PRIMITIVE_BLEND primitiveBlend
        );

    STDMETHOD(SetUnitMode)(
        D2D1_UNIT_MODE unitMode
        );

    STDMETHOD(Clear)(
        _In_opt_ CONST D2D1_COLOR_F* color
        );

    STDMETHOD(DrawGlyphRun)(
        D2D1_POINT_2F baselineOrigin,
        _In_ CONST DWRITE_GLYPH_RUN* glyphRun,
        _In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
        _In_ ID2D1Brush* foregroundBrush,
        DWRITE_MEASURING_MODE measuringMode
        );

    STDMETHOD(DrawLine)(
        D2D1_POINT_2F point0,
        D2D1_POINT_2F point1,
        _In_ ID2D1Brush* brush,
        FLOAT strokeWidth,
        _In_opt_ ID2D1StrokeStyle* strokeStyle
        );

    STDMETHOD(DrawGeometry)(
        _In_ ID2D1Geometry* geometry,
        _In_ ID2D1Brush* brush,
        FLOAT strokeWidth,
        _In_opt_ ID2D1StrokeStyle* strokeStyle
        );

    STDMETHOD(DrawRectangle)(
        _In_ CONST D2D1_RECT_F* rect,
        _In_ ID2D1Brush* brush,
        FLOAT strokeWidth,
        _In_opt_ ID2D1StrokeStyle* strokeStyle
        );

    STDMETHOD(DrawBitmap)(
        _In_ ID2D1Bitmap* bitmap,
        _In_opt_ CONST D2D1_RECT_F* destinationRectangle,
        FLOAT opacity,
        D2D1_INTERPOLATION_MODE interpolationMode,
        _In_opt_ CONST D2D1_RECT_F* sourceRectangle,
        _In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform
        );

    STDMETHOD(DrawImage)(
        _In_ ID2D1Image* image,
        _In_opt_ CONST D2D1_POINT_2F* targetOffset,
        _In_opt_ CONST D2D1_RECT_F* imageRectangle,
        D2D1_INTERPOLATION_MODE interpolationMode,
        D2D1_COMPOSITE_MODE compositeMode
        );

    STDMETHOD(DrawGdiMetafile)(
        _In_ ID2D1GdiMetafile* gdiMetafile,
        _In_opt_ CONST D2D1_POINT_2F* targetOffset
        );

    STDMETHOD(FillMesh)(
        _In_ ID2D1Mesh* mesh,
        _In_ ID2D1Brush* brush
        );

    STDMETHOD(FillOpacityMask)(
        _In_ ID2D1Bitmap* opacityMask,
        _In_ ID2D1Brush* brush,
        _In_opt_ CONST D2D1_RECT_F* destinationRectangle,
        _In_opt_ CONST D2D1_RECT_F* sourceRectangle
        );

    STDMETHOD(FillGeometry)(
        _In_ ID2D1Geometry* geometry,
        _In_ ID2D1Brush* brush,
        _In_opt_ ID2D1Brush* opacityBrush
        );

    STDMETHOD(FillRectangle)(
        _In_ CONST D2D1_RECT_F* rect,
        _In_ ID2D1Brush* brush
        );

    STDMETHOD(PushAxisAlignedClip)(
        _In_ CONST D2D1_RECT_F* clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode
        );

    STDMETHOD(PushLayer)(
        _In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
        _In_opt_ ID2D1Layer* layer
        );

    STDMETHOD(PopAxisAlignedClip)(
        );

    STDMETHOD(PopLayer)(
        );
};