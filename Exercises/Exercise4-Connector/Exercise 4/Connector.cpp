#include "stdafx.h"
#include "Connector.hpp"
#include <stdexcept>

template <class SERVICE_HANDLER, class IPC_CONNECTOR>
void Connector<SERVICE_HANDLER, IPC_CONNECTOR>::connect( SERVICE_HANDLER *sh, const Addr &remote_addr, Connection_Mode mode)
{
	connect_service_handler(sh, remote_addr, mode);
}

template <class SERVICE_HANDLER, class IPC_CONNECTOR>
virtual void Connector<SERVICE_HANDLER, IPC_CONNECTOR>::handle_event(HANDLE handle, Event_Type )
{ 
	complete(handle); 
}

template <class SERVICE_HANDLER, class IPC_CONNECTOR>
class Connector< SERVICE_HANDLER, IPC_CONNECTOR>::
	connect_service_handler(SERVICE_HANDLER *svc_handler, const Addr &addr, 
	Connection_Mode mode) 
{
	try {
		connector_.connect(*svc_handler, addr, mode);
		// activate if we connect synchronously
		activate_service_handler(svc_handler); // calls open() hook
	} 
	catch (SystemEx &ex)
	{
		if (ex.status() == EWOULDBLOCK && mode == ASYNC) {
			// register for asynchronously call back
			reactor_->register_handler(this,WRITE_MASK);
			// store <service handler *> in map
			connection_map_[connector_.get_handle()]= svc_handler;
		}
	}
} 

template <class SERVICE_HANDLER, class IPC_CONNECTOR>
virtual void Connector<SERVICE_HANDLER, IPC_CONNECTOR>::complete(HANDLE handle) 
{
	Connection_Map::iterator i = connection_map_.find(handle);

	if (i == connection_map_.end() ) 
		std::runtime_error("Connector fuck up!");

	// we just want the value part of the <key,value>
	SERVICE_HANDLER *svc_handler = (*i).second;
	
	// Transfer I/O Handle to <service_handler>
	svc_handler->set_handle(handle);
	reactor_->remove_handler(handle, WRITE_MASK);
	connection_map_.erase(i);
	
	// connection is complete so activate handler
	activate_service_handler(svc_handler); // calls open() hook
}
