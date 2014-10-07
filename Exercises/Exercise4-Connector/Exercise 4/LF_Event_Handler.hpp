#include "stdafx.h"
#include "Event_handler.hpp"
#include "LF_Thread_Pool.h"

class LF_Event_Handler : public Event_Handler
{
public:
	LF_Event_Handler(Event_Handler *eh, LF_Thread_Pool *tp) : concrete_event_handler_(eh), thread_pool_(tp)
	{}

	virtual void Handle_Event(HANDLE handle, Event_type eType)
	{
		thread_pool_->deactivate_handle(handle, eType);
		thread_pool_->promote_new_leader();

		concrete_event_handler_->handle_event(handle, eType);

		thread_pool_->reactivate_handler(handle, eType);
	}

private:
	Event_Handler *concrete_event_handler_;
	LF_Thread_Pool *thread_pool_;
};