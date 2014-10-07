#include "stdafx.h"
#include "SOCK_Connector.hpp"
#include "winsockHandling.hpp"
#include <stdexcept>


SOCK_Connector::SOCK_Connector()
{
	winsockHandling::init_winsock();
}

void SOCK_Connector::connect(SOCK_Stream& server, const INET_Address& addr)
{
	int ret = 0;
	const sockaddr* ad = addr.addr();
	SOCKET s = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		ret = WSAGetLastError();
		throw std::runtime_error("Socket() failed.");
	}

	ret = ::connect(s, ad, addr.size());
	if (ret != 0)
	{
		ret = WSAGetLastError();
		throw std::runtime_error("Connect() failed.");
	}
	else
	{
		server.set_handle(s);
	}
}

SOCK_Connector::~SOCK_Connector()
{
	winsockHandling::close_winsock();
}
