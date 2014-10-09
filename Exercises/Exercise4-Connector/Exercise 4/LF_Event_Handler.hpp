#include "stdafx.h"
#include "Event_handler.hpp"
#include "LF_Thread_Pool.h"

class LF_Event_Handler : public Event_Handler
{
public:
	LF_Event_Handler(Event_Handler *eh, LF_Thread_Pool *tp) : concrete_event_handler_(eh), thread_pool_(tp)
	{}

	~LF_Event_Handler()
	{
	}

	// Do some actions related to the thread pool
	virtual void handle_event(HANDLE handle, Event_type eType)
	{
		// Deactivate to prevent race conditions, when promoting a new leader
		thread_pool_->deactivate_handle(handle, eType);

		// Promote a new leader
		thread_pool_->promote_new_leader();

		// Do the work is actually has to do
		concrete_event_handler_->handle_event(handle, eType);

		thread_pool_->reactivate_handle(handle, eType);
	}

	HANDLE get_handle() const
	{
		return concrete_event_handler_->get_handle();
	}

private:
	Event_Handler *concrete_event_handler_;
	LF_Thread_Pool *thread_pool_;
};