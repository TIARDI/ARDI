#include "stdafx.h"
#include "Service_Handler.hpp"
#include "SOCK_stream.hpp"

void Service_Handler::handle_event(HANDLE h, Event_type et) 
{ 
	open(); 
}

SOCK_Stream& Service_Handler::peer() 
{ 
	return ipc_stream_; 
}

//INET_Address& Service_Handler::remote_addr() 
//{ 
//	return ipc_stream_.remote_addr(); 
//}

void Service_Handler::set_handle(HANDLE handle) 
{
	ipc_stream_.set_handle((SOCKET)handle);
}

HANDLE Service_Handler::get_handle() const
{
	return (HANDLE)ipc_stream_.get_handle();
}