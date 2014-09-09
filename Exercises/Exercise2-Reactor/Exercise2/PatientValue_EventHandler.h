#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"
#include "Reactor.hpp"
#include "SOCK_stream.h"

class PatientValue_EventHandler : public Event_Handler
{
public:

	PatientValue_EventHandler(SOCK_Stream&, Reactor*);
	~PatientValue_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;
private:
	SOCK_Stream _peer_stream;
	Reactor* _reactor;
};