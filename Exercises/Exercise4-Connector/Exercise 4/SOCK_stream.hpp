#pragma once
#include <stddef.h>
#ifdef _WIN32
#include <winsock2.h>
#else
typedef unsigned int SOCKET;
#endif

const SOCKET INVALID_VALUE_FOR_HANDLE = ~0;

class SOCK_Stream {
public:
	SOCK_Stream(SOCKET h);
	SOCK_Stream();	
	~SOCK_Stream();
	void close();
	void set_handle(SOCKET h);
	SOCKET get_handle() const;
	int recv(char *buf, size_t len, int flags = 0);
	size_t send(const char *buf, size_t len, int flags = 0);

private:
	// Socket handle for exchanging socket data.
	SOCKET handle_;
};