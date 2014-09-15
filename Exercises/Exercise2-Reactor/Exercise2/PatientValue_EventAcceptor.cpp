#include "stdafx.h"
#include "PatientValue_EventAcceptor.hpp"

PatientValue_EventAcceptor::PatientValue_EventAcceptor(const INET_Address &addr, Reactor *reactor) : acceptor_(addr),reactor_(reactor)
{
	reactor_->register_handler(this,Event_type::ACCEPT);
}
PatientValue_EventAcceptor::~PatientValue_EventAcceptor()
{
}

void PatientValue_EventAcceptor::handle_event(HANDLE h, Event_type eType)
{
	if(eType == Event_type::ACCEPT)
	{
		auto client_conn = std::make_shared<SOCK_Stream>();
		acceptor_.accept(*client_conn);
		new PatientValue_EventHandler(client_conn, reactor_);
	}
}
HANDLE PatientValue_EventAcceptor::get_handle() const
{
	return (HANDLE)acceptor_.get_handle();
}