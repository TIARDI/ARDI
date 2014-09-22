#pragma once
#include "Event_handler.hpp"

template <class SERVICE_HANDLER, class IPC_ACCEPTOR>
class Acceptor : public Event_Handler 
{
public:
	typedef typename IPC_ACCEPTOR::PEER_ADDR Addr;
	Acceptor (const Addr &local_addr, Reactor *r);
	virtual void handle_event(HANDLE h, Event_type et);
protected:
	virtual void accept(); // GoF template method
	virtual SERVICE_HANDLER *make_service_handler();
	virtual void accept_service_handler(SERVICE_HANDLER *);
	virtual void activate_service_handler(SERVICE_HANDLER *);

	virtual HANDLE get_handle() const;
private:
	IPC_ACCEPTOR peer_acceptor_; // template placeholder
};