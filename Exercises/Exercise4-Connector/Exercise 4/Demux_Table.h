#pragma once
#include <WinSock2.h>
#include <map>

#include "Event_handler.hpp"

struct EventHandlerTuple
{
	Event_Handler* handler;
	Event_type type;
};

class Demux_Table : public std::map<HANDLE, EventHandlerTuple>
{
public:
	void convert_to_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds);
};

