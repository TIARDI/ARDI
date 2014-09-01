#pragma once

class Reactor
{
public:
	virtual void register_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void register_handler(HANDLE h, Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(Event_Handler *eh, Event_Type et) = 0;
	virtual void remove_handler(HANDLE h, Event_Type et) const = 0;
	
	// Entry point into the reactive event loop
	void handle_events(timeval *timeout =0);
	
	// Define a singleton access point (GoF pattern)
	static Reactor *instance();
private:
	Reactor_Implementation *reactor_impl_; // uses the GoF Bridge pattern
};