#pragma once
#include "../Event_handler.hpp"
#include "../SOCK_stream.h"
#include "../INET_Address.hpp"
#include "../Reactor.hpp"

class AlarmSender_EventHandler : public Event_Handler
{
public:
	virtual ~AlarmSender_EventHandler();

	AlarmSender_EventHandler(const INET_Address& addr, Reactor* reactor);
	virtual void handle_event(HANDLE h, Event_type eType);
	virtual HANDLE get_handle() const;

private:
	SOCK_Stream stream_;
	Reactor* reactor_;
};

