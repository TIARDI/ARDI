
#include "stdafx.h"
#include <iostream>
#include "SOCK_Acceptor.hpp"
#include "SOCK_Connector.hpp"
#include "SOCK_stream.h"
#include "INET_Addr.hpp"
int main(int argc, char *argv[])
{
	if(argc != 1)
	{
		std::cout << "Only one argument is allowed" << std::endl;
		return -1;
	}

	if(argv[0] == "c")
	{
		std::cout << "Running as client..." << std::endl;
		RunClient();
	}
	else if(argv[0] == "s")
	{
		std::cout << "Running as server..." << std::endl;
		RunServer();
	}
	else
	{
		std::cout << "Argument '" << argv[0] << "' not allowed. Closing..." << std::endl;
		return -1;
	}

}

void RunClient()
{
	
	INET_Addr addr
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

		while(true) 
		{
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
}

void RunServer();