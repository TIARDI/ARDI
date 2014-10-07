#include "stdafx.h"
#include "LF_Thread_Pool.h"

void LF_Thread_Pool::join(int timeout)
{
	std::unique_lock<std::mutex> lock(mutex_);

	for (;;)
	{
		while (leader_thread_ != std::thread::id())
		{
			followers_condition_.wait(lock);
		}

		leader_thread_ = std::this_thread::get_id();

		lock.unlock();

		reactor_->handle_events(0);

		lock.lock();
	}
	lock.unlock();
}

void LF_Thread_Pool::promote_new_leader()
{
	std::unique_lock<std::mutex> lock(mutex_);

	if (leader_thread_ != std::this_thread::get_id())
		throw;

	leader_thread_ = std::thread::id();

	followers_condition_.notify_all();

	lock.unlock();
}

void LF_Thread_Pool::deactivate_handle(HANDLE handle, Event_type eType)
{

}

void LF_Thread_Pool::reactivate_handler(HANDLE handle, Event_type eType)
{

}

LF_Thread_Pool* LF_Thread_Pool::Instance()
{
	static LF_Thread_Pool tp;
	return &tp;
}