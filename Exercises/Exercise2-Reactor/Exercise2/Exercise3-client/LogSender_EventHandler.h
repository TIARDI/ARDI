#pragma once
#include <winsock2.h>
#include "../Event_handler.hpp"
#include "../SOCK_stream.h"
#include "../INET_Address.hpp"
#include "../Reactor.hpp"

class LogSender_EventHandler : public Event_Handler
{
public:
	LogSender_EventHandler(const INET_Address& addr, Reactor* reactor);
	virtual void handle_event(HANDLE h, Event_type eType);
	virtual ~LogSender_EventHandler();

private:
	SOCK_Stream stream_;
	Reactor* reactor_;
};

