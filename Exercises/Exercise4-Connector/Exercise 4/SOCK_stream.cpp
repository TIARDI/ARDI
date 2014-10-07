#include "stdafx.h"
#include "SOCK_stream.hpp"
#include "winsockHandling.hpp"

SOCK_Stream::SOCK_Stream(SOCKET h) : handle_(h)
{
	winsockHandling::init_winsock();
}

// Default constructor.
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

int SOCK_Stream::recv(char *buf, size_t len, int flags)
{
	return ::recv(handle_, buf, len, flags);
}

size_t SOCK_Stream::send(const char *buf, size_t len, int flags)
{
	return ::send(handle_, buf, len, flags);
}