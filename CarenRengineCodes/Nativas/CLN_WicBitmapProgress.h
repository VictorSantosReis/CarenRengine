#pragma once
#include "../SDK_Base.h"


/// <summary>
/// Classe responsável por conter o método que vai receber o progresso de notificação de um codificador ou decodificador.
/// Está classe não implementa a interface nativa (IWICBitmapCodecProgressNotification), serve apenas de auxiliar.
/// </summary>
class CLN_WicBitmapProgress
{
	//Construtores e destuidores da classe.
public:
	CLN_WicBitmapProgress();
	~CLN_WicBitmapProgress();


	//Declaração do evento de progresso.
public:
	PFNProgressNotification Evento_Progresso;


	//Declração do método que recebe o evento.
public:
	HRESULT Pfnprogressnotification(
		LPVOID pvData,
		ULONG uFrameNum,
		WICProgressOperation operation,
		double dblProgress
	);
};


