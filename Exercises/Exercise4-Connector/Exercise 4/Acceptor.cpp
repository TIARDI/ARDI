#include "stdafx.h"
#include "Acceptor.hpp"

template <class SERVICE_HANDLER>
Acceptor<SERVICE_HANDLER>::Acceptor(const INET_Address &local_addr, Reactor *reactor)
{
	// initialize the IPC_ACCEPTOR to listen for connections
	peer_acceptor_.open(local_addr);

	// register with <reactor>
	reactor->register_handler(this, ACCEPT_MASK);
}

template <class SERVICE_HANDLER>
void Acceptor<SERVICE_HANDLER>::accept()
{
	// GoF: Factory Method – creates a new <SERVICE_HANDLER>
	SERVICE_HANDLER *service_handler= make_service_handler();

	// Hook method that accepts a connection passively
	accept_service_handler(service_handler);

	// Hook method that activates the <SERVICE_HANDLER> by 
	// invoking its <open> activation hook method
	activate_service_handler(service_handler);
}

template <class SERVICE_HANDLER>
typename SERVICE_HANDLER *Acceptor<SERVICE_HANDLER>::make_service_handler()
{
	return new SERVICE_HANDLER;
}

template <class SERVICE_HANDLER>
void Acceptor<SERVICE_HANDLER>::accept_service_handler(SERVICE_HANDLER * handler)
{
	peer_acceptor_->accept (handler->peer ());
}

template <class SERVICE_HANDLER>
void Acceptor<SERVICE_HANDLER>::activate_service_handler(SERVICE_HANDLER * handler)
{
	handler->open ();
}
