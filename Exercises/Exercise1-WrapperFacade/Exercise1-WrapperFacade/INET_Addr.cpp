#include "stdafx.h"
#include "INET_Addr.hpp"

INET_Addr::INET_Addr (uint16_t port, uint64_t addr) 
{
	// Set up the address to become a server.
	memset (&addr_, 0, sizeof addr_);
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons (port);
	addr_.sin_addr.s_addr = htonl (addr);
}

uint16_t INET_Addr::get_port () const 
{ 
	return addr_.sin_port; 
}

uint64_t INET_Addr::get_ip_addr () const
{ 
	return addr_.sin_addr.s_addr; 
}

const sockaddr *INET_Addr::addr() const
{ 
	return reinterpret_cast <const sockaddr *>(&addr_);
}

size_t INET_Addr::size() const 
{ 
	return sizeof (addr_);
}
// ...
