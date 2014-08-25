#include <stdint.h>
#include <WINSOCK.h>

class INET_Addr 
{
public:
	INET_Addr (uint16_t port, uint64_t addr) 
	{
		// Set up the address to become a server.
		memset (&addr_, 0, sizeof addr_);
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons (port);
		addr_.sin_addr.s_addr = htonl (addr);
	}
	uint16_t get_port () const 
	{ 
		return addr_.sin_port; 
	}

	uint64_t get_ip_addr () const
	{ 
		return addr_.sin_addr.s_addr; 
	}
	
	sockaddr *addr () const
	{ 
		return reinterpret_cast <sockaddr *>(&addr_);
	}

	size_t size () const { return sizeof (addr_);
	}
	// ...
private:
	sockaddr_in addr_;
};