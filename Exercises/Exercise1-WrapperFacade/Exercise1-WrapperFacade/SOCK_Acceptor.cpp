#include "stdafx.h"
#include "SOCK_Acceptor.hpp"

SOCK_Acceptor::SOCK_Acceptor (const INET_Addr &addr)
{
	// Create a local endpoint of communication.
	handle_ = socket (PF_INET, SOCK_STREAM, 0);
	// Associate address with endpoint.
	bind (handle_, addr.addr (), addr.size());
	// Make endpoint listen for connections.
	listen (handle_, 5);
};

// A second method to initialize a passivemode
// acceptor socket, analogously to the constructor.
void SOCK_Acceptor::open (const INET_Addr &sock_addr)
{
	// Implement Code
};

// Accept a connection and initialize the <stream>.
void SOCK_Acceptor::accept (SOCK_Stream &s)
{
	s.set_handle(::accept(handle_, 0, 0));
}