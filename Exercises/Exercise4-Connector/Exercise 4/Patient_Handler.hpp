#pragma once

#include <WinSock2.h>
#include "Service_Handler.hpp"

typedef Service_Handler<SOCK_Stream> STREAM_HANDLER;
class Patient_Handler : public STREAM_HANDLER
{
	//Patient_Handlers
	void handle_event(HANDLE h, Event_type eType);
	virtual ~Patient_Handler();
};