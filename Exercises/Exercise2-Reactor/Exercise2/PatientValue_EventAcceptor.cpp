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
		SOCK_Stream client_conn;
		acceptor_.accept(client_conn);
		PatientValue_EventHandler *patientvalue_handler = new PatientValue_EventHandler(client_conn,reactor_);
	}
}
HANDLE PatientValue_EventAcceptor::get_handle() const
{
	return (HANDLE)acceptor_.get_handle();
}