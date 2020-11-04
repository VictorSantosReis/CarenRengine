#pragma once
#include "../SDK_Base.h"


/// <summary>
/// Classe respons�vel por conter o m�todo que vai receber o progresso de notifica��o de um codificador ou decodificador.
/// Est� classe n�o implementa a interface nativa (IWICBitmapCodecProgressNotification), serve apenas de auxiliar.
/// </summary>
class CLN_WicBitmapProgress
{
	//Construtores e destuidores da classe.
public:
	CLN_WicBitmapProgress();
	~CLN_WicBitmapProgress();


	//Declara��o do evento de progresso.
public:
	PFNProgressNotification Evento_Progresso;


	//Declra��o do m�todo que recebe o evento.
public:
	HRESULT Pfnprogressnotification(
		LPVOID pvData,
		ULONG uFrameNum,
		WICProgressOperation operation,
		double dblProgress
	);
};


