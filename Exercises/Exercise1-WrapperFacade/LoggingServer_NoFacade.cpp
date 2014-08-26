#if defined (_WIN32)
	#include <windows.h>
	typedef int ssize_t;
#else
	typedef unsigned int
	UINT32;
	#include <thread.h>
	#include <unistd.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <memory.h>
#endif /* _WIN32 */
	// Keep track of number of logging requests.
	static int request_count;
	// Lock that serializes concurrent access to request_count.
#if defined (_WIN32)
	static CRITICAL_SECTION lock;
#else
	static mutex_t lock;
#endif /* _WIN32 */

// Maximum size of a logging record.
static const int LOG_RECORD_MAX = 1024;
// Port number to listen on for requests.
static const int LOGGING_PORT = 10000;
// Entry point that writes logging records.
int write_record (char log_record[], int len) {
/* ... */
return 0;
}

// Entry point that processes logging records for one client connection.
#if defined (_WIN32)
	u_long
#else
	void *
#endif /* _WIN32 */
logging_handler (void *arg)
{
	// Handle UNIX/Win32 portability.
	#if defined (_WIN32)
		SOCKET h = reinterpret_cast <SOCKET>(arg);
	#else
	int h = reinterpret_cast<int> (arg);
	#endif /* _WIN32 */
		
	for (;;) 
	{
		#if defined (_WIN32)
			ULONG len;
		#else
			UINT32 len;
		#endif /* _WIN32 */
		// Ensure a 32-bit quantity.
		char log_record[LOG_RECORD_MAX];
		// The first <recv> reads the length(stored as a 32- bit integer) of adjacent logging record.
		// This code does not handle "short-<recv>s".
		ssize_t n = recv (h,reinterpret_cast <char *>(&len),sizeof len,0);
		// Bail out if we're shutdown or errors occur unexpectedly.
		if (n <= sizeof len)
			break;

		len = ntohl (len);
		if (len >LOG_RECORD_MAX) break;
		// The second <recv> then reads <len> bytes to obtain the actual record. This code handles "short-<recv>s".
		for (size_t nread =0; nread < len; nread += n)
		{ 
			n = recv (h,log_record + nread, len - nread, 0);
			// Bail out if an error occurs.
			if (n <= 0) return 0;
		}

		#if defined (_WIN32)
			EnterCriticalSection (&lock);
		#else
			mutex_lock (&lock);
		#endif /* _WIN32 */

		// Execute following two statements in a critical section to avoid ace conditions and scrambled output, respectively.
		++request_count;
		// A return value of -1 signifies failure.
		if (write_record (log_record, len) == -1)
			break;

		#if defined (_WIN32)
			LeaveCriticalSection (&lock);
		#else
			mutex_unlock (&lock);
		#endif /* _WIN32 */
	}

	#if defined (_WIN32)
		closesocket (h);
	#else
		close (h);
	#endif /* _WIN32 */
	return 0;
}

// Main driver function for the server.
int main (int argc, char *argv[]) 
{
	struct sockaddr_in sock_addr;
	// Handle UNIX/Win32 portability.
	#if defined (_WIN32)
		SOCKET acceptor;
		WORD version_requested = MAKEWORD(2,0);
		WSADATA wsa_data;
		int error = WSAStartup(version_requested, &wsa_data);
		if (error != 0) return -1;
	#else
		int acceptor;
	#endif /* _WIN32 */
	// Create a local endpoint of communication.
	acceptor = socket (AF_INET,SOCK_STREAM, 0);
	// Set up the address to become a server.
	memset (&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = PF_INET;
	sock_addr.sin_port = htons(LOGGING_PORT);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Associate address with endpoint.
	bind (acceptor,reinterpret_cast<struct sockaddr *>(&sock_addr), sizeof(sock_addr));
	// Make endpoint listen for connections.
	listen (acceptor, 5);

	// Main server event loop.
	for (;;) {
	// Handle UNIX/Win32 portability.
		#if defined (_WIN32)
			SOCKET h;
			DWORD t_id;
		#else
			int h;
			thread_t t_id;
		#endif /* _WIN32 */
		// Block waiting for clients to connect.
		h = accept (acceptor, 0, 0);
		//Spawn a new thread that runs the <server> entry point.
		#if defined (_WIN32)
			CreateThread (0, 0,LPTHREAD_START_ROUTINE(&logging_handler),reinterpret_cast <void *>(h), 0, &t_id);
		#else
			thr_create(0, 0, logging_handler,reinterpret_cast <void *> (h),THR_DETACHED, &t_id);
		#endif /* _WIN32 */
	}
	return 0;
}