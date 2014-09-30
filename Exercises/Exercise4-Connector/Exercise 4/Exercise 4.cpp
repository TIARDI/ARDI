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

//typedef Service_Handler<SOCK_Stream> Peer_Router;
//typedef Connector<Peer_Router, SOCK_Connector> Peer_Connector;
//typedef std::vector<Peer_Router>::iterator Peer_Iterator;
typedef Acceptor<Patient_Handler> Patient_Acceptor;

#define PATIENT_PORT 2003

int main()
{
	// Initialize three concrete acceptors to listen for connections on 
	// their well-known ports
	Patient_Acceptor s_acceptor(PATIENT_PORT, Reactor::instance());

	// Event loop that accepts connection request events and processes
	// data from a gateway
	for (; ;)
		Reactor::instance()->handle_events();
}
