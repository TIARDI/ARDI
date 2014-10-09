#include "stdafx.h"
#include <stdexcept>
#include "Demux_Table.h"


int Demux_Table::convert_to_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
	FD_ZERO(read_fds);
	FD_ZERO(write_fds);
	FD_ZERO(except_fds);

	int fds = 0;

	for (const auto handleKvp : (*this))
	{
		if (!handleKvp.second.is_active)
			continue;

		if (handleKvp.second.type & READ || handleKvp.second.type & ACCEPT)
		{
			FD_SET((SOCKET)handleKvp.first, read_fds);
			fds++;
		}
		
		if (handleKvp.second.type & WRITE)
		{
			FD_SET((SOCKET)handleKvp.first, write_fds);
			fds++;
		}
		
		if (handleKvp.second.type == EXCEPT)
		{
			FD_SET((SOCKET)handleKvp.first, except_fds);
			fds++;
		}
	}

	return fds;
}
