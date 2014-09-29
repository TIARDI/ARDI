#pragma once
#include "Reactor.hpp"

class ConcreteReactor : public Reactor
{
public:
	ConcreteReactor();
	~ConcreteReactor();
	virtual void register_handler(Event_Handler *eh, Event_type et);
	virtual void remove_handler(Event_Handler *eh, Event_type et);

	// Entry point into the reactive event loop
	virtual void handle_events(const timeval *timeout);
};

