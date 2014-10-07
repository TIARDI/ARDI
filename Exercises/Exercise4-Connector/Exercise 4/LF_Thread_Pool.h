#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Reactor.hpp"

class LF_Thread_Pool
{
public:
	LF_Thread_Pool(Reactor *reactor) : reactor_(reactor)
	{}

	void join(int timeout = 0);
	void promote_new_leader();
	void deactivate_handle(HANDLE handle, Event_type eType);
	void reactivate_handler(HANDLE handle, Event_type eType);

private:
	Reactor *reactor_;
	std::mutex mutex_;
	std::condition_variable followers_condition_;	std::thread::id leader_thread_;
};