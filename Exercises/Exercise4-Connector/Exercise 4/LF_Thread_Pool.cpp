#include "stdafx.h"
#include "LF_Thread_Pool.h"

void LF_Thread_Pool::join(int timeout)
{
	std::unique_lock<std::mutex> lock(mutex_);

	for (;;)
	{
		// Wait while there is a leader - while (leader_thread_ != NO_CURRENT_LEADER)
		while (leader_thread_ != std::thread::id())
		{
			followers_condition_.wait(lock);
		}

		// Set the current thread as leader
		leader_thread_ = std::this_thread::get_id();

		lock.unlock();

		// Do the next job from the reactor
		reactor_->handle_events(0);

		lock.lock();
	}
	lock.unlock();
}

void LF_Thread_Pool::promote_new_leader()
{
	std::unique_lock<std::mutex> lock(mutex_);

	// Throw exception. Only the leader can promote 
	if (leader_thread_ != std::this_thread::get_id())
		throw;

	// Indicate there is no leader
	leader_thread_ = std::thread::id();

	// notify a join method to promote a new leader
	followers_condition_.notify_all();

	lock.unlock();
}

// TODO: Implement to deactivate the handle to prevent race conditions
void LF_Thread_Pool::deactivate_handle(HANDLE handle, Event_type eType)
{

}

// TODO: Reenable the handle, for further use.
void LF_Thread_Pool::reactivate_handler(HANDLE handle, Event_type eType)
{

}

// Makes sure the Thread Pool is a singleton
LF_Thread_Pool* LF_Thread_Pool::Instance()
{
	static LF_Thread_Pool tp;
	return &tp;
}