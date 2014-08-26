
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
	

}

void RunServer()
{

	struct sockaddr_in sock_addr;
	INET_Addr inet(2222,INADDR_ANY);
	SOCK_Acceptor acceptor(inet);
	
	SOCK_Stream stream;

	while(true) 
	{
		acceptor.accept (stream);

		//receive from
	}
}