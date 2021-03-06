#pragma once
//#include "Event_handler.hpp"
#include "SOCK_Connector.hpp"
#include "Reactor.hpp"
#include <WinSock2.h>

template <class SERVICE_HANDLER>
class Connector 
{
public:
	Connector(){}

	// Template Method
	void connect(SERVICE_HANDLER *sh, const INET_Address &remote_addr)
	{
		connect_service_handler(sh, remote_addr);
	}

protected:
	virtual void connect_service_handler(SERVICE_HANDLER *svc_handler, 
		const INET_Address &addr)
	{
		connector_.connect(svc_handler->peer(), addr);
		// activate if we connect synchronously
		activate_service_handler(svc_handler); // calls open() hook
	} 

	virtual void activate_service_handler(SERVICE_HANDLER *sh)
	{
		sh->open();
	}

private:
	SOCK_Connector connector_;
};