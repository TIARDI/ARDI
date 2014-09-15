#pragma once
#include <winsock2.h>
#include <iostream>
#include <string>
#include "Event_handler.hpp"
#include "Reactor.hpp"
#include "SOCK_stream.h"
#include <memory>

class Log_EventHandler : public Event_Handler
{
public:

	Log_EventHandler(std::shared_ptr<SOCK_Stream>, Reactor*);
	~Log_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;

private:
	std::shared_ptr<SOCK_Stream> _peer_stream;
	Reactor *_reactor;
};