#include "../pch.h"
#include "CLN_WicBitmapProgress.h"

CLN_WicBitmapProgress::CLN_WicBitmapProgress()
{

}

CLN_WicBitmapProgress::~CLN_WicBitmapProgress()
{

}

HRESULT CLN_WicBitmapProgress::Pfnprogressnotification(LPVOID pvData, ULONG uFrameNum, WICProgressOperation operation, double dblProgress)
{
	//Verifica se o evento � valido
	if (ObjetoValido(Evento_Progresso))
	{
		//Chama o evento para notificar o usu�rio.
		return Evento_Progresso(pvData, uFrameNum, operation, dblProgress);
	}
	else
	{
		//Retorna que n�o foi implementado o evento.
		return E_NOTIMPL;
	}
}
