#pragma once
#include "Event_handler.hpp"
#include "SOCK_stream.hpp"
#include <string>

class Service_Handler : public Event_Handler 
{
public:
	virtual void handle_event(HANDLE h, Event_type et);

	// Hook template method, defined by a subclass
	virtual void open() = 0;
	SOCK_Stream &peer();
	//INET_Address& remote_addr();
	void set_handle(HANDLE handle);
	HANDLE get_handle() const;

protected:
	// transport handle
	SOCK_Stream ipc_stream_;
};