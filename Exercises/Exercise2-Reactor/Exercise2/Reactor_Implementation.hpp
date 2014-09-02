#pragma once
#include "Event_handler.hpp"

class Reactor_Implementation
{
public:
	virtual void register_handler(Event_Handler *eh, Event_type et) = 0;
	virtual void remove_handler(Event_Handler *eh, Event_type et) = 0;

	virtual void handle_events(const timeval *timeout = 0) = 0;

	virtual ~Reactor_Implementation(){}
};