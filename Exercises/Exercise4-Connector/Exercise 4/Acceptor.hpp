#pragma once
#include "Event_handler.hpp"
#include "Reactor.hpp"
#include "INET_Address.hpp"
#include "SOCK_Acceptor.hpp"

template <class SERVICE_HANDLER>
class Acceptor : public Event_Handler 
{
public:
	Acceptor (const INET_Address &local_addr, Reactor *r)
	{
		// initialize the IPC_ACCEPTOR to listen for connections
		peer_acceptor_.open(local_addr);

		// register with <reactor>
		r->register_handler(this, ACCEPT);
	}
	virtual void handle_event(HANDLE h, Event_type et)
	{
		if (et == ACCEPT)
		{
			accept();
		}
	}
protected:
	virtual void accept()
	{
		// GoF: Factory Method – creates a new <SERVICE_HANDLER>
		SERVICE_HANDLER *service_handler= make_service_handler();

		// Hook method that accepts a connection passively
		accept_service_handler(service_handler);

		// Hook method that activates the <SERVICE_HANDLER> by 
		// invoking its <open> activation hook method
		activate_service_handler(service_handler);
	}
	virtual SERVICE_HANDLER *make_service_handler()
	{
		return new SERVICE_HANDLER;
	}
	virtual void accept_service_handler(SERVICE_HANDLER *handler)
	{
		peer_acceptor_.accept (handler->peer ());
	}
	virtual void activate_service_handler(SERVICE_HANDLER *handler)
	{
		handler->open();
	}
	virtual HANDLE get_handle() const
	{
		return (HANDLE)peer_acceptor_.get_socket();
	}
private:
	SOCK_Acceptor peer_acceptor_; // template placeholder
};
