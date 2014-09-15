#include "stdafx.h"
#include "Alarm_EventHandler.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <array>

Alarm_EventHandler::Alarm_EventHandler(std::shared_ptr<SOCK_Stream>stream, Reactor *reactor)
	: _peer_stream(stream), _reactor(reactor)
{
	_reactor->register_handler(this, READ);
}

Alarm_EventHandler::~Alarm_EventHandler()
{
	//_reactor->remove_handler(this,READ); //Correct?
	//delete &_peer_stream;
}

void Alarm_EventHandler::handle_event(HANDLE h, Event_type eType)
{

	if(eType == READ)
	{
		std::array<char, 100> buffer;
		buffer.fill(0);

		auto res = _peer_stream->recv(buffer.data(), buffer.size(), 0);

		if (res == 0)
		{
			std::cout << "Alarm_EventHandler: connection closed." << std::endl;
			_reactor->remove_handler(this, eType);
			return;
		}

		time_t t = time(0);
		std::tm timeInfo; 
		localtime_s(&timeInfo, &t);
		
		std::cout << "Current time is: " << std::put_time(&timeInfo, "%c") << std::endl;
		std::cout << "Priority: " << buffer[0] << std::endl;
		std::cout << "Message: " << buffer.data() + 1 << std::endl;
	}
	else
	{
		std::cout << "Error from Alarm_EventHandler" << std::endl;
		_reactor->remove_handler(this, eType);
		delete this;
	}
}

HANDLE Alarm_EventHandler::get_handle() const
{
	return (HANDLE)_peer_stream->get_handle();
}