#pragma once
#include "Event_handler.hpp"
#include "SOCK_stream.hpp"

template <class IPC_STREAM>
class Service_Handler : public Event_Handler 
{
public:
	typedef typename IPC_STREAM::PEER_ADDR Addr;
	typedef Service_Handler<SOCK_STREA
	virtual void handle_event(HANDLE h, Event_type et);

	// Hook template method, defined by a subclass
	virtual void open() = 0;
	IPC_STREAM &peer();
	Addr &remote_addr();
	void set_handle(HANDLE handle);
	HANDLE get_handle();

private:
	// Template placeholder for a concrete IPC mechanism wrapper 
	// façade, which encapsulate a data-mode transport endpoint and
	// transport handle
	IPC_STREAM ipc_stream_;
};