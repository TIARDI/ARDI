#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Reactor.hpp"

class LF_Thread_Pool
{
public:
	static LF_Thread_Pool* Instance();

	void join(int timeout = 0);
	void promote_new_leader();
	void deactivate_handle(HANDLE handle, Event_type eType);
	void reactivate_handler(HANDLE handle, Event_type eType);

protected:
	LF_Thread_Pool() : reactor_(Reactor::instance())
	{}

private:
	Reactor *reactor_;
	std::mutex mutex_;
	std::condition_variable followers_condition_;	std::thread::id leader_thread_;

	//static LF_Thread_Pool instance_;
};