#pragma once
#include "Event_handler.hpp"
#include "Reactor.hpp"


template <class SERVICE_HANDLER, class IPC_CONNECTOR>
class Connector : public Event_Handler 
{
public:
	enum Connection_Mode { SYNC, ASYNC };
	typedef typename IPC_CONNECTOR::PEER_ADDR Addr;
	Connector(Reactor *reactor) : reactor_(reactor) {}

	// Template Method
	void connect(SERVICE_HANDLER *sh, const Addr &remote_addr, Connection_Mode mode);

	// Adapter Method (used in asynchronous mode)
	virtual void handle_event(HANDLE handle, Event_type et);

protected:
	virtual void complete(HANDLE handle);
	// Continued from previous slide
	virtual void connect_service_handler(const Addr &addr, Connection_Mode mode);
	virtual void activate_service_handler(SERVICE_HANDLER *sh);

private:
	IPC_CONNECTOR connector_;

	// C++ standard library map that associates <HANDLES> with 
	// <SERVICE_HANDLER> s for pending connections
	typedef map<HANDLE, SERVICE_HANDLER*> Connection_Map;
	Connection_Map connection_map_;
	Reactor *reactor_;
};