#pragma once
#include "Event_handler.hpp"
#include "Reactor.hpp"
#include "INET_Address.hpp"

template <class SERVICE_HANDLER>
class Acceptor : public Event_Handler 
{
public:
	Acceptor (const INET_Address &local_addr, Reactor *r);
	virtual void handle_event(HANDLE h, Event_type et);
protected:
	virtual void accept(); // GoF template method
	virtual SERVICE_HANDLER *make_service_handler();
	virtual void accept_service_handler(SERVICE_HANDLER *);
	virtual void activate_service_handler(SERVICE_HANDLER *);

	virtual HANDLE get_handle() const;
private:
	INET_Address peer_acceptor_; // template placeholder
};