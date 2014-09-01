#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"

class Log_EventHandler : public Event_Handler
{
public:

	Log_EventHandler();
	~Log_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;
};