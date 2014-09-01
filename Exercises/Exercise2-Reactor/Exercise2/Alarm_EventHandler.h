#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"

class Alarm_EventHandler : Event_Handler
{
public:

	Alarm_EventHandler();
	virtual ~Alarm_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;


};