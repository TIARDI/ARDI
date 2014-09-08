#include "stdafx.h"
#include "Log_EventAcceptor.hpp"

Log_EventAcceptor::Log_EventAcceptor(const INET_Address &addr, Reactor *reactor) : acceptor_(addr),reactor_(reactor)
{
	reactor_->register_handler(this,Event_type::ACCEPT);
}
Log_EventAcceptor::~Log_EventAcceptor()
{
}
	
void Log_EventAcceptor::handle_event(HANDLE h, Event_type eType)
{
	if(eType == Event_type::ACCEPT)
	{
		SOCK_Stream client_conn;
		acceptor_.accept(client_conn);
		Log_EventHandler *log_handler = new Log_EventHandler(client_conn, reactor_);
	}
}
HANDLE Log_EventAcceptor::get_handle() const
{
	return (HANDLE)acceptor_.get_handle();
}