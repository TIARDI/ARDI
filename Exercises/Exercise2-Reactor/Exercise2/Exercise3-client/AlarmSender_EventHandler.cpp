#include "stdafx.h"
#include "AlarmSender_EventHandler.hpp"

#include "../SOCK_connector.hpp"
#include <iostream>


AlarmSender_EventHandler::AlarmSender_EventHandler(const INET_Address& addr, Reactor* reactor) : reactor_(reactor)
{
	SOCK_Connector con;
	con.connect(stream_, addr);
	reactor_->register_handler(this, Event_type::WRITE);
}

AlarmSender_EventHandler::~AlarmSender_EventHandler()
{
}

void AlarmSender_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if (eType == Event_type::WRITE)
	{
		std::string msg = "ASomething-something alarm message!!";
		stream_.send(msg.c_str(), msg.length() + 1, 0);
	}
	else
	{
		std::cout << "Error from AlarmSender" << std::endl;
		reactor_->remove_handler(this, eType);
		//delete this;
	}

}

HANDLE AlarmSender_EventHandler::get_handle() const
{
	return (HANDLE)stream_.get_handle();
}
