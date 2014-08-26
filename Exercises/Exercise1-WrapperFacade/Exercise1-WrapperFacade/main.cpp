
#include "stdafx.h"
#include <iostream>
#include "SOCK_Acceptor.hpp"
#include "SOCK_Connector.hpp"
#include "SOCK_stream.h"
#include "INET_Address.hpp"


void RunClient()
{
	std::string message = "Hello from client";
	SOCK_Stream stream;
	SOCK_Connector connector;
	INET_Addr addr(2222,inet_addr("127.0.0.1"));
	connector.connect(stream,addr);
	stream.send(message.c_str(), message.size(),0);
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

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Only one argument is allowed" << std::endl;
		return -1;
	}

	if(argv[1] == "c")
	{
		std::cout << "Running as client..." << std::endl;
		RunClient();
	}
	else if(argv[1] == "s")
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


