#include "stdafx.h"
#include "LogSender_EventHandler.h"
#include "../SOCK_connector.hpp"

#include <iostream>


LogSender_EventHandler::LogSender_EventHandler(const INET_Address& addr, Reactor* reactor) : reactor_(reactor)
{
	SOCK_Connector con;
	con.connect(stream_, addr);
}

void LogSender_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if (eType == WRITE)
	{
		std::string msg = "SICK LOG MSG!";
		stream_.send(msg.c_str(), msg.length() + 1, 0);
	}
	else
	{
		std::cout << "Error from LogSender" << std::endl;
		reactor_->remove_handler(this, eType);
		delete this;
	}

}


LogSender_EventHandler::~LogSender_EventHandler()
{
}
