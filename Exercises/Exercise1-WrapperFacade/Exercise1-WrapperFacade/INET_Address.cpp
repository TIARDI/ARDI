#include "stdafx.h"
#include "INET_Address.hpp"

INET_Address::INET_Address (uint16_t port, uint32_t addr) 
{
	// Set up the address to become a server.
	memset (&addr_, 0, sizeof addr_);
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons (port);
	addr_.sin_addr.s_addr =  addr;
}

uint16_t INET_Address::get_port () const 
{ 
	return addr_.sin_port; 
}

uint32_t INET_Address::get_ip_addr () const
{ 
	return addr_.sin_addr.s_addr; 
}

const sockaddr *INET_Address::addr() const
{ 
	return reinterpret_cast <const sockaddr *>(&addr_);
}

size_t INET_Address::size() const 
{ 
	return sizeof (addr_);
}
// ...
