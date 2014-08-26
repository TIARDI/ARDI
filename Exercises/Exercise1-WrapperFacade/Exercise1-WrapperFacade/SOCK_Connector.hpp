#pragma once
#include "INET_Addr.hpp"
#include "SOCK_stream.h"

class SOCK_Connector
{
public:
	SOCK_Connector();
	void connect(SOCK_Stream& server, INET_Addr& addr);
	//void complete();
	virtual ~SOCK_Connector();
};
