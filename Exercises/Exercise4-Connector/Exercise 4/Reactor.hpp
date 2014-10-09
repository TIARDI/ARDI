#pragma once
#include "Event_handler.hpp"
#include "Reactor_Implementation.hpp"

#ifdef WIN32
	#include <WinSock2.h>
#else

#endif

// Dispatcher for Events (Synchrone)
class Reactor
{
public:
	// Register a new handle with the reactor
	virtual void register_handler(Event_Handler *eh, Event_type et) = 0;

	// Remove a handle from the reactor
	virtual void remove_handler(Event_Handler *eh, Event_type et) = 0;

	virtual void deactivate_handle(HANDLE handle, Event_type eType) = 0;
	virtual void reactivate_handle(HANDLE handle, Event_type eType) = 0;

	// Entry point into the reactive event loop
	virtual bool handle_events(bool onlyOneEvent = false, const timeval *timeout = 0) = 0;
	
	// Define a singleton access point (GoF pattern)
	static Reactor *instance();

protected:
	Reactor(Reactor_Implementation* reactor_impl);
	Reactor_Implementation* reactor_impl_; // uses the GoF Bridge pattern
};