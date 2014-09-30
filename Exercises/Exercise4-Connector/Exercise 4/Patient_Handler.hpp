#pragma once

#include <WinSock2.h>
#include "Service_Handler.hpp"

class Patient_Handler : public Service_Handler
{
	//Patient_Handlers
	void handle_event(HANDLE h, Event_type eType);
	virtual ~Patient_Handler();
};