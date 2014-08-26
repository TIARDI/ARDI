#include <winsock.h>
#include "INET_Addr.hpp"
#include "SOCK_stream.h"

class SOCK_Acceptor
{
public:
	// Initialize a passive-mode acceptor socket.
	SOCK_Acceptor (const INET_Addr &addr);

	~SOCK_Acceptor();

	// A second method to initialize a passivemode
	// acceptor socket, analogously to the constructor.
	void open (const INET_Addr &sock_addr);

	// Accept a connection and initialize the <stream>.
	void accept (SOCK_Stream &s);

private:
	SOCKET handle_; // Socket handle factory.
};