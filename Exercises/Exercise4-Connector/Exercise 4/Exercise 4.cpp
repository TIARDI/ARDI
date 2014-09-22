// Exercise 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Service_Handler.hpp"
#include "SOCK_stream.hpp"
#include "SOCK_Connector.hpp"

typedef Service_Handler<SOCK_Stream> Peer_Router;
typedef Connector<Peer_Router, SOCK_Connector> Peer_Connector;
typedef vector<Peer_Router>::iterator Peer_Iterator;

#include "Command_Router.hpp"
#include "Bulk_Data_Router.hpp"
#include "Status_Router.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

