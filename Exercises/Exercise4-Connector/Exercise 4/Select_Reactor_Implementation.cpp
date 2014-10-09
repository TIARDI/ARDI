#include "stdafx.h"
#include "Select_Reactor_Implementation.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>

using namespace std::this_thread;

Select_Reactor_Implementation::~Select_Reactor_Implementation()
{
	//~demux_table() will clean the rest
}

void Select_Reactor_Implementation::register_handler(Event_Handler *eh, Event_type et)
{
	std::unique_lock<std::mutex> lock(tablemutex_);
	auto mapItr = demuxTable.find(eh->get_handle());
	if (mapItr != demuxTable.end())
	{
		//handle is currently in map - cleanup.
		delete mapItr->second.handler;
	}

	EventHandlerTuple eht;
	eht.handler = eh;
	eht.type = et;
	eht.is_active = true;

	demuxTable[eh->get_handle()] = eht;

	handleready_condition_.notify_all();
}

void Select_Reactor_Implementation::remove_handler(Event_Handler *eh, Event_type et)
{
	(void)et; //unused variable
	std::unique_lock<std::mutex> lock(tablemutex_);

	auto mapItr = demuxTable.find(eh->get_handle());
	if (mapItr != demuxTable.end())
	{
		//handle is currently in map - cleanup.
		//delete mapItr->second.handler;
		demuxTable.erase(mapItr);
	}
}

void Select_Reactor_Implementation::deactivate_handle(HANDLE handle, Event_type et)
{
	std::unique_lock<std::mutex> lock(tablemutex_);
	auto mapItr = demuxTable.find(handle);
	if (mapItr != demuxTable.end())
	{
		//mapItr->second.type = (Event_type)(mapItr->second.type & ~et);
		mapItr->second.is_active = false;
	}
}

void Select_Reactor_Implementation::reactivate_handle(HANDLE handle, Event_type et)
{
	std::unique_lock<std::mutex> lock(tablemutex_);
	auto mapItr = demuxTable.find(handle);
	if (mapItr != demuxTable.end())
	{
		//mapItr->second.type = (Event_type)(mapItr->second.type | et);
		mapItr->second.is_active = true;
		handleready_condition_.notify_all();
	}
}

bool Select_Reactor_Implementation::handle_events(bool onlyOneEvent, const timeval *timeout)
{
	fd_set read_set, write_set, except_set;

	std::unique_lock<std::mutex> lock(tablemutex_);
	
	//std::cout << get_id() << " Pre convert" << std::endl;
	int fds = demuxTable.convert_to_fd_sets(&read_set, &write_set, &except_set);
	//std::cout << get_id() << " Pre loop fds: " << fds << std::endl;
	while (fds < 1)
	{
		//std::cout << get_id() << " Start loop fds: " << fds << std::endl;
		handleready_condition_.wait(lock); //wait for handles to become available
		//std::cout << get_id() << " Getting fds" << std::endl;
		fds = demuxTable.convert_to_fd_sets(&read_set, &write_set, &except_set);
		//std::cout << get_id() << " End loop fds: " << fds << std::endl;
	}	

	std::map<HANDLE, EventHandlerTuple> iterTable(demuxTable);
	lock.unlock();
		
	//std::cout << get_id() << " Pre SELECT" << std::endl;
	auto ret = ::select(0, &read_set, &write_set, &except_set, timeout);
	//std::cout << get_id() << " Post SELECT" << std::endl;

	if (ret == SOCKET_ERROR)
	{
		std::stringstream ss;
		ss << "In Select Reactor: socket error while running select(). ";
		ss << "ErrorCode: " << WSAGetLastError();
		std::cout << ss.str();
		throw std::runtime_error(ss.str());
	}
	else if (ret == 0) //timeout
	{
		return false; //bugfix
		for (auto handlerKvp : iterTable)
		{
			handlerKvp.second.handler->handle_event(handlerKvp.first, TIMEOUT);
		}
	}
	else
	{
		bool handledEvent = false;
		for (auto handlerKvp : iterTable)
		{
			if ((!onlyOneEvent || !handledEvent) && FD_ISSET((SOCKET)handlerKvp.first, &read_set))
			{
				//std::cout << get_id() << " Pre READ" << std::endl;
				handlerKvp.second.handler->handle_event(handlerKvp.first, READ);
				handledEvent = true;
				//std::cout << get_id() << " Post READ" << std::endl;
			}

			if ((!onlyOneEvent || !handledEvent) && FD_ISSET((SOCKET)handlerKvp.first, &write_set))
			{
				//std::cout << get_id() << " Pre WRITE" << std::endl;
				handlerKvp.second.handler->handle_event(handlerKvp.first, WRITE);
				handledEvent = true;
				//std::cout << get_id() << " Post WRITE" << std::endl;
			}

			if ((!onlyOneEvent || !handledEvent) && FD_ISSET((SOCKET)handlerKvp.first, &except_set))
			{
				handlerKvp.second.handler->handle_event(handlerKvp.first, EXCEPT);
				handledEvent = true;
			}

			if(onlyOneEvent && handledEvent)
			{
				break;
			}
		}
		return handledEvent;
	}
}