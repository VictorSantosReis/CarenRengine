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
#include "../pch.h"
#include "../Nativas/CLN_ID2D1CommandSink4.h"


//Métodos da interface ID2D1CommandSink4

METODODELC CLN_ID2D1CommandSink4::SetPrimitiveBlend2(D2D1_PRIMITIVE_BLEND primitiveBlend)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetPrimitiveBlend2))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetPrimitiveBlend2(primitiveBlend);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}


//Métodos da interface ID2D1CommandSink3

METODODELC CLN_ID2D1CommandSink4::DrawSpriteBatch(_In_ ID2D1SpriteBatch* spriteBatch, UINT32 startIndex, UINT32 spriteCount, _In_ ID2D1Bitmap* bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, D2D1_SPRITE_OPTIONS spriteOptions)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawSpriteBatch))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawSpriteBatch(spriteBatch, startIndex, spriteCount, bitmap, interpolationMode, spriteOptions);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}


//Métodos da interface ID2D1CommandSink2

METODODELC CLN_ID2D1CommandSink4::DrawInk(_In_ ID2D1Ink* ink, _In_ ID2D1Brush* brush, _In_opt_ ID2D1InkStyle* inkStyle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawInk))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawInk(ink, brush, inkStyle);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawGradientMesh(_In_ ID2D1GradientMesh* gradientMesh)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawGradientMesh))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawGradientMesh(gradientMesh);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawGdiMetafile(_In_ ID2D1GdiMetafile* gdiMetafile, _In_opt_ CONST D2D1_RECT_F* destinationRectangle, _In_opt_ CONST D2D1_RECT_F* sourceRectangle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawGdiMetafile1))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawGdiMetafile1(gdiMetafile, destinationRectangle, sourceRectangle);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}



//Métodos da interface ID2D1CommandSink1

METODODELC CLN_ID2D1CommandSink4::SetPrimitiveBlend1(D2D1_PRIMITIVE_BLEND primitiveBlend)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetPrimitiveBlend1))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetPrimitiveBlend1(primitiveBlend);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}




//Métodos da interface ID2D1CommandSink

METODODELC CLN_ID2D1CommandSink4::BeginDraw()
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_BeginDraw))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_BeginDraw();

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::EndDraw()
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_EndDraw))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_EndDraw();

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetAntialiasMode))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetAntialiasMode(antialiasMode);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetTags(
	D2D1_TAG tag1,
	D2D1_TAG tag2)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetTags))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetTags(tag1, tag2);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetTextAntialiasMode))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetTextAntialiasMode(textAntialiasMode);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetTextRenderingParams(_In_opt_ IDWriteRenderingParams* textRenderingParams)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetTextRenderingParams))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetTextRenderingParams(textRenderingParams);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetTransform(_In_ CONST D2D1_MATRIX_3X2_F* transform)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetTransform))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetTransform(transform);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND primitiveBlend)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetPrimitiveBlend))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetPrimitiveBlend(primitiveBlend);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::SetUnitMode(D2D1_UNIT_MODE unitMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_SetUnitMode))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_SetUnitMode(unitMode);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::Clear(_In_opt_ CONST D2D1_COLOR_F* color)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_Clear))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_Clear(color);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawGlyphRun(
	D2D1_POINT_2F baselineOrigin,
	_In_ CONST DWRITE_GLYPH_RUN* glyphRun,
	_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
	_In_ ID2D1Brush* foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawGlyphRun))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawGlyphRun(
			baselineOrigin,
			glyphRun,
			glyphRunDescription,
			foregroundBrush,
			measuringMode
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawLine(
	D2D1_POINT_2F point0,
	D2D1_POINT_2F point1,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawLine))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawLine(
			point0,
			point1,
			brush,
			strokeWidth,
			strokeStyle
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawGeometry))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawGeometry(
			geometry,
			brush,
			strokeWidth,
			strokeStyle
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawRectangle))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawRectangle(
			rect,
			brush,
			strokeWidth,
			strokeStyle
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawBitmap(
	_In_ ID2D1Bitmap* bitmap,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	FLOAT opacity,
	D2D1_INTERPOLATION_MODE interpolationMode,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle,
	_In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawBitmap))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawBitmap(
			bitmap,
			destinationRectangle,
			opacity,
			interpolationMode,
			sourceRectangle,
			perspectiveTransform
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawImage(
	_In_ ID2D1Image* image,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset,
	_In_opt_ CONST D2D1_RECT_F* imageRectangle,
	D2D1_INTERPOLATION_MODE interpolationMode,
	D2D1_COMPOSITE_MODE compositeMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawImage))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawImage(
			image,
			targetOffset,
			imageRectangle,
			interpolationMode,
			compositeMode
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::DrawGdiMetafile(
	_In_ ID2D1GdiMetafile* gdiMetafile,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_DrawGdiMetafile))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_DrawGdiMetafile(
			gdiMetafile,
			targetOffset
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::FillMesh(
	_In_ ID2D1Mesh* mesh,
	_In_ ID2D1Brush* brush)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_FillMesh))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_FillMesh(
			mesh,
			brush);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::FillOpacityMask(
	_In_ ID2D1Bitmap* opacityMask,
	_In_ ID2D1Brush* brush,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_FillOpacityMask))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_FillOpacityMask(
			opacityMask,
			brush,
			destinationRectangle,
			sourceRectangle
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::FillGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	_In_opt_ ID2D1Brush* opacityBrush)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_FillGeometry))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_FillGeometry(
			geometry,
			brush,
			opacityBrush
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::FillRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_FillRectangle))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_FillRectangle(
			rect,
			brush
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::PushAxisAlignedClip(
	_In_ CONST D2D1_RECT_F* clipRect,
	D2D1_ANTIALIAS_MODE antialiasMode)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_PushAxisAlignedClip))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_PushAxisAlignedClip(
			clipRect,
			antialiasMode
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::PushLayer(
	_In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
	_In_opt_ ID2D1Layer* layer)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_PushLayer))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_PushLayer(
			layerParameters1,
			layer
		);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::PopAxisAlignedClip()
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_PopAxisAlignedClip))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_PopAxisAlignedClip();

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink4::PopLayer()
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_PopAxisAlignedClip))
	{
		//Evento valido.
		//Chama o evento para notificar a classe gerenciada base.
		Evento_PopAxisAlignedClip();

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Define que o método não foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}