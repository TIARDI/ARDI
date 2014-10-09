#pragma once
#include "Reactor_Implementation.hpp"
#include "Demux_Table.h"
#include <mutex>
#include <condition_variable>

class Select_Reactor_Implementation : public Reactor_Implementation
{
public:
	virtual ~Select_Reactor_Implementation();

	virtual void register_handler(Event_Handler *eh, Event_type et);
	virtual void remove_handler(Event_Handler *eh, Event_type et);

	virtual void deactivate_handle(HANDLE handle, Event_type eType);
	virtual void reactivate_handle(HANDLE handle, Event_type eType);

	virtual void handle_events(bool onlyOneEvent, const timeval *timeout);

private:
	Demux_Table demuxTable;
	std::mutex tablemutex_;
	std::condition_variable handleready_condition_;
};

