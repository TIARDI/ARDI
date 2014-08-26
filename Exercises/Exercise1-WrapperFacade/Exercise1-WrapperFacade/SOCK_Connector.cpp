#include "SOCK_Connector.hpp"
#include "stdafx.h"

SOCK_Connector::SOCK_Connector()
{
}

void SOCK_Connector::connect(SOCK_Stream& server, INET_Addr& addr)
{
	SOCKET s = server.get_handle();
	const sockaddr* ad = addr.addr();

	::connect(s, ad, addr.size());
}

SOCK_Connector::~SOCK_Connector()
{
}
