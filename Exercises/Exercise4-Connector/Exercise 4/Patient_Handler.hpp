#pragma once

#include "Event_handler.hpp"
#include <WinSock2.h>

class Patient_Handler : public Event_Handler
{
public:
	virtual ~Patient_Handler();

	Patient_Handler();
	void handle_event(HANDLE h, Event_type eType);
	virtual HANDLE get_handle() const;
};