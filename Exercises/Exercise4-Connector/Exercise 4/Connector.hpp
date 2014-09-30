#pragma once
#include "Event_handler.hpp"
#include "SOCK_Connector.hpp"
#include "Reactor.hpp"
#include <map>
#include <WinSock2.h>

template <class SERVICE_HANDLER>
class Connector : public Event_Handler 
{
public:
	enum Connection_Mode { SYNC, ASYNC };
	Connector(Reactor *reactor);

	// Template Method
	void connect(SERVICE_HANDLER *sh, const Addr &remote_addr, Connection_Mode mode);

	// Adapter Method (used in asynchronous mode)
	virtual void handle_event(HANDLE handle, Event_type et);

protected:
	virtual void complete(HANDLE handle);
	virtual void connect_service_handler(SERVICE_HANDLER *svc_handler, 
		const Addr &addr, Connection_Mode mode);
	virtual void activate_service_handler(SERVICE_HANDLER *sh);

private:
	SOCK_Connector connector_;

	// C++ standard library map that associates <HANDLES> with 
	// <SERVICE_HANDLER> s for pending connections
	std::map<HANDLE, SERVICE_HANDLER*> connection_map_;
	Reactor *reactor_;
};