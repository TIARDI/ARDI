#include "stdafx.h"
#include "LF_Thread_Pool.h"
#include <stdexcept>

void LF_Thread_Pool::join(int timeout)
{
	std::unique_lock<std::mutex> lock(mutex_);

	for (;;)
	{
		while (leader_thread_ != INVALID_THREAD_ID)
		{
			followers_condition_.wait(lock);
		}

		leader_thread_ = std::this_thread::get_id();

		lock.unlock();

		reactor_->handle_events(true); //only handle a single event

		lock.lock();
	}
}

void LF_Thread_Pool::promote_new_leader()
{
	std::unique_lock<std::mutex> lock(mutex_);

	if (leader_thread_ != std::this_thread::get_id())
		throw std::runtime_error("Only leader thread can promote.");

	leader_thread_ = INVALID_THREAD_ID;

	followers_condition_.notify_one();
}

void LF_Thread_Pool::deactivate_handle(HANDLE handle, Event_type eType)
{
	reactor_->deactivate_handle(handle, eType);
}

void LF_Thread_Pool::reactivate_handle(HANDLE handle, Event_type eType)
{
	reactor_->reactivate_handle(handle, eType);
}

LF_Thread_Pool* LF_Thread_Pool::Instance()
{
	static LF_Thread_Pool tp;
	return &tp;
}

LF_Thread_Pool::~LF_Thread_Pool()
{
	followers_condition_.notify_all();
}