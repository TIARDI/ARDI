#include "stdafx.h"
#include "Alarm_EventHandler.h"
#include <iostream>
#include <ctime>

Alarm_EventHandler::Alarm_EventHandler(const SOCK_Stream &stream, Reactor *reactor) 
	: _peer_stream(stream), _reactor(reactor)
{
	_reactor->register_handler(this, READ);
}

Alarm_EventHandler::~Alarm_EventHandler()
{
	_reactor->remove_handler(this,READ); //Correct?
	delete _reactor;
}

void Alarm_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if(eType == READ)
	{
		time_t t = time(0);
		struct tm timeInfo; 
		localtime_s(&timeInfo, &t);
		
		std::cout << "Current time is: " 
		<< timeInfo.tm_hour << ":"
		<< timeInfo.tm_min << ":"
		<< timeInfo.tm_sec
		<< " on the "
		<< timeInfo.tm_mday << "/"
		<< timeInfo.tm_mon  + 1 << "-"
		<< timeInfo.tm_year + 1900 
		<< std::endl;
	}
	else
	{
		std::cout << "Error from Alarm_EventHandler" << std::endl;
		_reactor->remove_handler(this,READ);
		delete this;
	}


}

HANDLE Alarm_EventHandler::get_handle() const
{
	return (HANDLE)_peer_stream.get_handle();
}