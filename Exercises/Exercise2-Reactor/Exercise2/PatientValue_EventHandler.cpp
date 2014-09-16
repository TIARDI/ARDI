#include "stdafx.h"
#include "PatientValue_EventHandler.h"
#include <iostream>
#include <array>

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
		std::array<char, 100> buffer;
		buffer.fill(0);

		auto res = _peer_stream->recv(buffer.data(), buffer.size() - 1, 0);

		if (res == 0)
		{
			std::cout << "patientValue_EventHandler: connection closed." << std::endl;
			_reactor->remove_handler(this, eType);
			return;
		}
		std::cout << "Type: " << buffer[0] << std::endl;
		std::cout << "Value: " << buffer.data() + 1 << std::endl;
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