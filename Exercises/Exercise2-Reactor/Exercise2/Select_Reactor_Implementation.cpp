#include "stdafx.h"
#include "Select_Reactor_Implementation.hpp"
#include <stdexcept>
#include <sstream>

Select_Reactor_Implementation::~Select_Reactor_Implementation()
{
	for (auto handlerKvp : demuxTable)
	{
		delete handlerKvp.second.handler;
	}
	//~demux_table() will clean the rest
}

void Select_Reactor_Implementation::register_handler(Event_Handler *eh, Event_type et)
{
	auto mapItr = demuxTable.find(eh->get_handle());
	if (mapItr != demuxTable.end())
	{
		//handle is currently in map - cleanup.
		delete mapItr->second.handler;
	}

	auto eht = EventHandlerTuple();
	eht.handler = eh;
	eht.type = et;

	demuxTable[eh->get_handle()] = eht;
}

void Select_Reactor_Implementation::remove_handler(Event_Handler *eh, Event_type et)
{
	auto mapItr = demuxTable.find(eh->get_handle());
	if (mapItr != demuxTable.end())
	{
		//handle is currently in map - cleanup.
		delete mapItr->second.handler;
		demuxTable.erase(mapItr);
	}
}

void Select_Reactor_Implementation::handle_events(const timeval *timeout)
{
	fd_set read_set, write_set, except_set;

	demuxTable.convert_to_fd_sets(&read_set, &write_set, &except_set);

	auto ret = ::select(0, &read_set, &write_set, &except_set, timeout);

	if (ret == SOCKET_ERROR)
	{
		auto ss = std::stringstream();
		ss << "In Select Reactor: socket error while running select(). ";
		ss << "ErrorCode: " << WSAGetLastError();
		throw std::runtime_error(ss.str());
	}
	else if (ret == 0) //timeout
	{
		for (auto handlerKvp : demuxTable)
		{
			handlerKvp.second.handler->handle_event(handlerKvp.first, TIMEOUT);
		}
	}
	else
	{
		for (auto handlerKvp : demuxTable)
		{
			if (FD_ISSET((SOCKET)handlerKvp.first, &read_set) ||
				FD_ISSET((SOCKET)handlerKvp.first, &write_set) ||
				FD_ISSET((SOCKET)handlerKvp.first, &except_set))
			{
				handlerKvp.second.handler->handle_event(handlerKvp.first, handlerKvp.second.type);
			}
		}
	}
}