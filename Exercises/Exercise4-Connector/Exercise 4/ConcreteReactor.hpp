#pragma once
#include "Reactor.hpp"

class ConcreteReactor : public Reactor
{
public:
	ConcreteReactor();
	~ConcreteReactor();
	virtual void register_handler(Event_Handler *eh, Event_type et);
	virtual void remove_handler(Event_Handler *eh, Event_type et);
	virtual void deactivate_handle(HANDLE handle, Event_type eType);
	virtual void reactivate_handle(HANDLE handle, Event_type eType);

	// Entry point into the reactive event loop
	virtual bool handle_events(bool onlyOneEvent, const timeval *timeout);
};

