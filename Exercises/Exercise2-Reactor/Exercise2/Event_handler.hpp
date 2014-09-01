#pragma once
#include <winsock2.h>

enum Event_type
{
	READ = 0x01,
	ACCEPT = READ,
	WRITE = 0x02,
	TIMEOUT = 0x03,
	EXCEPT = 0x04
};

class Event_Handler
{
public:
	virtual void handle_event(HANDLE h, Event_type eType) = 0;
	virtual HANDLE get_handle() const = 0;

	virtual ~Event_Handler() = 0;
};