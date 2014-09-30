#include "stdafx.h"
#include "Acceptor.hpp"

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
Acceptor<SERVICE_HANDLER, IPC_ACCEPTOR>::Acceptor(const Addr &local_addr, 
												  Reactor *reactor)
{
	// initialize the IPC_ACCEPTOR to listen for connections
	peer_acceptor_.open(local_addr);

	// register with <reactor>
	reactor->register_handler(this, ACCEPT_MASK);
}

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
void Acceptor<SERVICE_HANDLER, IPC_ACCEPTOR>::accept()
{
	// GoF: Factory Method – creates a new <SERVICE_HANDLER>
	SERVICE_HANDLER *service_handler= make_service_handler();

	// Hook method that accepts a connection passively
	accept_service_handler(service_handler);

	// Hook method that activates the <SERVICE_HANDLER> by 
	// invoking its <open> activation hook method
	activate_service_handler(service_handler);
}

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
typename SERVICE_HANDLER *Acceptor<SERVICE_HANDLER, IPC_ACCEPTOR>::make_service_handler()
{
	return new SERVICE_HANDLER;
}

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
void Acceptor<SERVICE_HANDLER, IPC_ACCEPTOR>::accept_service_handler(SERVICE_HANDLER * handler)
{
	peer_acceptor_->accept (handler->peer ());
}

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
void Acceptor<SERVICE_HANDLER, IPC_ACCEPTOR>::activate_service_handler(SERVICE_HANDLER * handler)
{
	handler->open ();
}
