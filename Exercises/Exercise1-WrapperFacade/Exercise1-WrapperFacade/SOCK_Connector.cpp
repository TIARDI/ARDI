#include "stdafx.h"
#include "SOCK_Connector.hpp"
#include "winsockHandling.hpp"


SOCK_Connector::SOCK_Connector()
{
	winsockHandling::init_winsock();
}

void SOCK_Connector::connect(SOCK_Stream& server, INET_Address& addr)
{
	SOCKET s = server.get_handle();
	const sockaddr* ad = addr.addr();

	::connect(s, ad, addr.size());
}

SOCK_Connector::~SOCK_Connector()
{
	winsockHandling::close_winsock();
}
