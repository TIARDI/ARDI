#include "stdafx.h"
#include "Acceptor.hpp"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"

//typedef Service_Handler<SOCK_Stream> Peer_Router;
//typedef Connector<Peer_Router, SOCK_Connector> Peer_Connector;
//typedef std::vector<Peer_Router>::iterator Peer_Iterator;
typedef Acceptor<Patient_Handler> Patient_Acceptor;

#define PATIENT_PORT 2003

int main()
{
	INET_Address patientAddr(PATIENT_PORT, INADDR_ANY);

	// Initialize concrete acceptor to listen for connections on 
	// well-known port
	Patient_Acceptor s_acceptor(patientAddr, Reactor::instance());

	// Event loop that accepts connection request events and processes
	// data from a gateway
	for (;;)
		Reactor::instance()->handle_events();
}
