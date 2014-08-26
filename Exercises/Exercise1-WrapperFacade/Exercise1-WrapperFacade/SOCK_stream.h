
typedef int SOCKET;
const int IN

class SOCK_Stream {
public:
// Default and copy constructor.
	SOCK_Stream () : handle_
	(INVALID_HANDLE_VALUE) { }
	SOCK_Stream (SOCKET h): handle_ (h) { }
// Automatically close the handle on destruction.
	~SOCK_Stream () { close (handle_); }
// Set/get the underlying SOCKET handle.
	void set_handle (SOCKET h) { handle_ = h; }
	SOCKET get_handle () const { return handle_; }
// Regular I/O operations.
	ssize_t recv (void *buf, size_t len, int flags);
	ssize_t send (const char *buf, size_t len, int flags);
// I/O operations for "short" receives and sends.
	ssize_t recv_n (char *buf, size_t len, int flags);
	ssize_t send_n (const char *buf, size_t len, int flags);
// ... other methods omitted.
private:
// Socket handle for exchanging socket data.
	SOCKET handle_;
};