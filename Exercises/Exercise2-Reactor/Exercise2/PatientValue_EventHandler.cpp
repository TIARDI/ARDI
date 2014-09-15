#include "stdafx.h"
#include "PatientValue_EventHandler.h"
#include <iostream>

PatientValue_EventHandler::PatientValue_EventHandler(std::shared_ptr<SOCK_Stream> stream, Reactor* reactor)
	: _peer_stream(stream), _reactor(reactor)
{
	_reactor->register_handler(this, READ);
}

PatientValue_EventHandler::~PatientValue_EventHandler()
{
}

void PatientValue_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if(eType == READ)
	{
		char buf;
		std::cout << _peer_stream->recv(&buf, sizeof buf, 0) << std::endl;
	}
	else
	{
		std::cout << "Error from PatinetValue" << std::endl;
		_reactor->remove_handler(this, eType);
		delete this;
	}
}

HANDLE PatientValue_EventHandler::get_handle() const
{
	return (HANDLE)_peer_stream->get_handle();
}