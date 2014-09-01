
#include "stdafx.h"
#include <iostream>
#include "SOCK_Acceptor.hpp"
#include "SOCK_Connector.hpp"
#include "SOCK_stream.h"
#include "INET_Address.hpp"


void RunClient(std::string serverIp)
{
	std::string message = "Hello from client";
	SOCK_Stream stream;
	SOCK_Connector connector;
	INET_Address addr(2222, inet_addr(serverIp.c_str()));
	connector.connect(stream,addr);
	
	stream.send(message.c_str(), message.size(), 0);
}

void RunServer()
{

//	struct sockaddr_in sock_addr;
	INET_Address inet(2222,INADDR_ANY);
	SOCK_Acceptor acceptor(inet);


	while(true) 
	{
		SOCK_Stream stream;
		char message[100] = {0};

		acceptor.accept(stream);
		std::cout << "Server: Connection accepted." << std::endl;
		stream.recv(message, 100, 0);
		std::cout << "Message: " << message << std::endl;

		if (strncmp("exit", message, 4) == 0) //used with telnet as client for testing.
		{
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3 && argv[1][0] == 'c')
	if(std::string(argv[1]).compare(std::string("c")) && argc == 3)
	{
		std::cout << "Running as client..." << std::endl;
		RunClient(std::string(argv[2]));
	}
	else if (argc == 2 && argv[1][0] == 's')
	else if(std::string(argv[1]).compare(std::string("s")))
	{
		std::cout << "Running as server..." << std::endl;
		RunServer();
	}
	else
	{
		std::cout << "Arguments not accepted. argc" << argc << ". Closing..." << std::endl;
		for(int i = 0; i < argc; i++)
		{
			std::cout << argv[i] << "[" << i << "]" << std::endl;
		}
		return 0;
	}

}

