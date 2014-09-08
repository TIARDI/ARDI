#pragma once
#include "INET_Address.hpp"
#include "SOCK_stream.h"
#ifdef _WIN32
#include <winsock2.h>
#else
// Unix SOCKET
#endif

class SOCK_Acceptor
{
public:
	// Initialize a passive-mode acceptor socket.
	SOCK_Acceptor (const INET_Address &addr);

	~SOCK_Acceptor();

	// A second method to initialize a passivemode
	// acceptor socket, analogously to the constructor.
	void open (const INET_Address &sock_addr);

	// Accept a connection and initialize the <stream>.
	void accept (SOCK_Stream &s);

	SOCKET get_handle() const;

private:
	SOCKET handle_; // Socket handle factory.
};