#include "../pch.h"
#include "../Nativas/CLN_ID2D1CommandSink.h"

METODODELC CLN_ID2D1CommandSink::BeginDraw()
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::EndDraw()
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetAntialiasMode(D2D1_ANTIALIAS_MODE antialiasMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetTags(
	D2D1_TAG tag1,
	D2D1_TAG tag2)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetTextRenderingParams(_In_opt_ IDWriteRenderingParams* textRenderingParams)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetTransform(_In_ CONST D2D1_MATRIX_3X2_F* transform)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND primitiveBlend)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::SetUnitMode(D2D1_UNIT_MODE unitMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::Clear(_In_opt_ CONST D2D1_COLOR_F* color)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawGlyphRun(
	D2D1_POINT_2F baselineOrigin,
	_In_ CONST DWRITE_GLYPH_RUN* glyphRun,
	_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
	_In_ ID2D1Brush* foregroundBrush,
	DWRITE_MEASURING_MODE measuringMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawLine(
	D2D1_POINT_2F point0,
	D2D1_POINT_2F point1,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush,
	FLOAT strokeWidth,
	_In_opt_ ID2D1StrokeStyle* strokeStyle)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawBitmap(
	_In_ ID2D1Bitmap* bitmap,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	FLOAT opacity,
	D2D1_INTERPOLATION_MODE interpolationMode,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle,
	_In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawImage(
	_In_ ID2D1Image* image,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset,
	_In_opt_ CONST D2D1_RECT_F* imageRectangle,
	D2D1_INTERPOLATION_MODE interpolationMode,
	D2D1_COMPOSITE_MODE compositeMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::DrawGdiMetafile(
	_In_ ID2D1GdiMetafile* gdiMetafile,
	_In_opt_ CONST D2D1_POINT_2F* targetOffset)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::FillMesh(
	_In_ ID2D1Mesh* mesh,
	_In_ ID2D1Brush* brush)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::FillOpacityMask(
	_In_ ID2D1Bitmap* opacityMask,
	_In_ ID2D1Brush* brush,
	_In_opt_ CONST D2D1_RECT_F* destinationRectangle,
	_In_opt_ CONST D2D1_RECT_F* sourceRectangle)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::FillGeometry(
	_In_ ID2D1Geometry* geometry,
	_In_ ID2D1Brush* brush,
	_In_opt_ ID2D1Brush* opacityBrush)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::FillRectangle(
	_In_ CONST D2D1_RECT_F* rect,
	_In_ ID2D1Brush* brush)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::PushAxisAlignedClip(
	_In_ CONST D2D1_RECT_F* clipRect,
	D2D1_ANTIALIAS_MODE antialiasMode)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::PushLayer(
	_In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1,
	_In_opt_ ID2D1Layer* layer)
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::PopAxisAlignedClip()
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

METODODELC CLN_ID2D1CommandSink::PopLayer()
{
	//Entra na sess�o critica de cod�go.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento � valido
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
		//Define que o m�todo n�o foi implementado.
		Resultado = E_NOTIMPL;
	}

	//Sai da sess�o critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}