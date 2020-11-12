#include "../pch.h"
#include "CLN_IWICDevelopRawNotificationCallback.h"

HRESULT __stdcall CLN_IWICDevelopRawNotificationCallback::Notify(UINT NotificationMask)
{
    //Entra na sess�o critica de c�digo.
    EnterCriticalSection(&SessaoCritica);

    //Verifica se o evento � valido.
    if (ObjetoValido(Evento_OnNotify))
    {
        //Chama o evento para notificar o usu�rio e retorna o resultado.
        return Evento_OnNotify(NotificationMask);
    }
    else
    {
        //Retorna que o evento n�o foi implementado.
        return E_NOTIMPL;
    }

    //Sai da sess�o critica de c�digo.
    LeaveCriticalSection(&SessaoCritica);
}
