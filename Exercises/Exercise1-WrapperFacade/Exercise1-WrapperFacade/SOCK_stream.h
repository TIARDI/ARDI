#pragma once
#include <stddef.h>
#ifdef _WIN32
#include <winsock.h>
#else
typedef int SOCKET;
#endif

extern const int INVALID_HANDLE_VALUE;

class SOCK_Stream {
public:
	SOCK_Stream();
	SOCK_Stream(SOCKET h);
	~SOCK_Stream();
	void set_handle(SOCKET h);
	SOCKET get_handle() const;
	size_t recv(void *buf, size_t len, int flags);
	size_t send(const char *buf, size_t len, int flags);
	size_t recv_n(char *buf, size_t len, int flags);
	size_t send_n(const char *buf, size_t len, int flags);

private:
	// Socket handle for exchanging socket data.
	SOCKET handle_;
};