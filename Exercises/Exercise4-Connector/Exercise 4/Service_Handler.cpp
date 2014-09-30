#include "stdafx.h"
#include "Service_Handler.hpp"
#include "SOCK_stream.hpp"

template <class IPC_STREAM>
void Service_Handler<IPC_STREAM>::handle_event(HANDLE h, Event_type et) 
{ 
	open(); 
}

template <class IPC_STREAM>
IPC_STREAM& Service_Handler<IPC_STREAM>::peer() 
{ 
	return ipc_stream_; 
}

template <class IPC_STREAM>
typename Service_Handler<IPC_STREAM>::Addr &Service_Handler<IPC_STREAM>::remote_addr() 
{ 
	return ipc_stream_.remote_addr(); 
}

template <class IPC_STREAM>
void Service_Handler<IPC_STREAM>::set_handle(HANDLE handle) 
{
	ipc_stream_.set_handle(handle);
}