#include "INET_Addr.hpp"

class INET_Addr
{
public:
	INET_Addr (uint16_t port, uint64_t addr);
	uint16_t get_port () const ;
	uint64_t get_ip_addr () const;
	const sockaddr *addr () const;
	size_t size () const;
};