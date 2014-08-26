#include "stdafx.h"
#include "SOCK_stream.h"
#include "winsockHandling.hpp"

SOCK_Stream::SOCK_Stream(SOCKET h) : handle_(h)
{
	
}

// Default and copy constructor.
SOCK_Stream::SOCK_Stream() : handle_(INVALID_VALUE_FOR_HANDLE)
{
	winsockHandling::init_winsock();
}

// Automatically close the handle on destruction.

SOCK_Stream::~SOCK_Stream () 
{ 
	closesocket(handle_);
	winsockHandling::close_winsock();
}

// Set/get the underlying SOCKET handle.
void SOCK_Stream::set_handle (SOCKET h)
{ 
	handle_ = h; 
}

SOCKET SOCK_Stream::get_handle () const 
{ 
	return handle_; 
}
// Regular I/O operations.

size_t SOCK_Stream::recv(void *buf, size_t len, int flags)
{
	return NULL;
}

size_t SOCK_Stream::send(const char *buf, size_t len, int flags)
{
	return NULL;
}

// I/O operations for "short" receives and sends.
size_t SOCK_Stream::recv_n(char *buf, size_t len, int flags)
{
	return NULL;
}

size_t SOCK_Stream::send_n(const char *buf, size_t len, int flags)
{
	return NULL;
}
// ... other methods omitted.