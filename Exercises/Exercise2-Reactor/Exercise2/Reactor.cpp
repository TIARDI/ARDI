#include "stdafx.h"
#include "Reactor.h"
#include "Event_handler.hpp"

#ifdef WIN32
	#include <WinSock2.h>
#else

#endif

typedef Reactor Reactor_Implementation;

void Reactor::register_handler(Event_Handler *eh, Event_Type et)
{

}

void Reactor::register_handler(HANDLE h, Event_Handler *eh, Event_Type et) 
{

}

void Reactor::remove_handler(Event_Handler *eh, Event_Type et)
{

}

void Reactor::remove_handler(HANDLE h, Event_Type et) const
{

}

// Entry point into the reactive event loop
void Reactor::handle_events(timeval *timeout = 0)
{

}

// Define a singleton access point (GoF pattern)
static Reactor* Reactor::instance()
{
	return reactor_impl_;

}