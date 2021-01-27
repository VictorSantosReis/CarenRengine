#include "../pch.h"
#include "CLN_IWICDevelopRawNotificationCallback.h"

HRESULT __stdcall CLN_IWICDevelopRawNotificationCallback::Notify(UINT NotificationMask)
{
    //Entra na sessão critica de código.
    EnterCriticalSection(&SessaoCritica);

    //Verifica se o evento é valido.
    if (ObjetoValido(Evento_OnNotify))
    {
        //Chama o evento para notificar o usuário e retorna o resultado.
        return Evento_OnNotify(NotificationMask);
    }
    else
    {
        //Retorna que o evento não foi implementado.
        return E_NOTIMPL;
    }

    //Sai da sessão critica de código.
    LeaveCriticalSection(&SessaoCritica);
}
