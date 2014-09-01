#pragma once
#include "INET_Address.hpp"
#include "SOCK_stream.h"

class SOCK_Connector
{
public:
	SOCK_Connector();
	void connect(SOCK_Stream& server, INET_Address& addr);
	//void complete();
	virtual ~SOCK_Connector();
};
