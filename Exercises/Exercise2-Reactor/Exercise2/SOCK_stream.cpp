#include "stdafx.h"
#include "SOCK_stream.h"
#include "winsockHandling.hpp"

SOCK_Stream::SOCK_Stream(SOCKET h) : handle_(h)
{
	winsockHandling::init_winsock();
}

// Default and copy constructor.
SOCK_Stream::SOCK_Stream() : handle_(INVALID_VALUE_FOR_HANDLE)
{
	winsockHandling::init_winsock();
}

// Automatically close the handle on destruction.

SOCK_Stream::~SOCK_Stream () 
{ 
	close();
}

void SOCK_Stream::close()
{
	if (handle_ != INVALID_VALUE_FOR_HANDLE)
	{
		closesocket(handle_);
		winsockHandling::close_winsock();
	}
}

// Set/get the underlying SOCKET handle.
void SOCK_Stream::set_handle (SOCKET h)
{ 
	close(); //close current socket first.
	handle_ = h; 
}

SOCKET SOCK_Stream::get_handle () const 
{ 
	return handle_; 
}
// Regular I/O operations.

size_t SOCK_Stream::recv(char *buf, size_t len, int flags)
{
	return ::recv(handle_, buf, len, flags);
}

size_t SOCK_Stream::send(const char *buf, size_t len, int flags)
{
	return ::send(handle_, buf, len, flags);
}

// I/O operations for "short" receives and sends.
size_t SOCK_Stream::recv_n(char *buf, size_t len, int flags)
{
	return 0;
}

size_t SOCK_Stream::send_n(const char *buf, size_t len, int flags)
{
	return 0;
}
// ... other methods omitted.