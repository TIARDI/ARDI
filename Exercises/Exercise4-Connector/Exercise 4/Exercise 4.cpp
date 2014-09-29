// Exercise 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Service_Handler.hpp"
#include "SOCK_stream.hpp"
#include "SOCK_Connector.hpp"
#include "Connector.hpp"
#include <vector>
#include "Acceptor.hpp"
#include "SOCK_Acceptor.hpp"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"


typedef Service_Handler<SOCK_Stream> Peer_Router;
typedef Connector<Peer_Router, SOCK_Connector> Peer_Connector;
typedef std::vector<Peer_Router>::iterator Peer_Iterator;
typedef Acceptor<Patient_Handler, SOCK_Acceptor> Status_Acceptor;
typedef Acceptor<Patient_Handler, SOCK_Acceptor> Bulk_Data_Acceptor;
typedef Acceptor<Patient_Handler, SOCK_Acceptor> Command_Acceptor;

#include "Command_Router.hpp"
#include "Bulk_Data_Router.hpp"
#include "Status_Router.hpp"

int main()
{
	// Initialize three concrete acceptors to listen for connections on 
	// their well-known ports
	Status_Acceptor s_acceptor(STATUS_PORT, Reactor::instance());
	Bulk_Data_Acceptor bd_acceptor(BULK_DATA_PORT, Reactor::instance());
	Command_Acceptor c_acceptor(COMMAND_PORT, Reactor::instance());

	// Event loop that accepts connection request events and processes
	// data from a gateway
	for (; ;)
		Reactor::instance()->handle_events();
}
