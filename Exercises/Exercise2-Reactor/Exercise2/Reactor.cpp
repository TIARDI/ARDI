#include "stdafx.h"
#include "Reactor.hpp"

void Reactor::register_handler(Event_Handler *eh, Event_type et)
{

}

void Reactor::register_handler(HANDLE h, Event_Handler *eh, Event_type et) 
{

}

void Reactor::remove_handler(Event_Handler *eh, Event_type et)
{

}

void Reactor::remove_handler(HANDLE h, Event_type et) const
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