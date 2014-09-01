#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"

class PatientValue_EventHandler : Event_Handler
{
public:

	PatientValue_EventHandler();
	virtual ~PatientValue_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;
};