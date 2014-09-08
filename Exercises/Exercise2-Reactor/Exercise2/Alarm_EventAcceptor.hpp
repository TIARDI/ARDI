#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"
#include "Alarm_EventHandler.h"
#include "SOCK_Acceptor.hpp"
#include "SOCK_stream.h"
#include "INET_Address.hpp"
#include "Reactor.hpp"

class Alarm_EventAcceptor : public Event_Handler
{
public:
	Alarm_EventAcceptor(const INET_Address &addr, Reactor *reactor);
	~Alarm_EventAcceptor();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;

private:
	SOCK_Acceptor acceptor_;
	Reactor *reactor_;
};