#include "stdafx.h"
#include "LF_Thread_Pool.h"

void LF_Thread_Pool::join(int timeout)
{
	mutex_.lock();

	for (;;)
	{
		while (leader_thread_ == std::thread::id())
		{
			followers_condition_.wait_for(std::unique_lock<std::mutex>(mutex_), std::chrono::seconds(timeout));
		}

		leader_thread_ = std::this_thread::get_id();

		mutex_.unlock();

		reactor_->handle_events();

		mutex_.lock();
	}
	mutex_.unlock();
}

void LF_Thread_Pool::promote_new_leader()
{
	mutex_.lock();

	if (leader_thread_ != std::this_thread::get_id())
		throw;

	leader_thread_ = std::thread::id();

	followers_condition_.notify_all();

	mutex_.unlock();
}

void LF_Thread_Pool::deactivate_handle(HANDLE handle, Event_type eType)
{

}

void LF_Thread_Pool::reactivate_handler(HANDLE handle, Event_type eType)
{

}