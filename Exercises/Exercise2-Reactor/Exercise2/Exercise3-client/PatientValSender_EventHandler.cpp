#include "stdafx.h"
#include "PatientValSender_EventHandler.hpp"
#include "../SOCK_connector.hpp"
#include <iostream>


PatientValSender_EventHandler::PatientValSender_EventHandler(const INET_Address& addr, Reactor* reactor) : reactor_(reactor)
{
	SOCK_Connector con;
	con.connect(stream_, addr);
	reactor_->register_handler(this, Event_type::WRITE);
}


PatientValSender_EventHandler::~PatientValSender_EventHandler()
{
}

void PatientValSender_EventHandler::handle_event(HANDLE h, Event_type eType)
{
	if (eType == Event_type::WRITE)
	{
		std::string msg = "H60BPM";
		stream_.send(msg.c_str(), msg.length() + 1, 0);
	}
	else
	{
		std::cout << "Error from PatientValSender" << std::endl;
		reactor_->remove_handler(this, eType);
		//delete this;
	}

}

HANDLE PatientValSender_EventHandler::get_handle() const
{
	return (HANDLE)stream_.get_handle();
}