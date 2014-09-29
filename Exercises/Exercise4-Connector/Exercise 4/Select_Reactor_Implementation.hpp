#pragma once
#include "Reactor_Implementation.hpp"
#include "Demux_Table.h"

class Select_Reactor_Implementation : public Reactor_Implementation
{
public:
	virtual ~Select_Reactor_Implementation();

	virtual void register_handler(Event_Handler *eh, Event_type et);
	virtual void remove_handler(Event_Handler *eh, Event_type et);

	virtual void handle_events(const timeval *timeout);

private:
	Demux_Table demuxTable;
};

