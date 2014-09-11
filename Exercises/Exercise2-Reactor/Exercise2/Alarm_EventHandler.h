#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"
#include "SOCK_stream.h"
#include "Reactor.hpp"
#include <memory>

class Alarm_EventHandler : public Event_Handler
{
public:
	Alarm_EventHandler(std::shared_ptr<SOCK_Stream>, Reactor*);
	~Alarm_EventHandler();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;
private:
	std::shared_ptr<SOCK_Stream> _peer_stream;
	Reactor *_reactor;
};