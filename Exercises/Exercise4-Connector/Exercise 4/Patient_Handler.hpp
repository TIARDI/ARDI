#pragma once

#include "Event_handler.hpp"
#include <WinSock2.h>

class Patient_Handler : public Event_Handler
{
	//Patient_Handlers
	void handle_event(HANDLE h, Event_type eType);
	virtual ~Patient_Handler();
};