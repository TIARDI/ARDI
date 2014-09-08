#include "stdafx.h"
#include "SOCK_Acceptor.hpp"
#include "winsockHandling.hpp"
#include <stdexcept>

SOCK_Acceptor::SOCK_Acceptor (const INET_Address &addr)
{
	winsockHandling::init_winsock();

	open(addr);
};

SOCK_Acceptor::~SOCK_Acceptor()
{
	closesocket(handle_);
	winsockHandling::close_winsock();
}

// A second method to initialize a passivemode
// acceptor socket, analogously to the constructor.
void SOCK_Acceptor::open (const INET_Address &addr)
{
	if (handle_ != INVALID_VALUE_FOR_HANDLE)
		closesocket(handle_);

	// Create a local endpoint of communication.
	handle_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (handle_ == INVALID_SOCKET)
	{
		throw std::runtime_error("Socket() failed.");
	}

	// Associate address with endpoint.
	auto ret = bind(handle_, addr.addr(), addr.size());
	if (ret != 0)
	{
		throw std::runtime_error("Bind() failed.");
	}

	// Make endpoint listen for connections.
	ret = listen(handle_, 5);
	if (ret != 0)
	{
		throw std::runtime_error("Listen() failed.");
	}
};

SOCKET SOCK_Acceptor::get_handle() const
{
	return handle_;
}

// Accept a connection and initialize the <stream>.
void SOCK_Acceptor::accept (SOCK_Stream &s)
{
	s.set_handle(::accept(handle_, 0, 0));
}