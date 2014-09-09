#include "stdafx.h"
#include "Alarm_EventAcceptor.hpp"

Alarm_EventAcceptor::Alarm_EventAcceptor(const INET_Address &addr, Reactor *reactor) : acceptor_(addr),reactor_(reactor)
{
	reactor_->register_handler(this,Event_type::ACCEPT);
}
Alarm_EventAcceptor::~Alarm_EventAcceptor()
{
}
	
void Alarm_EventAcceptor::handle_event(HANDLE h, Event_type eType)
{
	if(eType == Event_type::ACCEPT)
	{
		SOCK_Stream* client_conn = new SOCK_Stream();
		acceptor_.accept(*client_conn);
		Alarm_EventHandler *alarm_handler = new Alarm_EventHandler(*client_conn,reactor_);
	}
}
HANDLE Alarm_EventAcceptor::get_handle() const
{
	return (HANDLE)acceptor_.get_handle();
}