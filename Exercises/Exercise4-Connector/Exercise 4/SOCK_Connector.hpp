 #pragma once
#include "INET_Address.hpp"
#include "SOCK_stream.hpp"

class SOCK_Connector
{
public:
	SOCK_Connector();
	void connect(SOCK_Stream& server, const INET_Address& addr);
	//void complete();
	virtual ~SOCK_Connector();
};
