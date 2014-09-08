#pragma once
#include <winsock2.h>
#include "Event_handler.hpp"
#include "PatientValue_EventHandler.h"
#include "SOCK_Acceptor.hpp"
#include "SOCK_stream.h"
#include "INET_Address.hpp"
#include "Reactor.hpp"

class PatientValue_EventAcceptor : public Event_Handler
{
public:
	PatientValue_EventAcceptor(const INET_Address &addr, Reactor *reactor);
	~PatientValue_EventAcceptor();
	
	void handle_event(HANDLE h, Event_type eType);
	HANDLE get_handle() const;

private:
	SOCK_Acceptor acceptor_;
	Reactor *reactor_;
};