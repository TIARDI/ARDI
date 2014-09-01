#pragma once
#include "stdafx.h"
#include <stdint.h>

#ifdef _WIN32
#include <winsock2.h>
#else
//TODO: sockaddr and sockaddr_in
#endif

class INET_Address
{
public:
	INET_Address(uint16_t port, uint32_t addr);
	uint16_t get_port() const ;
	uint32_t get_ip_addr() const;
	const sockaddr *addr() const;
	size_t size() const;
	
private:
	sockaddr_in addr_;
};