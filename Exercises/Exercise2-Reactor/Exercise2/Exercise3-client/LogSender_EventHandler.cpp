#include "stdafx.h"
#include "LogSender_EventHandler.h"
#include "../SOCK_connector.hpp"

#include <iostream>


LogSender_EventHandler::LogSender_EventHandler(const INET_Address& addr, Reactor* reactor) : reactor_(reactor)
{
	SOCK_Connector con;
	con.connect(stream_, addr);
	reactor_->register_handler(this, Event_type::WRITE);
}

void LogSender_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if (eType == Event_type::WRITE)
	{
		std::string msg = "AWESOME LOG MESSAGE!";
		stream_.send(msg.c_str(), msg.length() + 1, 0);
	}
	else
	{
		std::cout << "Error from LogSender" << std::endl;
		reactor_->remove_handler(this, eType);
		//delete this;
	}

}

HANDLE LogSender_EventHandler::get_handle() const
{
	return (HANDLE)stream_.get_handle();
}

LogSender_EventHandler::~LogSender_EventHandler()
{
}
